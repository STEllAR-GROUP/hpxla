//  Copyright (c) 2012 Stephanie Crillo and Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

#if defined(BOOST_ENABLE_ASSERT_HANDLER)
    #undef BOOST_ENABLE_ASSERT_HANDLER
#endif

#include <hpx/util/high_resolution_timer.hpp>

#include <boost/assert.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/program_options.hpp>
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
//  
// Note that std::size_t is an unsigned integer type used for holding sizes of
// std::vectors and std::strings.
//
// Also, H(i, j) == H[i][j].

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
    coords(int i_, int j_) : i(i_), j(j_) {}

    int i;
    int j;
};

std::ostream& operator<<(std::ostream& out, coords const& c)
{
    out << "(" << c.i << "," << c.j << ")"; 
    return out; 
}

///////////////////////////////////////////////////////////////////////////////
struct alignment
{ 
    std::vector<std::vector<int> > H;
    std::vector<coords> backpath;
};

///////////////////////////////////////////////////////////////////////////////
alignment smith_waterman(std::string const& a, std::string const& b)
{
    // Make sure that a and b have the same size (e.g. m == n), for now.
    assert(a.size() == b.size());

    // j is the length of our input sequences plus one. This is number of
    // rows and columns in our square matrix. The extra, zero-filled row is
    // needed because the algorithm backtracks until it reaches a zero number.
    std::size_t k = a.size() + 1; 

    // Create our matrix and fill it with zeros.
    alignment result;
    result.H.resize(k, std::vector<int>(k, 0));

    // Declare a reference variable (e.g. an "alias") called H which refers to
    // result.H.
    std::vector<std::vector<int> >& H = result.H;

    ///////////////////////////////////////////////////////////////////////////
    // Generate scoring matrix.
    int H_max = 0;
    int i_max = 0;
    int j_max = 0;

    for (std::size_t i = 1; i < k; ++i)
    {
        for (std::size_t j = 1; j < k; ++j)
        {
            int match_mismatch = 0;
            if (a[i-1] == b[j-1])
            {
                match_mismatch = H[i-1][j-1] + match;
            } 
            else 
            {
                match_mismatch = H[i-1][j-1] + mismatch;
            }
            int deletion = H[i-1][j] + gap;
            int insertion = H[i][j-1] + gap;        
            H[i][j] = maximum(0, match_mismatch, deletion, insertion);

            if (H[i][j] > H_max)
            {
                H_max = H[i][j];
                i_max = i;
                j_max = j; 
            }
        } 
    }  

    ///////////////////////////////////////////////////////////////////////////
    // Backtracking.

    // 0.) Make a vector to hold coords.
    // 1.) We want to start at H_max, or the coordinate of H_max, so
    //     (i_max, j_max).
    // 2.) Then, determine which value is largest (where i is initially i_max,
    //     and j is initially j_max):
    //        (i-1, j-1) for match/mismatch,
    //        (i-1, j)   for an insertion, and
    //        (i, j-1)   for a deletion. 
    // 3.) Reset the current i and j coords to equal next i and j coords. 
    
    std::vector<coords>& backpath = result.backpath;
    backpath.push_back(coords(i_max, j_max)); 

    while (true)
    {
        coords last = backpath.back();
        int match_mismatch = H[last.i-1][last.j-1]; 
        int insertion = H[last.i][last.j-1];
        int deletion = H[last.i-1][last.j];
    
        int m = maximum(match_mismatch, insertion, deletion);    
    
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
  , std::size_t length
  , std::size_t iterations = 1 << 10
    )
{ 
    std::string const chars("ATGC");
  
    boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);

    ///////////////////////////////////////////////////////////////////////////
    // Generate our sequences using the mt19937 random number generator.
    std::string a, b;

    for (std::size_t x = 0; x < length; ++x)
    {
        a += chars[index_dist(rng)];
        b += chars[index_dist(rng)];
    }

    ///////////////////////////////////////////////////////////////////////////
    // Generate our sequences using the mt19937 random number generator.
    hpx::util::high_resolution_timer t;

    for (std::size_t x = 0; x < iterations; ++x)
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

    std::size_t p = a.size() + 1;

    // H_path is a matrix of bools that is the same size as align.H. Each cell
    // of H_path has a boolean. The cells that are in align.backpath are true,
    // and all the others are false.
    std::vector<std::vector<bool> > H_path(p, std::vector<bool>(p));

    for (std::size_t x = 0; x < align.backpath.size(); ++x)
        H_path[align.backpath[x].i][align.backpath[x].j] = true;

    for (std::size_t i = 0; i < p; ++i)
    {
        for (std::size_t j = 0; j < p; ++j)
        {
            // Check if the current element align.H[i][j] is part of the optimal
            // alignment.
            if (H_path[i][j])
                std::cout << "\t" << yellow << align.H[i][j] << nocolor;
            else
                std::cout << "\t" <<           align.H[i][j]           ;
        }

        std::cout << "\n";
    } 

    std::cout << "\n";
}

