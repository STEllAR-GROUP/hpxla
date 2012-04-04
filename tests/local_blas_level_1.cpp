////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/util/lightweight_test.hpp>

#include <hpxla/local_blas.hpp>
#include <hpxla/compare_real.hpp>

using namespace hpxla::blas;

using hpxla::compare_real;

using hpxla::local_matrix;
using hpxla::local_matrix_policy;

using hpxla::policy::column_major_indexing;
using hpxla::policy::row_major_indexing;

using hpx::util::report_errors;

template <
    typename Matrix
>
void test_real()
{
    typedef typename Matrix::value_type value_type;

    ///////////////////////////////////////////////////////////////////////////
    // {{{ ASUM
    {
        Matrix x{1, 2, 3, 4, 5};

        HPX_TEST(compare_real(15.0, asum(x)));

        Matrix y{1, -2, -3, -4, 5};

        HPX_TEST(compare_real(15.0, asum(y)));
    }
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ AXPY
    {
        Matrix x{1, 2, 3, 4, 5}, y(5);

        axpy(5, x, y);

        HPX_TEST_EQ(1, x(0));
        HPX_TEST_EQ(2, x(1));
        HPX_TEST_EQ(3, x(2));
        HPX_TEST_EQ(4, x(3));
        HPX_TEST_EQ(5, x(4));

        HPX_TEST_EQ(5,  y(0));
        HPX_TEST_EQ(10, y(1));
        HPX_TEST_EQ(15, y(2));
        HPX_TEST_EQ(20, y(3));
        HPX_TEST_EQ(25, y(4));
    }
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ COPY 
    {
        Matrix x{1, 2, 3, 4, 5}, y(5);

        copy(x, y);

        HPX_TEST_EQ(1, x(0));
        HPX_TEST_EQ(2, x(1));
        HPX_TEST_EQ(3, x(2));
        HPX_TEST_EQ(4, x(3));
        HPX_TEST_EQ(5, x(4));

        HPX_TEST_EQ(1, y(0));
        HPX_TEST_EQ(2, y(1));
        HPX_TEST_EQ(3, y(2));
        HPX_TEST_EQ(4, y(3));
        HPX_TEST_EQ(5, y(4));
    }    
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ DOT
    {
        Matrix x{1, 2, 3, 4, 5};

        HPX_TEST(compare_real(55.0, dot(x, x)));
    }    
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ NRM2 
    {
        Matrix x{1, 2, 3, 4, 5};

        HPX_TEST(compare_real(std::sqrt(55.0), nrm2(x), 1e-6));
    }  
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ ROT 
    {
        Matrix w{1, 2, 3}, x{4, 5, 6}, y(w), z(x);

        /// y{c * w(0) + s * x(0), c * w(1) + s * x(1), c * w(2) + s * x(2)}
        /// z{c * x(0) - s * w(0), c * x(1) - s * w(1), c * x(2) - s * w(2)}

        value_type const c = 7;
        value_type const s = 8;

        rot(y, z, c, s); 

        HPX_TEST(compare_real(c * w(0) + s * x(0), y(0)));
        HPX_TEST(compare_real(c * w(1) + s * x(1), y(1)));
        HPX_TEST(compare_real(c * w(2) + s * x(2), y(2)));

        HPX_TEST(compare_real(c * x(0) - s * w(0), z(0)));
        HPX_TEST(compare_real(c * x(1) - s * w(1), z(1)));
        HPX_TEST(compare_real(c * x(2) - s * w(2), z(2)));
    }    
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ ROTM 
    {

    }    
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ ROTMG 
    {

    }    
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ SCAL 
    {

    }    
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ SWAP 
    {
        Matrix x{1, 2, 3, 4, 5}, y{-1, -1, -1, -1, -1};

        swap(x, y);

        HPX_TEST_EQ(-1, x(0));
        HPX_TEST_EQ(-1, x(1));
        HPX_TEST_EQ(-1, x(2));
        HPX_TEST_EQ(-1, x(3));
        HPX_TEST_EQ(-1, x(4));

        HPX_TEST_EQ(1, y(0));
        HPX_TEST_EQ(2, y(1));
        HPX_TEST_EQ(3, y(2));
        HPX_TEST_EQ(4, y(3));
        HPX_TEST_EQ(5, y(4));
    }    
    // }}}
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ IAMAX
    {
        Matrix x{1, -1, 4, -5, 0}, y{1, 1, 1, 1, 1}, z{0, 2, 1, 2, -1};

        HPX_TEST_EQ(3U, iamax(x));
        HPX_TEST_EQ(0U, iamax(y));
        HPX_TEST_EQ(1U, iamax(z));
    }    
    // }}}
}

template <
    typename Policy
>
void test_float()
{
    typedef local_matrix<float, Policy> matrix_type;
    
    ///////////////////////////////////////////////////////////////////////////
    // {{{ DSDOT
    {
        matrix_type x{1, 2, 3, 4, 5};

        HPX_TEST(compare_real(55, dsdot(x, x)));
    }    
    // }}}
}

int main()
{
    ///////////////////////////////////////////////////////////////////////////
    test_real<
        local_matrix<
            float
          , local_matrix_policy<
                column_major_indexing
            >
        >
    >();

    test_real<
        local_matrix<
            float
          , local_matrix_policy<
                row_major_indexing
            >
        >
    >();

    test_real<
        local_matrix<
            double
          , local_matrix_policy<
                column_major_indexing
            >
        >
    >();

    test_real<
        local_matrix<
            double
          , local_matrix_policy<
                row_major_indexing
            >
        >
    >();

    ///////////////////////////////////////////////////////////////////////////
    test_float<
        local_matrix_policy<
            column_major_indexing
        >
    >();

    test_float<
        local_matrix_policy<
            row_major_indexing
        >
    >();

    return report_errors();
}

