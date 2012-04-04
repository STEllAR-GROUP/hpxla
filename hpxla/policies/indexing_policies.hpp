////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_951BCE80_0D7A_4AE5_85AB_2064E2E25DC3)
#define HPXLA_951BCE80_0D7A_4AE5_85AB_2064E2E25DC3

#include <hpxla/local_blas/blas_enums.hpp>
#include <hpxla/matrix_dimensions.hpp>

#include <boost/assert.hpp>

// TODO: Make sure negative offsets aren't larger than input indices.

namespace hpxla { namespace policy
{

struct column_major_indexing
{
    static boost::uint64_t index(
        boost::uint64_t row
      , boost::uint64_t col
      , matrix_bounds bounds
      , matrix_offsets offsets = matrix_offsets(0, 0)
        ) 
    {
        BOOST_ASSERT(row < bounds.rows);
        BOOST_ASSERT(col < bounds.cols);

        return (col + offsets.cols) * bounds.rows + (row + offsets.rows);
    }

    static boost::uint64_t leading_dimension(
        matrix_bounds bounds
        )
    {
        return bounds.rows;
    }

    static boost::uint64_t vector_stride(
        matrix_bounds bounds
        )
    {
        return 1;
    }

    static blas::index_order order()
    {
        return blas::column_major;
    }

    template <
        typename T
    >
    static T* compute_pointer(
        T* base
      , matrix_bounds bounds
      , matrix_offsets offsets
        )
    { 
        return base + index(0, 0, bounds, offsets);
    }
};

struct row_major_indexing
{
    static boost::uint64_t index(
        boost::uint64_t row
      , boost::uint64_t col
      , matrix_bounds bounds
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        BOOST_ASSERT(row < bounds.rows);
        BOOST_ASSERT(col < bounds.cols);

        return (row + offsets.rows) * bounds.cols + (col + offsets.cols);
    }

    static boost::uint64_t leading_dimension(
        matrix_bounds bounds
        )
    {
        return bounds.cols;
    }

    static boost::uint64_t vector_stride(
        matrix_bounds bounds
        )
    {
        return bounds.cols;
    }

    static blas::index_order order()
    {
        return blas::row_major;
    }

    template <
        typename T
    >
    static T* compute_pointer(
        T* base
      , matrix_bounds bounds
      , matrix_offsets offsets
        )
    { 
        return base + index(0, 0, bounds, offsets);
    }
};

}}

#endif // HPXLA_951BCE80_0D7A_4AE5_85AB_2064E2E25DC3

