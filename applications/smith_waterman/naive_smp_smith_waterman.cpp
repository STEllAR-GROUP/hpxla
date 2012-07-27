//  Copyright (c) 2012 Stephanie Crillo and Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/util/high_resolution_timer.hpp>

#include <hpxla/local_matrix.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/atomic.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

///////////////////////////////////////////////////////////////////////////////
// Utility stuff written by Bryce. Instructions for Stephie:
//
// maximum() is a function that takes three or four arguments and returns the
// highest of the three or four arguments. 
//
// gap, match and mismatch are (like) global const variables that define the gap
// scoring scheme. They are just like the const chars used in the calculator
// example from Bjarne's book.

// WARN: This will break for sequences with length greater than 2^32.

template <typename T>
T const& maximum(T const& A, T const& B, T const& C)
{
    return (std::max)((std::max)(A, B), C); 
}

template <typename T>
T const& maximum(T const& A, T const& B, T const& C, T const& D)
{
    return (std::max)((std::max)((std::max)(A, B), C), D); 
}

enum gap_scoring
{
    gap      = -1,
    match    = +2,
    mismatch = -1 
};

///////////////////////////////////////////////////////////////////////////////
struct coords
{
    coords(boost::uint32_t i_, boost::uint32_t j_) : i(i_), j(j_) {}

    boost::uint32_t i;
    boost::uint32_t j;
};

std::ostream& operator<<(std::ostream& out, coords const& c)
{
    out << "(" << c.i << "," << c.j << ")"; 
    return out; 
}

///////////////////////////////////////////////////////////////////////////////
struct alignment
{ 
    hpxla::local_matrix<hpx::future<boost::int64_t> > H;
    std::vector<coords> backpath;
};

// Keep this under 128 bits and it'll be lockfree when used with boost::atomic<>
// on (modern) x86-64 platforms.
struct winner
{
    winner() : value(0), i(0), j(0) {}

    winner(boost::int64_t value_, boost::uint32_t i_, boost::uint32_t j_)
      : value(value_), i(i_), j(j_)
    {}

    boost::int64_t value;
    boost::uint32_t i;
    boost::uint32_t j;
};

boost::atomic<winner> H_best(winner(0, 0, 0));

boost::int64_t generate_scoring_cell(
    boost::uint32_t i
  , boost::uint32_t j
  , char ai
  , char bj
  , hpx::future<boost::int64_t> const& left      // H(i, j-1)
  , hpx::future<boost::int64_t> const& diagonal  // H(i-1, j-1)
  , hpx::future<boost::int64_t> const& up        // H(i-1, j) 
    )
{
    boost::int64_t match_mismatch = 0;
    if (ai == bj)
    {
        match_mismatch = diagonal.get() + match;
    } 
    else 
    {
        match_mismatch = diagonal.get() + mismatch;
    }
    boost::int64_t deletion = up.get() + gap;
    boost::int64_t insertion = left.get() + gap;        
    
    boost::int64_t ij_value
        = maximum(boost::int64_t(0), match_mismatch, deletion, insertion);

    winner H_best_old = H_best.load(); 

    while (true)
    {
        winner H_best_new(ij_value, i, j);

        if (H_best_new.value > H_best_old.value)
        {
            if (H_best.compare_exchange_weak(H_best_old, H_best_new))
                break;
        }
        else
            break;
    }

    return ij_value;
}

