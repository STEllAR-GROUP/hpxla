////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_AA7B5EF8_9E19_4F28_B48C_EB9DC2512EA0)
#define HPXLA_AA7B5EF8_9E19_4F28_B48C_EB9DC2512EA0

#include <hpxla/local_matrix_view.hpp>

#include <boost/array.hpp>

#include <complex>

#include <cblas.h>

// TODO: std::vector overloads.

namespace hpxla { namespace blas
{

///////////////////////////////////////////////////////////////////////////////
// {{{ ASUM

/// BLAS1: Computes the sum of magnitudes of the vector elements.
template <
    typename Policy
>
inline float asum(
    local_matrix_view<float, Policy> const& X
    )
{
    return ::cblas_sasum(X.rows(), X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
template <
    typename Policy
>
inline float asum(
    local_matrix_view<std::complex<float>, Policy> const& X
    )
{
    return ::cblas_scasum(X.rows(), (void const*) X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
template <
    typename Policy
>
inline double asum(
    local_matrix_view<double, Policy> const& X
    )
{
    return ::cblas_dasum(X.rows(), X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
template <
    typename Policy
>
inline double asum(
    local_matrix_view<std::complex<double>, Policy> const& X
    )
{
    return ::cblas_dzasum(X.rows(), (void const*) X.data(), X.vector_stride()); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ AXPY

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
template <
    typename Policy
>
inline void axpy(
    float a
  , local_matrix_view<float, Policy> const& X
  , local_matrix_view<float, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_saxpy(X.rows(), a, X.data(), X.vector_stride()
                             , Y.data(), Y.vector_stride());
}

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
template <
    typename Policy
>
inline void axpy(
    std::complex<float> a
  , local_matrix_view<std::complex<float>, Policy> const& X
  , local_matrix_view<std::complex<float>, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_caxpy(X.rows(), (void const*) &a
                          , (void const*) X.data(), X.vector_stride()
                          , (void*)       Y.data(), Y.vector_stride());
}

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
template <
    typename Policy
>
inline void axpy(
    double a
  , local_matrix_view<double, Policy> const& X
  , local_matrix_view<double, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_daxpy(X.rows(), a, X.data(), X.vector_stride()
                             , Y.data(), Y.vector_stride());
}

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
template <
    typename Policy
>
inline void axpy(
    std::complex<double> a
  , local_matrix_view<std::complex<double>, Policy> const& X
  , local_matrix_view<std::complex<double>, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_zaxpy(X.rows(), (void const*) &a
                          , (void const*) X.data(), X.vector_stride()
                          , (void*)       Y.data(), Y.vector_stride());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ COPY 

/// BLAS1: Copies vector to another vector. 
template <
    typename Policy
>
inline void copy(
    local_matrix_view<float, Policy> const& X
  , local_matrix_view<float, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_scopy(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride());
}

/// BLAS1: Copies vector to another vector. 
template <
    typename Policy
>
inline void copy(
    local_matrix_view<std::complex<float>, Policy> const& X
  , local_matrix_view<std::complex<float>, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_ccopy(X.rows(), (void const*) X.data(), X.vector_stride()
                          , (void*)       Y.data(), Y.vector_stride());
}

/// BLAS1: Copies vector to another vector. 
template <
    typename Policy
>
inline void copy(
    local_matrix_view<double, Policy> const& X
  , local_matrix_view<double, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_dcopy(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride());
}

/// BLAS1: Copies vector to another vector. 
template <
    typename Policy
>
inline void copy(
    local_matrix_view<std::complex<double>, Policy> const& X
  , local_matrix_view<std::complex<double>, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_zcopy(X.rows(), (void const*) X.data(), X.vector_stride()
                          , (void*)       Y.data(), Y.vector_stride());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOT

/// BLAS1: Computes a vector-vector dot product.
template <
    typename Policy
>
inline float dot(
    local_matrix_view<float, Policy> const& X
  , local_matrix_view<float, Policy> const& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_sdot(X.rows(), X.data(), X.vector_stride()
                                , Y.data(), Y.vector_stride()); 
}

/// BLAS1: Computes a vector-vector dot product.
template <
    typename Policy
>
inline double dot(
    local_matrix_view<double, Policy> const& X
  , local_matrix_view<double, Policy> const& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_ddot(X.rows(), X.data(), X.vector_stride()
                                , Y.data(), Y.vector_stride()); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SDSDOT

/// BLAS1: Computes a vector-vector dot product with extended precision.
template <
    typename Policy
>
inline float sdsdot(
    local_matrix_view<float, Policy> const& X
  , local_matrix_view<float, Policy> const& Y
  , float sb = 0.0
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_sdsdot(X.rows(), sb, X.data(), X.vector_stride()
                                      , Y.data(), Y.vector_stride()); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DSDOT

/// BLAS1: Computes a vector-vector dot product with extended precision.
template <
    typename Policy
>
inline double dsdot(
    local_matrix_view<float, Policy> const& X
  , local_matrix_view<float, Policy> const& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_dsdot(X.rows(), X.data(), X.vector_stride()
                                 , Y.data(), Y.vector_stride()); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOTC

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
template <
    typename Policy
>
inline std::complex<float> dotc(
    local_matrix_view<std::complex<float>, Policy> const& X
  , local_matrix_view<std::complex<float>, Policy> const& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<float> r(0.0, 0.0);
    ::cblas_cdotc_sub(X.rows(), (void const*) X.data(), X.vector_stride()
                              , (void*)       Y.data(), Y.vector_stride()
                              , (void*)       &r);
    return r; 
}

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
template <
    typename Policy
>
inline std::complex<double> dotc(
    local_matrix_view<std::complex<double>, Policy> const& X
  , local_matrix_view<std::complex<double>, Policy> const& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<double> r(0.0, 0.0);
    ::cblas_zdotc_sub(X.rows(), (void const*) X.data(), X.vector_stride()
                              , (void*)       Y.data(), Y.vector_stride()
                              , (void*)       &r);
    return r; 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOTU

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
template <
    typename Policy
>
inline std::complex<float> dotu(
    local_matrix_view<std::complex<float>, Policy> const& X
  , local_matrix_view<std::complex<float>, Policy> const& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<float> r(0.0, 0.0);
    ::cblas_cdotu_sub(X.rows(), (void const*) X.data(), X.vector_stride()
                              , (void*)       Y.data(), Y.vector_stride()
                              , (void*)       &r);
    return r; 
}

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
template <
    typename Policy
>
inline std::complex<double> dotu(
    local_matrix_view<std::complex<double>, Policy> const& X
  , local_matrix_view<std::complex<double>, Policy> const& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<double> r(0.0, 0.0);
    ::cblas_zdotu_sub(X.rows(), (void const*) X.data(), X.vector_stride()
                              , (void*)       Y.data(), Y.vector_stride()
                              , (void*)       &r);
    return r; 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ NRM2 

/// BLAS1: Computes the Euclidean norm of a vector. 
template <
    typename Policy
>
inline float nrm2(
    local_matrix_view<float, Policy> const& X
    )
{
    return ::cblas_snrm2(X.rows(), X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the Euclidean norm of a vector. 
template <
    typename Policy
>
inline float nrm2(
    local_matrix_view<std::complex<float>, Policy> const& X
    )
{
    return ::cblas_scnrm2(X.rows(), (void const*) X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the Euclidean norm of a vector. 
template <
    typename Policy
>
inline double nrm2(
    local_matrix_view<double, Policy> const& X
    )
{
    return ::cblas_dnrm2(X.rows(), X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the Euclidean norm of a vector. 
template <
    typename Policy
>
inline double nrm2(
    local_matrix_view<std::complex<double>, Policy> const& X
    )
{
    return ::cblas_dznrm2(X.rows(), (void const*) X.data(), X.vector_stride()); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROT 

/// BLAS1: Performs rotation of points in the plane.
template <
    typename Policy
>
inline void rot(
    local_matrix_view<float, Policy>& X
  , local_matrix_view<float, Policy>& Y
  , float c
  , float s
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_srot(X.rows(), X.data(), X.vector_stride()
                         , Y.data(), Y.vector_stride(), c, s); 
} 

/// BLAS1: Performs rotation of points in the plane.
template <
    typename Policy
>
inline void rot(
    local_matrix_view<double, Policy>& X
  , local_matrix_view<double, Policy>& Y
  , double c
  , double s
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_drot(X.rows(), X.data(), X.vector_stride()
                         , Y.data(), Y.vector_stride(), c, s); 
} 

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROTG

/// BLAS1: Computes the parameters for a Givens rotation.
inline void rotg(
    float& a
  , float& b
  , float& c
  , float& s
    )
{
    ::cblas_srotg(&a, &b, &c, &s);
}

/// BLAS1: Computes the parameters for a Givens rotation.
inline void rotg(
    double& a
  , double& b
  , double& c
  , double& s
    )
{
    ::cblas_drotg(&a, &b, &c, &s);
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROTM 

/// BLAS1: Performs modified Givens rotation of points in the plane.
template <
    typename Policy
>
inline void rotm(
    local_matrix_view<float, Policy>& X
  , local_matrix_view<float, Policy>& Y
  , local_matrix_view<float, Policy> const& param
    )
{
    BOOST_ASSERT(5 == param.rows()); 
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_srotm(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride(), param.data()); 
} 

/// BLAS1: Performs modified Givens rotation of points in the plane.
template <
    typename Policy
>
inline void rotm(
    local_matrix_view<float, Policy>& X
  , local_matrix_view<float, Policy>& Y
  , boost::array<float, 5> const& param
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_srotm(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride(), param.data()); 
} 

/// BLAS1: Performs modified Givens rotation of points in the plane.
template <
    typename Policy
>
inline void rotm(
    local_matrix_view<double, Policy>& X
  , local_matrix_view<double, Policy>& Y
  , local_matrix_view<double, Policy> const& param
    )
{
    BOOST_ASSERT(5 == param.rows()); 
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_drotm(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride(), param.data()); 
} 

/// BLAS1: Performs modified Givens rotation of points in the plane.
template <
    typename Policy
>
inline void rotm(
    local_matrix_view<double, Policy>& X
  , local_matrix_view<double, Policy>& Y
  , boost::array<double, 5> const& param
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_drotm(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride(), param.data()); 
} 

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROTMG 

/// BLAS1: Computes the parameters for a modified Givens rotation.
template <
    typename Policy
>
inline void rotmg(
    float& d1
  , float& d2
  , float& x1
  , float y1
  , local_matrix_view<float, Policy>& param
    )
{
    BOOST_ASSERT(5 == param.rows()); 
    ::cblas_srotmg(&d1, &d2, &x1, y1, param.data());
}

/// BLAS1: Computes the parameters for a modified Givens rotation.
template <
    typename Policy
>
inline void rotmg(
    float& d1
  , float& d2
  , float& x1
  , float y1
  , boost::array<float, 5>& param
    )
{
    ::cblas_srotmg(&d1, &d2, &x1, y1, param.c_array());
}

/// BLAS1: Computes the parameters for a modified Givens rotation.
template <
    typename Policy
>
inline void rotmg(
    double& d1
  , double& d2
  , double& x1
  , double y1
  , local_matrix_view<double, Policy>& param
    )
{
    BOOST_ASSERT(5 == param.rows()); 
    ::cblas_drotmg(&d1, &d2, &x1, y1, param.data());
}

/// BLAS1: Computes the parameters for a modified Givens rotation.
template <
    typename Policy
>
inline void rotmg(
    double& d1
  , double& d2
  , double& x1
  , double y1
  , boost::array<double, 5>& param
    )
{
    ::cblas_drotmg(&d1, &d2, &x1, y1, param.c_array());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SCAL 

/// BLAS1: Computes the product of a vector by a scalar. 
template <
    typename Policy
>
inline void scal(
    float a 
  , local_matrix_view<float, Policy>& X
    )
{
    ::cblas_sscal(X.rows(), a, X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
template <
    typename Policy
>
inline void scal(
    std::complex<float> a
  , local_matrix_view<std::complex<float>, Policy>& X
    )
{
    ::cblas_cscal(X.rows(), (void const*) &a
                          , (void*)       X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
template <
    typename Policy
>
inline void scal(
    float a
  , local_matrix_view<std::complex<float>, Policy>& X
    )
{
    ::cblas_csscal(X.rows(), a, (void*) X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
template <
    typename Policy
>
inline void scal(
    double a
  , local_matrix_view<double, Policy>& X
    )
{
    ::cblas_dscal(X.rows(), a, X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
template <
    typename Policy
>
inline void scal(
    std::complex<double> a
  , local_matrix_view<std::complex<double>, Policy>& X
    )
{
    ::cblas_zscal(X.rows(), (void const*) &a
                          , (void*)       X.data(), X.vector_stride()); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
template <
    typename Policy
>
inline void scal(
    double a
  , local_matrix_view<std::complex<double>, Policy>& X
    )
{
    ::cblas_zdscal(X.rows(), a, (void*) X.data(), X.vector_stride()); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SWAP 

/// BLAS1: Swaps a vector with another vector. 
template <
    typename Policy
>
inline void swap(
    local_matrix_view<float, Policy>& X
  , local_matrix_view<float, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_sswap(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride());
}

/// BLAS1: Swaps a vector with another vector. 
template <
    typename Policy
>
inline void swap(
    local_matrix_view<std::complex<float>, Policy>& X
  , local_matrix_view<std::complex<float>, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_cswap(X.rows(), (void*) X.data(), X.vector_stride()
                          , (void*) Y.data(), Y.vector_stride());
}

/// BLAS1: Swaps a vector with another vector. 
template <
    typename Policy
>
inline void swap(
    local_matrix_view<double, Policy>& X
  , local_matrix_view<double, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_dswap(X.rows(), X.data(), X.vector_stride()
                          , Y.data(), Y.vector_stride());
}

/// BLAS1: Swaps a vector with another vector. 
template <
    typename Policy
>
inline void swap(
    local_matrix_view<std::complex<double>, Policy>& X
  , local_matrix_view<std::complex<double>, Policy>& Y
    )
{
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_zswap(X.rows(), (void*) X.data(), X.vector_stride()
                          , (void*) Y.data(), Y.vector_stride());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ IAMAX

/// BLAS1: Finds the index of the element with maximum absolute value. 
template <
    typename Policy
>
inline std::size_t iamax(
    local_matrix_view<float, Policy> const& X
    )
{
    return ::cblas_isamax(X.rows(), X.data(), X.vector_stride()); 
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
template <
    typename Policy
>
inline std::size_t iamax(
    local_matrix_view<std::complex<float>, Policy> const& X
    )
{
    return ::cblas_icamax(X.rows(), (void const*) X.data(), X.vector_stride()); 
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
template <
    typename Policy
>
inline std::size_t iamax(
    local_matrix_view<double, Policy> const& X
    )
{
    return ::cblas_idamax(X.rows(), X.data(), X.vector_stride()); 
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
template <
    typename Policy
>
inline std::size_t iamax(
    local_matrix_view<std::complex<double>, Policy> const& X
    )
{
    return ::cblas_izamax(X.rows(), (void const*) X.data(), X.vector_stride()); 
}

// }}}
 
}}

#endif // HPXLA_AA7B5EF8_9E19_4F28_B48C_EB9DC2512EA0

