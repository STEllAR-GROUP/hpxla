//  Copyright (c) 2012 Stephanie Crillo and Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/include/async.hpp>
#include <hpx/util/high_resolution_timer.hpp>

#include <hpxla/local_matrix.hpp>

#include <boost/format.hpp>
#include <boost/ref.hpp>
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
    hpxla::local_matrix<boost::int64_t> H;
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

boost::int64_t calc_cell(
    boost::uint32_t i
  , boost::uint32_t j
  , char ai
  , char bj
  , boost::int64_t left      // H(i, j-1)
  , boost::int64_t diagonal  // H(i-1, j-1)
  , boost::int64_t up        // H(i-1, j) 
    )
{
    boost::int64_t match_mismatch = 0;
    if (ai == bj)
    {
        match_mismatch = diagonal + match;
    } 
    else 
    {
        match_mismatch = diagonal + mismatch;
    }
    boost::int64_t deletion = up + gap;
    boost::int64_t insertion = left + gap;        
    
    boost::int64_t ij_value
        = maximum(boost::int64_t(0), match_mismatch, deletion, insertion);

    return ij_value;
}

void calc_block(
    hpxla::local_matrix_view<boost::int64_t>& H 
  , hpxla::local_matrix_view<hpx::shared_future<void> >& C // Control matrix.
  , coords start   // The start of our cell block. 
  , coords end     // The end of our cell block.
  , coords control // Our location in the control matrix.
  , std::string const& a
  , std::string const& b
    )
{
    // TODO: Handle this with hpx::wait_all?
    C(control.i,   control.j-1).get(); 
    C(control.i-1, control.j-1).get(); 
    C(control.i-1, control.j  ).get(); 

    winner local_best = H_best.load();

    // Generate scores.
    for (boost::uint32_t i = start.i; i < end.i; ++i)
    {
        for (boost::uint32_t j = start.j; j < end.j; ++j)
        {
            H(i, j) = calc_cell(i, j, a[i-1], b[j-1]
              , H(i,   j-1) // left
              , H(i-1, j-1) // diagonal 
              , H(i-1, j  ) // up
            ); 

            if (H(i, j) > local_best.value)
            {
                local_best.value = H(i, j);
                local_best.i = i;
                local_best.j = j;
            } 
        }
    }

    winner H_best_old = H_best.load(); 

    while (true)
    {
        if (local_best.value > H_best_old.value)
        {
            if (H_best.compare_exchange_weak(H_best_old, local_best))
                break;
        }
        else
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
alignment smith_waterman(
    std::string const& a
  , std::string const& b
  , boost::uint32_t grain_size
    )
{
    // Make sure that a and b have the same size (e.g. m == n), for now.
    BOOST_ASSERT(a.size() == b.size());

    if (a.size() % grain_size)
        throw std::invalid_argument(boost::str(boost::format(
            "grain size of %1% is invalid for a sequence of length %2%")
            % grain_size % a.size()));

    // j is the length of our input sequences plus one. This is number of
    // rows and columns in our square matrix. The extra, zero-filled row is
    // needed because the algorithm backtracks until it reaches a zero number.
    boost::uint32_t k = a.size() + 1; 

    // Create our matrix and fill it with zeros.
    alignment result;

    // k * k matrix
    result.H = hpxla::local_matrix<boost::int64_t>(k, k, 0); 

    // Declare a matrix view (e.g. an "alias") called H which refers to
    // result.H.
    hpxla::local_matrix_view<boost::int64_t> H = result.H.view();

    // Control matrix, for synchronizing the blocked, parallel operations.
    boost::uint32_t g = (grain_size % a.size()) + 1;
    hpxla::local_matrix<hpx::shared_future<void> > control_matrix(g, g); 

    hpxla::local_matrix_view<hpx::shared_future<void> > C = control_matrix.view();

    for (boost::uint32_t x = 0; x < g; ++x)
    {
        C(0, x) = hpx::lcos::make_ready_future();
        C(x, 0) = hpx::lcos::make_ready_future();
    }

    ///////////////////////////////////////////////////////////////////////////
    // Generate scoring matrix.

    for (boost::uint32_t i = 1; i < g; ++i)
    {
        for (boost::uint32_t j = 1; j < g; ++j)
        {
            boost::uint32_t const step = a.size() / grain_size;

            coords const start( ((i-1)*step)+1, ((j-1)*step)+1 ); 
            coords const end(   ((i)*step)+1,   ((j)*step)+1   ); 

            coords const control(i, j);

            //calc_block(H, C, start, end, control, a, b);
            C(i, j) = hpx::async(calc_block, 
                    boost::reference_wrapper<hpxla::local_matrix_view<boost::int64_t> >(H), 
                    boost::reference_wrapper<hpxla::local_matrix_view<hpx::shared_future<void> > >(C), 
                    start, end, control, a, b);
        } 
    }  

    for (boost::uint32_t i = 1; i < g; ++i)
        for (boost::uint32_t j = 1; j < g; ++j)
            C(i, j).get(); 

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
        boost::int64_t match_mismatch = H(last.i-1, last.j-1); 
        boost::int64_t insertion = H(last.i, last.j-1);
        boost::int64_t deletion = H(last.i-1, last.j);
    
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
  , boost::uint32_t seed 
  , boost::uint32_t length
  , boost::uint32_t grain_size
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
        smith_waterman(a, b, grain_size);

    double runtime = t.elapsed();

    std::cout << seed << ","
              << hpx::get_os_thread_count() << "," 
              << length << ","
              << grain_size << ","
              << iterations << ","
              << runtime << "\n";
}

std::string const nocolor = "\E[0m";
std::string const yellow  = "\E[1;33m";

void validate_sw(
    boost::uint32_t grain_size = 1
  , std::string const& a = "AGCACACA"
  , std::string const& b = "ACACACTA"
    )
{
    std::cout << "A: " << a << "\n"
              << "B: " << b << "\n"
              << "grain-size: " << grain_size << "\n\n";

    alignment align = smith_waterman(a, b, grain_size);

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
                std::cout << "\t" << yellow << align.H(i, j) << nocolor;
            else
                std::cout << "\t" <<           align.H(i, j)           ;
        }

        std::cout << "\n";
    } 

    std::cout << "\n";
}

