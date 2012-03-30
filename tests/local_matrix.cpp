////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/util/lightweight_test.hpp>

#include <hpxla/local_matrix.hpp>

///  NOTE: The view() methods of local_matrix<> are tested in
/// local_matrix_view.cpp

template <
    typename Matrix
>
void test()
{
    ///////////////////////////////////////////////////////////////////////////
    // Constructors.

    { // {{{ Default ctor.
        Matrix m;

        HPX_TEST(m.empty());

        HPX_TEST_EQ(0U, m.rows());
        HPX_TEST_EQ(0U, m.columns());
    } // }}}

    { // {{{ std::vector<std::vector<> > ctor.
        // Square matrix.
        Matrix m0({ { 1, 2, 3 }
                  , { 4, 5, 6 }
                  , { 7, 8, 9 } });

        HPX_TEST(!m0.empty());

        HPX_TEST_EQ(3U, m0.rows());
        HPX_TEST_EQ(3U, m0.columns());

        HPX_TEST_EQ(m0(0, 0), 1);
        HPX_TEST_EQ(m0(0, 1), 2);
        HPX_TEST_EQ(m0(0, 2), 3);
        HPX_TEST_EQ(m0(1, 0), 4);
        HPX_TEST_EQ(m0(1, 1), 5);
        HPX_TEST_EQ(m0(1, 2), 6);
        HPX_TEST_EQ(m0(2, 0), 7);
        HPX_TEST_EQ(m0(2, 1), 8);
        HPX_TEST_EQ(m0(2, 2), 9);

        // Non-square matrix.
        Matrix m1({ { 1, 2, 3 }
                  , { 4, 5, 6 } });

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(2U, m1.rows());
        HPX_TEST_EQ(3U, m1.columns());

        HPX_TEST_EQ(m1(0, 0), 1);
        HPX_TEST_EQ(m1(0, 1), 2);
        HPX_TEST_EQ(m1(0, 2), 3);
        HPX_TEST_EQ(m1(1, 0), 4);
        HPX_TEST_EQ(m1(1, 1), 5);
        HPX_TEST_EQ(m1(1, 2), 6);
    } // }}}  
 
    { // {{{ Dimensions + initial value ctor.

    } // }}}

    { // {{{ Copy ctor.

    } // }}}

    { // {{{ Move ctor.

    } // }}}

    ///////////////////////////////////////////////////////////////////////////
    // Assignment operators.

    { // {{{ Copy assignment.

    } // }}}

    { // {{{ Move assignment.

    } // }}}

    ///////////////////////////////////////////////////////////////////////////
    // Indexing - operator().

    { // {{{ Mutable matrix indexing - A(i, j).

    } // }}}

    { // {{{ Immutable matrix indexing - A(i, j).

    } // }}}

    { // {{{ Mutable vector indexing - A(i).

    } // }}}

    { // {{{ Immutable dual indexing - A(i).

    } // }}}
 
    ///////////////////////////////////////////////////////////////////////////
    // Dimensions - rows(), columns() and empty(). 

    { // {{{ rows().

    } // }}}

    { // {{{ columns().

    } // }}}

    { // {{{ empty().

    } // }}}

    ///////////////////////////////////////////////////////////////////////////
    // Raw pointer access.

    { // {{{ Raw access and indexing.

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