template <typename Iterator>
bool parse_list(Iterator first, Iterator last, std::vector<std::size_t>& v)
{
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::qi::_1;
    using boost::spirit::ascii::space;

    uint_parser<std::size_t> size_t_;

    bool r = phrase_parse(first, last, size_t_ % ',', space, v);

    if (first != last)
        return false;

    return r;
}

int app_main(boost::program_options::variables_map& vm)
{
    ///////////////////////////////////////////////////////////////////////
    // Handle commandline options. 

    // Initialize the PRNG seed. 
    boost::uint32_t seed = vm["seed"].as<boost::uint32_t>();

    if (!seed)
        seed = boost::uint32_t(std::time(0));

    std::size_t iterations = vm["iterations"].as<std::size_t>();

    // Parse lengths.
    std::string raw_lengths = vm["lengths"].as<std::string>();

    std::vector<std::size_t> lengths;

    if (!parse_list(raw_lengths.begin(), raw_lengths.end(), lengths))
        throw std::invalid_argument("--lengths argument could not be parsed\n");

    boost::random::mt19937 rng(seed);

    ///////////////////////////////////////////////////////////////////////
    // Validate implementation. 
    if (vm.count("validate"))
    {
        validate_sw();
    }

    ///////////////////////////////////////////////////////////////////////
    // Benchmark implementation. 

    // Print out header rows.
    std::cout << "HPX Serial Smith-Waterman Performance\n"
              << "Sequence Length,Iterations,Total Walltime (s)\n";

    for (std::size_t x = 0; x < lengths.size(); ++x)
        benchmark_sw(rng, lengths[x], iterations);

    return 0;
}

int main(int argc, char** argv)
{
    using namespace boost::program_options;

    ///////////////////////////////////////////////////////////////////////////
    // Parse command line.
    variables_map vm;

    options_description cmdline("Usage: " HPX_APPLICATION_STRING " [options]");

    cmdline.add_options()
        ( "help,h"
        , "print out program usage (this message)")

        ( "lengths"
        , value<std::string>()->default_value("32,64,128,256")
        , "sequence lengths to use (comma seperated list)")

        ( "validate"
        , "run validation code before performing benchmarks")
       
        ( "iterations"
        , value<std::size_t>()->default_value(1024)
        , "number of tests to perform for each sequence length")
 
        ( "seed"
        , value<boost::uint32_t>()->default_value(0)
        , "seed for the pseudo random number generator (if 0, a seed is "
          "choosen based on the current system time)")
        ;

    store(command_line_parser(argc, argv).options(cmdline).run(), vm);

    notify(vm);

    // Print help screen.
    if (vm.count("help"))
    {
        std::cout << cmdline;
        return 0;
    }

    return app_main(vm);
}

