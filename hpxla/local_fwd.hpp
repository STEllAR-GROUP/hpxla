////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84)
#define HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84

#include <boost/fusion/include/define_struct.hpp>

BOOST_FUSION_DEFINE_STRUCT(
    (hpxla), matrix_dimensions,
    (std::size_t, rows)
    (std::size_t, cols));

namespace hpxla
{

struct column_major_index
{
    typedef std::size_t result_type;

    std::size_t operator()(
        std::size_t row
      , std::size_t col
      , matrix_dimensions bounds
      , matrix_dimensions offsets = matrix_dimensions(0, 0)
        ) const
    {
        BOOST_ASSERT(row < bounds.rows);
        BOOST_ASSERT(col < bounds.cols);

        return (col + offsets.cols) * bounds.rows + (row + offsets.rows);
    }
};

struct row_major_index
{
    typedef std::size_t result_type;

    std::size_t operator()(
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

