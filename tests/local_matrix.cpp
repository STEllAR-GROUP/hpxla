////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/util/lightweight_test.hpp>

#include <hpxla/local_matrix.hpp>

// NOTE: The view() method of local_matrix<> is tested in local_matrix_view.cpp.
// The order() and leading_dimension() methods are tested in the local BLAS
// tests.

using hpxla::local_matrix;
using hpxla::local_matrix_policy;
using hpxla::matrix_bounds;

using hpxla::policy::column_major_indexing;
using hpxla::policy::row_major_indexing;

using hpx::util::report_errors;

template <
    typename Matrix
>
void test()
{
    ///////////////////////////////////////////////////////////////////////////
    // Constructors.

    { // {{{ Default ctor.
        Matrix m0;

        HPX_TEST(m0.empty());

        HPX_TEST_EQ(0U, m0.rows());
        HPX_TEST_EQ(0U, m0.columns());
    } // }}}

    { // {{{ std::vector<std::vector<> > ctor.
        // Brackets in parenthesis. 
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

        // Brackets. 
        Matrix m1{ { 1, 2, 3 }
                 , { 4, 5, 6 }
                 , { 7, 8, 9 } };

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(3U, m1.rows());
        HPX_TEST_EQ(3U, m1.columns());

        HPX_TEST_EQ(m1(0, 0), 1);
        HPX_TEST_EQ(m1(0, 1), 2);
        HPX_TEST_EQ(m1(0, 2), 3);
        HPX_TEST_EQ(m1(1, 0), 4);
        HPX_TEST_EQ(m1(1, 1), 5);
        HPX_TEST_EQ(m1(1, 2), 6);
        HPX_TEST_EQ(m1(2, 0), 7);
        HPX_TEST_EQ(m1(2, 1), 8);
        HPX_TEST_EQ(m1(2, 2), 9);

        // Brackets assignment. 
        Matrix m2 = { { 1, 2, 3 }
                    , { 4, 5, 6 }
                    , { 7, 8, 9 } };

        HPX_TEST(!m2.empty());

        HPX_TEST_EQ(3U, m2.rows());
        HPX_TEST_EQ(3U, m2.columns());

        HPX_TEST_EQ(m2(0, 0), 1);
        HPX_TEST_EQ(m2(0, 1), 2);
        HPX_TEST_EQ(m2(0, 2), 3);
        HPX_TEST_EQ(m2(1, 0), 4);
        HPX_TEST_EQ(m2(1, 1), 5);
        HPX_TEST_EQ(m2(1, 2), 6);
        HPX_TEST_EQ(m2(2, 0), 7);
        HPX_TEST_EQ(m2(2, 1), 8);
        HPX_TEST_EQ(m2(2, 2), 9);

        // Non-square matrix.
        Matrix m3({ { 1, 2, 3 }
                  , { 4, 5, 6 } });

        HPX_TEST(!m3.empty());

        HPX_TEST_EQ(2U, m3.rows());
        HPX_TEST_EQ(3U, m3.columns());

        HPX_TEST_EQ(m3(0, 0), 1);
        HPX_TEST_EQ(m3(0, 1), 2);
        HPX_TEST_EQ(m3(0, 2), 3);
        HPX_TEST_EQ(m3(1, 0), 4);
        HPX_TEST_EQ(m3(1, 1), 5);
        HPX_TEST_EQ(m3(1, 2), 6);

        // 1 x n matrix. Note that the extra set of brackets distinguish this
        // ctor from the std::vector<> ctor.
        Matrix m4({ { 1, 2, 3 } });

        HPX_TEST(!m4.empty());

        HPX_TEST_EQ(1U, m4.rows());
        HPX_TEST_EQ(3U, m4.columns());

        HPX_TEST_EQ(m4(0, 0), 1);
        HPX_TEST_EQ(m4(0, 1), 2);
        HPX_TEST_EQ(m4(0, 2), 3);
    } // }}}  

    { // {{{ std::vector<> ctor.
        // Brackets in parenthesis. 
        Matrix m0({ 1, 2, 3 });

        HPX_TEST(!m0.empty());

        HPX_TEST_EQ(3U, m0.rows());
        HPX_TEST_EQ(1U, m0.columns());

        HPX_TEST_EQ(m0(0, 0), 1);
        HPX_TEST_EQ(m0(1, 0), 2);
        HPX_TEST_EQ(m0(2, 0), 3);

        // Brackets. 
        Matrix m1{ 1, 2, 3 };

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(3U, m1.rows());
        HPX_TEST_EQ(1U, m1.columns());

        HPX_TEST_EQ(m1(0, 0), 1);
        HPX_TEST_EQ(m1(1, 0), 2);
        HPX_TEST_EQ(m1(2, 0), 3);

        // Brackets assignment. 
        Matrix m2 = { 1, 2, 3 };

        HPX_TEST(!m2.empty());

        HPX_TEST_EQ(3U, m2.rows());
        HPX_TEST_EQ(1U, m2.columns());

        HPX_TEST_EQ(m2(0, 0), 1);
        HPX_TEST_EQ(m2(1, 0), 2);
        HPX_TEST_EQ(m2(2, 0), 3);
    } // }}}  
 
    { // {{{ Dimensions + initial value ctor.
        // Rows only (n x 1 matrix).
        Matrix m0(2);

        HPX_TEST(!m0.empty());

        HPX_TEST_EQ(2U, m0.rows());
        HPX_TEST_EQ(1U, m0.columns()); 

        HPX_TEST_EQ(m0(0, 0), 0);
        HPX_TEST_EQ(m0(1, 0), 0);

        // Rows and columns (n x m matrix).
        Matrix m1(2, 3);

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(2U, m1.rows());
        HPX_TEST_EQ(3U, m1.columns()); 

        HPX_TEST_EQ(m1(0, 0), 0);
        HPX_TEST_EQ(m1(1, 0), 0);
        HPX_TEST_EQ(m1(0, 1), 0);
        HPX_TEST_EQ(m1(1, 1), 0);
        HPX_TEST_EQ(m1(0, 2), 0);
        HPX_TEST_EQ(m1(1, 2), 0);

        // Rows and columns (n x m matrix) with non-default initializer
        Matrix m2(2, 2, 1);

        HPX_TEST(!m2.empty());

        HPX_TEST_EQ(2U, m2.rows());
        HPX_TEST_EQ(2U, m2.columns()); 

        HPX_TEST_EQ(m2(0, 0), 1);
        HPX_TEST_EQ(m2(1, 0), 1);
        HPX_TEST_EQ(m2(0, 1), 1);
        HPX_TEST_EQ(m2(1, 1), 1);
    } // }}}

    { // {{{ Copy ctor.
        Matrix m0{ { 17, 42 }
                 , { 42, 17 } };

        HPX_SANITY(!m0.empty());

        HPX_SANITY_EQ(2U, m0.rows());
        HPX_SANITY_EQ(2U, m0.columns());

        HPX_SANITY_EQ(m0(0, 0), 17);
        HPX_SANITY_EQ(m0(1, 0), 42);
        HPX_SANITY_EQ(m0(0, 1), 42);
        HPX_SANITY_EQ(m0(1, 1), 17);

        Matrix m1(m0);

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(2U, m1.rows());
        HPX_TEST_EQ(2U, m1.columns());

        HPX_TEST_EQ(m1(0, 0), 17);
        HPX_TEST_EQ(m1(1, 0), 42);
        HPX_TEST_EQ(m1(0, 1), 42);
        HPX_TEST_EQ(m1(1, 1), 17);

        // Try mutating the copy - this should not affect the original.
        m1(0, 0) = 42;
        m1(1, 0) = 17;
        m1(0, 1) = 17;
        m1(1, 1) = 42;

        HPX_TEST_EQ(m1(0, 0), 42);
        HPX_TEST_EQ(m1(1, 0), 17);
        HPX_TEST_EQ(m1(0, 1), 17);
        HPX_TEST_EQ(m1(1, 1), 42);

        HPX_TEST_EQ(m0(0, 0), 17);
        HPX_TEST_EQ(m0(1, 0), 42);
        HPX_TEST_EQ(m0(0, 1), 42);
        HPX_TEST_EQ(m0(1, 1), 17);
    } // }}}

    { // {{{ Move ctor.
        Matrix m0{ { 17, 42 }
                 , { 42, 17 } };

        HPX_SANITY(!m0.empty());

        HPX_SANITY_EQ(2U, m0.rows());
        HPX_SANITY_EQ(2U, m0.columns());

        HPX_SANITY_EQ(m0(0, 0), 17);
        HPX_SANITY_EQ(m0(1, 0), 42);
        HPX_SANITY_EQ(m0(0, 1), 42);
        HPX_SANITY_EQ(m0(1, 1), 17);

        Matrix m1(boost::move(m0));

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(2U, m1.rows());
        HPX_TEST_EQ(2U, m1.columns());

        HPX_TEST_EQ(m1(0, 0), 17);
        HPX_TEST_EQ(m1(1, 0), 42);
        HPX_TEST_EQ(m1(0, 1), 42);
        HPX_TEST_EQ(m1(1, 1), 17);

        // Make sure the original is now empty.
        HPX_TEST(m0.empty());

        HPX_TEST_EQ(0U, m0.rows());
        HPX_TEST_EQ(0U, m0.columns());
    } // }}}

    ///////////////////////////////////////////////////////////////////////////
    // Assignment operators.

    { // {{{ Copy assignment.
        Matrix m0{ { 17, 42 }
                 , { 42, 17 } };

        HPX_SANITY(!m0.empty());

        HPX_SANITY_EQ(2U, m0.rows());
        HPX_SANITY_EQ(2U, m0.columns());

        HPX_SANITY_EQ(m0(0, 0), 17);
        HPX_SANITY_EQ(m0(1, 0), 42);
        HPX_SANITY_EQ(m0(0, 1), 42);
        HPX_SANITY_EQ(m0(1, 1), 17);

        Matrix m1;

        HPX_SANITY(m1.empty());

        HPX_SANITY_EQ(0U, m1.rows());
        HPX_SANITY_EQ(0U, m1.columns());

        m1 = m0;

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(2U, m1.rows());
        HPX_TEST_EQ(2U, m1.columns());

        HPX_TEST_EQ(m1(0, 0), 17);
        HPX_TEST_EQ(m1(1, 0), 42);
        HPX_TEST_EQ(m1(0, 1), 42);
        HPX_TEST_EQ(m1(1, 1), 17);

        // Try mutating the copy - this should not affect the original.
        m1(0, 0) = 42;
        m1(1, 0) = 17;
        m1(0, 1) = 17;
        m1(1, 1) = 42;

        HPX_TEST_EQ(m1(0, 0), 42);
        HPX_TEST_EQ(m1(1, 0), 17);
        HPX_TEST_EQ(m1(0, 1), 17);
        HPX_TEST_EQ(m1(1, 1), 42);

        HPX_TEST_EQ(m0(0, 0), 17);
        HPX_TEST_EQ(m0(1, 0), 42);
        HPX_TEST_EQ(m0(0, 1), 42);
        HPX_TEST_EQ(m0(1, 1), 17);

    } // }}}

    { // {{{ Move assignment.
        Matrix m0{ { 17, 42 }
                 , { 42, 17 } };

        HPX_SANITY(!m0.empty());

        HPX_SANITY_EQ(2U, m0.rows());
        HPX_SANITY_EQ(2U, m0.columns());

        HPX_SANITY_EQ(m0(0, 0), 17);
        HPX_SANITY_EQ(m0(1, 0), 42);
        HPX_SANITY_EQ(m0(0, 1), 42);
        HPX_SANITY_EQ(m0(1, 1), 17);

        Matrix m1;

        HPX_SANITY(m1.empty());

        HPX_SANITY_EQ(0U, m1.rows());
        HPX_SANITY_EQ(0U, m1.columns());

        m1 = boost::move(m0);

        HPX_TEST(!m1.empty());

        HPX_TEST_EQ(2U, m1.rows());
        HPX_TEST_EQ(2U, m1.columns());

        HPX_TEST_EQ(m1(0, 0), 17);
        HPX_TEST_EQ(m1(1, 0), 42);
        HPX_TEST_EQ(m1(0, 1), 42);
        HPX_TEST_EQ(m1(1, 1), 17);

        // Make sure the original is now empty.
        HPX_TEST(m0.empty());

        HPX_TEST_EQ(0U, m0.rows());
        HPX_TEST_EQ(0U, m0.columns());

    } // }}}

    ///////////////////////////////////////////////////////////////////////////

    { // {{{ Constness 
        Matrix const m0{ { 17, 42 }
                       , { 42, 17 } };

        HPX_TEST(!m0.empty());

        HPX_TEST_EQ(2U, m0.rows());
        HPX_TEST_EQ(2U, m0.columns());

        HPX_TEST_EQ(m0(0, 0), 17);
        HPX_TEST_EQ(m0(1, 0), 42);
        HPX_TEST_EQ(m0(0, 1), 42);
        HPX_TEST_EQ(m0(1, 1), 17);
    } // }}}

    ///////////////////////////////////////////////////////////////////////////

    { // {{{ Vector indexing. 
        // Brackets. 
        Matrix m0{ 1, 2, 3 };

        HPX_TEST(!m0.empty());

        HPX_TEST_EQ(3U, m0.rows());
        HPX_TEST_EQ(1U, m0.columns());

        HPX_TEST_EQ(m0(0), 1);
        HPX_TEST_EQ(m0(1), 2);
        HPX_TEST_EQ(m0(2), 3);
    } // }}}
 
    ///////////////////////////////////////////////////////////////////////////

    { // {{{ Raw access and indexing.
        typedef typename Matrix::pointer pointer;
        typedef typename Matrix::indexing_policy_type indexer;

        Matrix m0{ { 1, 2, 3 }
                 , { 4, 5, 6 } };

        HPX_SANITY(!m0.empty());

        HPX_SANITY_EQ(2U, m0.rows());
        HPX_SANITY_EQ(3U, m0.columns());

        HPX_SANITY_EQ(m0(0, 0), 1);
        HPX_SANITY_EQ(m0(0, 1), 2);
        HPX_SANITY_EQ(m0(0, 2), 3);
        HPX_SANITY_EQ(m0(1, 0), 4);
        HPX_SANITY_EQ(m0(1, 1), 5);
        HPX_SANITY_EQ(m0(1, 2), 6);

        matrix_bounds bounds(2, 3);

        pointer p0 = m0.data();

        HPX_TEST_EQ(p0[indexer::index(0, 0, bounds)], 1); 
        HPX_TEST_EQ(p0[indexer::index(0, 1, bounds)], 2); 
        HPX_TEST_EQ(p0[indexer::index(0, 2, bounds)], 3); 
        HPX_TEST_EQ(p0[indexer::index(1, 0, bounds)], 4); 
        HPX_TEST_EQ(p0[indexer::index(1, 1, bounds)], 5); 
        HPX_TEST_EQ(p0[indexer::index(1, 2, bounds)], 6); 

        p0[indexer::index(1, 2, bounds)] = 7;

        HPX_TEST_EQ(m0(1, 2), 7);
        HPX_TEST_EQ(p0[indexer::index(1, 2, bounds)], 7); 
    } // }}} 
}

int main()
{
    ///////////////////////////////////////////////////////////////////////////
    test<
        local_matrix<
            float
          , local_matrix_policy<
                column_major_indexing
            >
        >
    >();

    test<
        local_matrix<
            float
          , local_matrix_policy<
                row_major_indexing
            >
        >
    >();

    test<
        local_matrix<
            double
          , local_matrix_policy<
                column_major_indexing
            >
        >
    >();

    test<
        local_matrix<
            double
          , local_matrix_policy<
                row_major_indexing
            >
        >
    >();

    return report_errors();
}