///////////////////////////////////////////////////////////////////////////////
alignment smith_waterman(std::string const& a, std::string const& b)
{
    // Make sure that a and b have the same size (e.g. m == n), for now.
    BOOST_ASSERT(a.size() == b.size());

    // j is the length of our input sequences plus one. This is number of
    // rows and columns in our square matrix. The extra, zero-filled row is
    // needed because the algorithm backtracks until it reaches a zero number.
    boost::uint32_t k = a.size() + 1; 

    // Create our matrix and fill it with zeros.
    alignment result;

    // k * k matrix
    result.H = hpxla::local_matrix<hpx::future<boost::int64_t> >(k, k); 

    // Declare a matrix view (e.g. an "alias") called H which refers to
    // result.H.
    hpxla::local_matrix_view<hpx::future<boost::int64_t> > H = result.H.view();

    for (boost::uint32_t x = 0; x < k; ++x)
    {
        H(0, x) = hpx::lcos::create_value<boost::int64_t>(0);
        H(x, 0) = hpx::lcos::create_value<boost::int64_t>(0);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Generate scoring matrix.

    for (boost::uint32_t i = 1; i < k; ++i)
    {
        for (boost::uint32_t j = 1; j < k; ++j)
        {
            H(i, j) = hpx::async(&generate_scoring_cell, i, j, a[i-1], b[j-1]
                               , H(i, j-1)   // left dependency
                               , H(i-1, j-1) // diagonal dependency
                               , H(i-1, j)); // top dependency
        } 
    }  

    for (boost::uint32_t i = 1; i < k; ++i)
        for (boost::uint32_t j = 1; j < k; ++j)
            H(i, j).get(); 

    ///////////////////////////////////////////////////////////////////////////
    // Backtracking.

    // 0.) Make a vector to hold coords.
    // 1.) We want to start at H_best, or the coordinate of H_best, so
    //     (i_max, j_max).
    // 2.) Then, determine which value is largest (where i is initially i_max,
    //     and j is initially j_max):
    //        (i-1, j-1) for match/mismatch,
    //        (i-1, j)   for an insertion, and
    //        (i, j-1)   for a deletion. 
    // 3.) Reset the current i and j coords to equal next i and j coords. 
   
    winner H_max = H_best.load();
 
    std::vector<coords>& backpath = result.backpath;
    backpath.push_back(coords(H_max.i, H_max.j)); 

    while (true)
    {
        coords last = backpath.back();
        boost::int64_t match_mismatch = H(last.i-1, last.j-1).get(); 
        boost::int64_t insertion = H(last.i, last.j-1).get();
        boost::int64_t deletion = H(last.i-1, last.j).get();
    
        boost::int64_t m = maximum(match_mismatch, insertion, deletion);    
    
        if (m == 0)
            break; 

        if (m == match_mismatch)
        {
            backpath.push_back(coords(last.i-1, last.j-1));
        }
        else if (m == insertion)
        {
            backpath.push_back(coords(last.i, last.j-1));
        }
        else // deletion
        {
            backpath.push_back(coords(last.i-1, last.j));
        } 
    }    

    return result;
}

void benchmark_sw(
    boost::random::mt19937& rng
  , boost::uint32_t length
  , boost::uint32_t iterations = 1 << 10
    )
{ 
    std::string const chars("ATGC");
  
    boost::random::uniform_int_distribution<boost::uint32_t>
        index_dist(0, chars.size() - 1);

    ///////////////////////////////////////////////////////////////////////////
    // Generate our sequences using the mt19937 random number generator.
    std::string a, b;

    for (boost::uint32_t x = 0; x < length; ++x)
    {
        a += chars[index_dist(rng)];
        b += chars[index_dist(rng)];
    }

    ///////////////////////////////////////////////////////////////////////////
    // Generate our sequences using the mt19937 random number generator.
    hpx::util::high_resolution_timer t;

    for (boost::uint32_t x = 0; x < iterations; ++x)
        smith_waterman(a, b);

    double runtime = t.elapsed();

    std::cout << length << "," << iterations << "," << runtime << "\n";
}

std::string const nocolor = "\E[0m";
std::string const yellow  = "\E[1;33m";

void validate_sw(
    std::string const& a = "AGCACACA"
  , std::string const& b = "ACACACTA"
    )
{
    std::cout << "A: " << a << "\n"
              << "B: " << b << "\n\n";

    alignment align = smith_waterman(a, b);

    boost::uint32_t p = a.size() + 1;

    // H_path is a matrix of bools that is the same size as align.H. Each cell
    // of H_path has a boolean. The cells that are in align.backpath are true,
    // and all the others are false.
    hpxla::local_matrix<bool> H_path(p, p, false); // p * p matrix

    for (boost::uint32_t x = 0; x < align.backpath.size(); ++x)
        H_path(align.backpath[x].i, align.backpath[x].j) = true;

    for (boost::uint32_t i = 0; i < p; ++i)
    {
        for (boost::uint32_t j = 0; j < p; ++j)
        {
            // Check if the current element align.H(i, j) is part of the optimal
            // alignment.
            if (H_path(i, j))
                std::cout << "\t" << yellow << align.H(i, j).get() << nocolor;
            else
                std::cout << "\t" <<           align.H(i, j).get()           ;
        }

        std::cout << "\n";
    } 

    std::cout << "\n";
}

template <typename Iterator>
bool parse_list(Iterator first, Iterator last, std::vector<boost::uint32_t>& v)
{
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::qi::_1;
    using boost::spirit::ascii::space;

    uint_parser<boost::uint32_t> size_t_;

    bool r = phrase_parse(first, last, size_t_ % ',', space, v);

    if (first != last)
        return false;

    return r;
}

int hpx_main(boost::program_options::variables_map& vm)
{
    ///////////////////////////////////////////////////////////////////////
    // Handle commandline options. 

    // Initialize the PRNG seed. 
    boost::uint32_t seed = vm["seed"].as<boost::uint32_t>();

    if (!seed)
        seed = boost::uint32_t(std::time(0));

    boost::uint32_t iterations = vm["iterations"].as<boost::uint32_t>();

    // Parse lengths.
    std::string raw_lengths = vm["lengths"].as<std::string>();

    std::vector<boost::uint32_t> lengths;

    if (!parse_list(raw_lengths.begin(), raw_lengths.end(), lengths))
        throw std::invalid_argument("--lengths argument could not be parsed\n");

    boost::random::mt19937 rng(seed);

    {
        ///////////////////////////////////////////////////////////////////////
        // Validate implementation. 
        if (vm.count("validate"))
        {
            validate_sw();
        }
 
        ///////////////////////////////////////////////////////////////////////
        // Benchmark implementation. 
    
        // Print out header rows.
        std::cout << "HPX Naive SMP Smith-Waterman Performance\n"
                  << "Sequence Length,Iterations,Total Walltime (s)\n";
    
        for (boost::uint32_t x = 0; x < lengths.size(); ++x)
            benchmark_sw(rng, lengths[x], iterations);
    }

    return hpx::finalize();
}

int main(int argc, char** argv)
{
    using namespace boost::program_options;

    variables_map vm;

    options_description cmdline("Usage: " HPX_APPLICATION_STRING " [options]");

    cmdline.add_options()
        ( "lengths"
        , value<std::string>()->default_value("32,64,128,256")
        , "sequence lengths to use (comma seperated list, maximum length "
          " currently allowed is 2^32)")

        ( "validate"
        , "run validation code before performing benchmarks")
       
        ( "iterations"
        , value<boost::uint32_t>()->default_value(1024)
        , "number of tests to perform for each sequence length")
 
        ( "seed"
        , value<boost::uint32_t>()->default_value(0)
        , "seed for the pseudo random number generator (if 0, a seed is "
          "choosen based on the current system time)")
        ;

    // Initialize and run HPX.
    return hpx::init(cmdline, argc, argv);
}

