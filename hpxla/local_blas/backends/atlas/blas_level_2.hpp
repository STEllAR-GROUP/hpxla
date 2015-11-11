////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_A891B2EE_B6A4_4F1C_94DE_D652FE57EE0A)
#define HPXLA_A891B2EE_B6A4_4F1C_94DE_D652FE57EE0A

#include <hpxla/local_matrix_view.hpp>
#include <hpxla/local_blas/blas_enums.hpp>
#include <hpxla/compare_real.hpp>

#include <complex>

extern "C"
{
    #include <cblas.h>
}

// NOTE: ATM, only implemented for general matrices.
// TODO: std::vector overloads.

namespace hpxla { namespace blas
{

///////////////////////////////////////////////////////////////////////////////
// {{{ GEMV

/// BLAS2: Computes a matrix-vector product using a general matrix.
template <
    typename Policy
>
inline void gemv(
    local_matrix_view<float, Policy> const& A
  , local_matrix_view<float, Policy> const& X
  , local_matrix_view<float, Policy>& Y
  , float alpha = 1.0
  , float beta = 0.0
  , transpose_operation trans = no_transpose
    )
{
    typedef local_matrix_view<float, Policy> matrix_type;

    std::size_t const m = A.rows();
    std::size_t const n = A.columns();
 
    ///////////////////////////////////////////////////////////////////////////
    // Check A.
    BOOST_ASSERT(!A.empty());

    ///////////////////////////////////////////////////////////////////////////
    // Check Y.
    if (!compare_real(0.0f, beta))
    {
        BOOST_ASSERT(!Y.empty());

        if (no_transpose == trans)
            BOOST_ASSERT(m == Y.rows());
        else
            BOOST_ASSERT(n == Y.rows());
    }

    else
    {
        if (no_transpose == trans)
        {
            if (m != Y.rows())
                Y = boost::move(matrix_type(m));
        }

        else if (n != Y.rows())
            Y = boost::move(matrix_type(n));
    }
   
    ///////////////////////////////////////////////////////////////////////////
    // Check X. 
    BOOST_ASSERT(!X.empty());

    if (no_transpose == trans)
        BOOST_ASSERT(n == X.rows());
    else
        BOOST_ASSERT(m == X.rows());

    ///////////////////////////////////////////////////////////////////////////
    ::cblas_sgemv(CBLAS_ORDER(A.index_order()), CBLAS_TRANSPOSE(trans), m, n
                , alpha
                , A.data(), A.leading_dimension()
                , X.data(), X.vector_stride()
                , beta
                , Y.data(), Y.vector_stride());
} 

/// BLAS2: Computes a matrix-vector product using a general matrix.
template <
    typename Policy
>
inline void gemv(
    local_matrix_view<std::complex<float>, Policy> const& A
  , local_matrix_view<std::complex<float>, Policy> const& X
  , local_matrix_view<std::complex<float>, Policy>& Y
  , std::complex<float> alpha = 1.0
  , std::complex<float> beta = 0.0
  , transpose_operation trans = no_transpose
    )
{
    typedef local_matrix_view<std::complex<float>, Policy> matrix_type;

    std::size_t const m = A.rows();
    std::size_t const n = A.columns();
 
    ///////////////////////////////////////////////////////////////////////////
    // Check A.
    BOOST_ASSERT(!A.empty());

    ///////////////////////////////////////////////////////////////////////////
    // Check Y. 
    if (!(  compare_real(0.0f, beta.real())
         && compare_real(0.0f, beta.imag())))
    {
        BOOST_ASSERT(!Y.empty());

        if (no_transpose == trans)
            BOOST_ASSERT(m == Y.rows());
        else
            BOOST_ASSERT(n == Y.rows());
    }

    else
    {
        if (no_transpose == trans)
        {
            if (m != Y.rows())
                Y = boost::move(matrix_type(m)); 
        }

        else if (n != Y.rows())
            Y = boost::move(matrix_type(n)); 
    }
   
    ///////////////////////////////////////////////////////////////////////////
    // Check X. 
    BOOST_ASSERT(!X.empty());

    if (no_transpose == trans)
        BOOST_ASSERT(n == X.rows());
    else
        BOOST_ASSERT(m == X.rows());

    ///////////////////////////////////////////////////////////////////////////
    ::cblas_cgemv(CBLAS_ORDER(A.index_order()), CBLAS_TRANSPOSE(trans), m, n
                , (void const*) &alpha
                , (void const*) A.data(), A.leading_dimension()
                , (void const*) X.data(), X.vector_stride()
                , (void const*) &beta
                , (void*)       Y.data(), Y.vector_stride());
} 

/// BLAS2: Computes a matrix-vector product using a general matrix.
template <
    typename Policy
>
inline void gemv(
    local_matrix_view<double, Policy> const& A
  , local_matrix_view<double, Policy> const& X
  , local_matrix_view<double, Policy>& Y
  , double alpha = 1.0
  , double beta = 0.0
  , transpose_operation trans = no_transpose
    )
{
    typedef local_matrix_view<double, Policy> matrix_type;

    std::size_t const m = A.rows();
    std::size_t const n = A.columns();
 
    ///////////////////////////////////////////////////////////////////////////
    // Check A.
    BOOST_ASSERT(!A.empty());

    ///////////////////////////////////////////////////////////////////////////
    // Check Y. 
    if (!compare_real(0.0, beta))
    {
        BOOST_ASSERT(!Y.empty());

        if (no_transpose == trans)
            BOOST_ASSERT(m == Y.rows());
        else
            BOOST_ASSERT(n == Y.rows());
    }

    else
    {
        if (no_transpose == trans)
        {
            if (m != Y.rows())
                Y = boost::move(matrix_type(m)); 
        }

        else if (n != Y.rows())
            Y = boost::move(matrix_type(n)); 
    }
   
    ///////////////////////////////////////////////////////////////////////////
    // Check X. 
    BOOST_ASSERT(!X.empty());

    if (no_transpose == trans)
        BOOST_ASSERT(n == X.rows());
    else
        BOOST_ASSERT(m == X.rows());

    ///////////////////////////////////////////////////////////////////////////
    ::cblas_dgemv(CBLAS_ORDER(A.index_order()), CBLAS_TRANSPOSE(trans), m, n
                , alpha
                , A.data(), A.leading_dimension()
                , X.data(), X.vector_stride()
                , beta
                , Y.data(), Y.vector_stride());
} 

/// BLAS2: Computes a matrix-vector product using a general matrix.
template <
    typename Policy
>
inline void gemv(
    local_matrix_view<std::complex<double>, Policy> const& A
  , local_matrix_view<std::complex<double>, Policy> const& X
  , local_matrix_view<std::complex<double>, Policy>& Y
  , std::complex<double> alpha = 1.0
  , std::complex<double> beta = 0.0
  , transpose_operation trans = no_transpose
    )
{
    typedef local_matrix_view<std::complex<double>, Policy> matrix_type;

    std::size_t const m = A.rows();
    std::size_t const n = A.columns();
 
    ///////////////////////////////////////////////////////////////////////////
    // Check A.
    BOOST_ASSERT(!A.empty());

    ///////////////////////////////////////////////////////////////////////////
    // Check Y. 
    if (!(  compare_real(0.0, beta.real())
         && compare_real(0.0, beta.imag())))
    {
        BOOST_ASSERT(!Y.empty());

        if (no_transpose == trans)
            BOOST_ASSERT(m == Y.rows());
        else
            BOOST_ASSERT(n == Y.rows());
    }

    else
    {
        if (no_transpose == trans)
        {
            if (m != Y.rows())
                Y = boost::move(matrix_type(m)); 
        }

        else if (n != Y.rows())
            Y = boost::move(matrix_type(n)); 
    }
   
    ///////////////////////////////////////////////////////////////////////////
    // Check X. 
    BOOST_ASSERT(!X.empty());

    if (no_transpose == trans)
        BOOST_ASSERT(n == X.rows());
    else
        BOOST_ASSERT(m == X.rows());

    ///////////////////////////////////////////////////////////////////////////
    ::cblas_zgemv(CBLAS_ORDER(A.index_order()), CBLAS_TRANSPOSE(trans), m, n
                , (void const*) &alpha
                , (void const*) A.data(), A.leading_dimension()
                , (void const*) X.data(), X.vector_stride()
                , (void const*) &beta
                , (void*)       Y.data(), Y.vector_stride());
} 

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ GER

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ GERC

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ GERU

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ HEMV

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ HER

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ HER2

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SYMV

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SYR

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SYR2

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ TRMV

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ TRSV

// }}}
 
}}

#endif // HPXLA_A891B2EE_B6A4_4F1C_94DE_D652FE57EE0A

