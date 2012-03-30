////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84)
#define HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84

#include <hpxla/local_blas/blas_order.hpp>

#include <boost/fusion/include/define_struct.hpp>

BOOST_FUSION_DEFINE_STRUCT(
    (hpxla), matrix_dimensions,
    (std::size_t, rows)
    (std::size_t, cols));

namespace hpxla
{

struct column_major_index
{
    static std::size_t index(
        std::size_t row
      , std::size_t col
      , matrix_dimensions bounds
      , matrix_dimensions offsets = matrix_dimensions(0, 0)
        ) 
    {
        BOOST_ASSERT(row < bounds.rows);
        BOOST_ASSERT(col < bounds.cols);

        return (col + offsets.cols) * bounds.rows + (row + offsets.rows);
    }

    static std::size_t leading_dimension(
        matrix_dimensions bounds
        )
    {
        return bounds.rows;
    }

    static blas::index_order order()
    {
        return HPXLA_COLUMN_MAJOR_ORDER;
    }

    template <
        typename T
    >
    static T* compute_pointer(
        T* base
      , matrix_dimensions bounds
      , matrix_dimensions offsets
        )
    { 
        return base + index(0, 0, bounds, offsets);
    }
};

struct row_major_index
{
    static std::size_t index(
        std::size_t row
      , std::size_t col
      , matrix_dimensions bounds
      , matrix_dimensions offsets = matrix_dimensions(0, 0)
        ) const
    {
        BOOST_ASSERT(row < bounds.rows);
        BOOST_ASSERT(col < bounds.cols);

        return (row + offsets.rows) * bounds.cols + (col + offsets.cols);
    }

    static std::size_t leading_dimension(
        matrix_dimensions bounds
        )
    {
        return bounds.cols;
    }

    static blas::index_order order()
    {
        return HPXLA_ROW_MAJOR_ORDER;
    }

    template <
        typename T
    >
    static T* compute_pointer(
        T* base
      , matrix_dimensions bounds
      , matrix_dimensions offsets
        )
    { 
        return base + index(0, 0, bounds, offsets);
    }
};

template <
    typename T
  , typename Index = column_major_index 
>
struct local_matrix_view;

template <
    typename T
  , typename Index = column_major_index 
>
struct local_matrix;

}

#endif // HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84