template <typename Iterator>
bool read_list(Iterator first, Iterator last, std::vector<boost::uint32_t>& v)
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

    if (!read_list(raw_lengths.begin(), raw_lengths.end(), lengths))
        throw std::invalid_argument("--lengths argument not be parsed\n");

    // Parse grain sizes.
    std::string raw_grain_sizes = vm["grain-sizes"].as<std::string>();

    std::vector<boost::uint32_t> grain_sizes;

    if (!read_list(raw_grain_sizes.begin(), raw_grain_sizes.end(), grain_sizes))
        throw std::invalid_argument("--grain-sizes could not be parsed\n");

    boost::random::mt19937 rng(seed);

    {
        ///////////////////////////////////////////////////////////////////////
        // Validate implementation. 
        if (vm.count("validate"))
        {
            validate_sw(1);
            validate_sw(2);
        }

        ///////////////////////////////////////////////////////////////////////
        // Benchmark implementation. 
    
        // Print out header rows.
        if (!vm.count("no-header"))
            std::cout
                << "HPX Blocked SMP Smith-Waterman Performance\n"
                << "Seed,OS-Threads,Sequence Length,Grain Size,Iterations,"
                   "Total Walltime (s)\n";
    
        for (boost::uint32_t x = 0; x < lengths.size(); ++x)
            benchmark_sw(rng, seed, lengths[x], grain_sizes[x], iterations);
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

        ( "grain-sizes"
        , value<std::string>()->default_value("4,4,4,4")
        , "grain sizes to use (comma seperated list, must have the same "
          " number of elements as --lengths)")

        ( "validate"
        , "run validation code before performing benchmarks")

        ( "no-header"
        , "do not print out the CSV header for the benchmark data")
       
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

