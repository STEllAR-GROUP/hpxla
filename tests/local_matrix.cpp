////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/util/lightweight_test.hpp>

#include <hpxla/local_blas.hpp>
#include <hpxla/local_matrix.hpp>

template <
    typename Matrix
>
void test()
{
    { // {{{ Default ctor.
        Matrix m;

        HPX_TEST(m.empty());

        HPX_TEST_EQ(0U, m.rows());
        HPX_TEST_EQ(0U, m.columns());
    } // }}}

    { // {{{ From std::vector<std::vector<> >.
        Matrix m({ { 1, 2, 3 }
                 , { 4, 5, 6 }
                 , { 7, 8, 9 } });

        HPX_TEST(!m.empty());

        HPX_TEST_EQ(3U, m.rows());
        HPX_TEST_EQ(3U, m.columns());

        HPX_TEST_EQ(m(0, 0), 1);
        HPX_TEST_EQ(m(0, 1), 2);
        HPX_TEST_EQ(m(0, 2), 3);
        HPX_TEST_EQ(m(1, 0), 4);
        HPX_TEST_EQ(m(1, 1), 5);
        HPX_TEST_EQ(m(1, 2), 6);
        HPX_TEST_EQ(m(2, 0), 7);
        HPX_TEST_EQ(m(2, 1), 8);
        HPX_TEST_EQ(m(2, 2), 9);
    } // }}}  
        
    { // {{{ Dimensions + initial value ctor.

    } // }}}
}

int main()
{
    test<hpxla::local_matrix<double, hpxla::column_major_index> >();
    test<hpxla::local_matrix<double, hpxla::row_major_index> >();
    test<hpxla::local_matrix<float, hpxla::column_major_index> >();
    test<hpxla::local_matrix<float, hpxla::row_major_index> >();

    return hpx::util::report_errors();
}

