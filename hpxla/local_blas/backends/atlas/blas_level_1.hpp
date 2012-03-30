////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_AA7B5EF8_9E19_4F28_B48C_EB9DC2512EA0)
#define HPXLA_AA7B5EF8_9E19_4F28_B48C_EB9DC2512EA0

#include <hpxla/local_matrix.hpp>

#include <boost/array.hpp>

#include <complex>

#include <cblas.h>

// TODO: std::vector overloads.
// TODO: Replace local_matrix with local_matrix_view, add local_matrix
//       forwarders.

namespace hpxla { namespace blas
{

///////////////////////////////////////////////////////////////////////////////
// {{{ ASUM

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline float asum(
    local_matrix<float> const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_sasum(X.rows(), X.data(), strideX); 
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline float asum(
    local_matrix<std::complex<float> > const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_scasum(X.rows(), (void const*) X.data(), strideX); 
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline double asum(
    local_matrix<double> const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_dasum(X.rows(), X.data(), strideX); 
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline double asum(
    local_matrix<std::complex<double> > const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_dzasum(X.rows(), (void const*) X.data(), strideX); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ AXPY (TODO: inline version)

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
inline void axpy(
    float a
  , local_matrix<float> const& X
  , local_matrix<float>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_saxpy(X.rows(), a, X.data(), strideX, Y.data(), strideY);
}

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
inline void axpy(
    std::complex<float> a
  , local_matrix<std::complex<float> > const& X
  , local_matrix<std::complex<float> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_caxpy(X.rows(), (void const*) &a
                          , (void const*) X.data(), strideX
                          , (void*)       Y.data(), strideY);
}

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
inline void axpy(
    double a
  , local_matrix<double> const& X
  , local_matrix<double>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_daxpy(X.rows(), a, X.data(), strideX, Y.data(), strideY);
}

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
inline void axpy(
    std::complex<double> a
  , local_matrix<std::complex<double> > const& X
  , local_matrix<std::complex<double> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_zaxpy(X.rows(), (void const*) &a
                          , (void const*) X.data(), strideX
                          , (void*)       Y.data(), strideY);
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ COPY 

/// BLAS1: Copies vector to another vector. 
inline void copy(
    local_matrix<float> const& X
  , local_matrix<float>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_scopy(X.rows(), X.data(), strideX, Y.data(), strideY);
}

/// BLAS1: Copies vector to another vector. 
inline void copy(
    local_matrix<std::complex<float> > const& X
  , local_matrix<std::complex<float> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_ccopy(X.rows(), (void const*) X.data(), strideX
                          , (void*)       Y.data(), strideY);
}

/// BLAS1: Copies vector to another vector. 
inline void copy(
    local_matrix<double> const& X
  , local_matrix<double>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_dcopy(X.rows(), X.data(), strideX, Y.data(), strideY);
}

/// BLAS1: Copies vector to another vector. 
inline void copy(
    local_matrix<std::complex<double> > const& X
  , local_matrix<std::complex<double> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_zcopy(X.rows(), (void const*) X.data(), strideX
                          , (void*)       Y.data(), strideY);
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOT

/// BLAS1: Computes a vector-vector dot product.
inline float dot(
    local_matrix<float> const& X
  , local_matrix<float> const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_sdot(X.rows(), X.data(), strideX, Y.data(), strideY); 
}

/// BLAS1: Computes a vector-vector dot product.
inline double dot(
    local_matrix<double> const& X
  , local_matrix<double> const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_ddot(X.rows(), X.data(), strideX, Y.data(), strideY); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SDOT

/// BLAS1: Computes a vector-vector dot product with extended precision.
inline float sdot(
    local_matrix<float> const& X
  , local_matrix<float> const& Y
  , float sb = 0.0
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_sdsdot(X.rows(), sb, X.data(), strideX, Y.data(), strideY); 
}

/// BLAS1: Computes a vector-vector dot product with extended precision.
inline double sdot(
    local_matrix<float> const& X
  , local_matrix<float> const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    return ::cblas_dsdot(X.rows(), X.data(), strideX, Y.data(), strideY); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOTC

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
inline std::complex<float> dotc(
    local_matrix<std::complex<float> > const& X
  , local_matrix<std::complex<float> > const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<float> r(0.0, 0.0);
    ::cblas_cdotc_sub(X.rows(), (void const*) X.data(), strideX
                              , (void*)       Y.data(), strideY
                              , (void*)       &r);
    return r; 
}

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
inline std::complex<double> dotc(
    local_matrix<std::complex<double> > const& X
  , local_matrix<std::complex<double> > const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<double> r(0.0, 0.0);
    ::cblas_zdotc_sub(X.rows(), (void const*) X.data(), strideX
                              , (void*)       Y.data(), strideY
                              , (void*)       &r);
    return r; 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOTU

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
inline std::complex<float> dotu(
    local_matrix<std::complex<float> > const& X
  , local_matrix<std::complex<float> > const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<float> r(0.0, 0.0);
    ::cblas_cdotu_sub(X.rows(), (void const*) X.data(), strideX
                              , (void*)       Y.data(), strideY
                              , (void*)       &r);
    return r; 
}

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
inline std::complex<double> dotu(
    local_matrix<std::complex<double> > const& X
  , local_matrix<std::complex<double> > const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    std::complex<double> r(0.0, 0.0);
    ::cblas_zdotu_sub(X.rows(), (void const*) X.data(), strideX
                              , (void*)       Y.data(), strideY
                              , (void*)       &r);
    return r; 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ NRM2 

/// BLAS1: Computes the Euclidean norm of a vector. 
inline float nrm2(
    local_matrix<float> const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_snrm2(X.rows(), X.data(), strideX); 
}

/// BLAS1: Computes the Euclidean norm of a vector. 
inline float nrm2(
    local_matrix<std::complex<float> > const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_scnrm2(X.rows(), (void const*) X.data(), strideX); 
}

/// BLAS1: Computes the Euclidean norm of a vector. 
inline double nrm2(
    local_matrix<double> const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_dnrm2(X.rows(), X.data(), strideX); 
}

/// BLAS1: Computes the Euclidean norm of a vector. 
inline double nrm2(
    local_matrix<std::complex<double> > const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_dznrm2(X.rows(), (void const*) X.data(), strideX); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROT 

/// BLAS1: Performs rotation of points in the plane.
inline void rot(
    local_matrix<float>& X
  , local_matrix<float>& Y
  , float c
  , float s
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_srot(X.rows(), X.data(), strideX, Y.data(), strideY, c, s); 
} 

/// BLAS1: Performs rotation of points in the plane.
inline void rot(
    local_matrix<double>& X
  , local_matrix<double>& Y
  , double c
  , double s
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_drot(X.rows(), X.data(), strideX, Y.data(), strideY, c, s); 
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
inline void rotm(
    local_matrix<float>& X
  , local_matrix<float>& Y
  , local_matrix<float> const& param
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == param.columns()); 
    BOOST_ASSERT(5 == param.rows()); 
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_srotm(X.rows(), X.data(), strideX, Y.data(), strideY, param.data()); 
} 

/// BLAS1: Performs modified Givens rotation of points in the plane.
inline void rotm(
    local_matrix<float>& X
  , local_matrix<float>& Y
  , boost::array<float, 5> const& param
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_srotm(X.rows(), X.data(), strideX, Y.data(), strideY, param.data()); 
} 

/// BLAS1: Performs modified Givens rotation of points in the plane.
inline void rotm(
    local_matrix<double>& X
  , local_matrix<double>& Y
  , local_matrix<double> const& param
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == param.columns()); 
    BOOST_ASSERT(5 == param.rows()); 
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_drotm(X.rows(), X.data(), strideX, Y.data(), strideY, param.data()); 
} 

/// BLAS1: Performs modified Givens rotation of points in the plane.
inline void rotm(
    local_matrix<double>& X
  , local_matrix<double>& Y
  , boost::array<double, 5> const& param
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_drotm(X.rows(), X.data(), strideX, Y.data(), strideY, param.data()); 
} 

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROTMG 

/// BLAS1: Computes the parameters for a modified Givens rotation.
inline void rotmg(
    float& d1
  , float& d2
  , float& x1
  , float y1
  , local_matrix<float>& param
    )
{
    BOOST_ASSERT(1 == param.columns()); 
    BOOST_ASSERT(5 == param.rows()); 
    ::cblas_srotmg(&d1, &d2, &x1, y1, param.data());
}

/// BLAS1: Computes the parameters for a modified Givens rotation.
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
inline void rotmg(
    double& d1
  , double& d2
  , double& x1
  , double y1
  , local_matrix<double>& param
    )
{
    BOOST_ASSERT(1 == param.columns()); 
    BOOST_ASSERT(5 == param.rows()); 
    ::cblas_drotmg(&d1, &d2, &x1, y1, param.data());
}

/// BLAS1: Computes the parameters for a modified Givens rotation.
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
inline void scal(
    float a 
  , local_matrix<float>& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    ::cblas_sscal(X.rows(), a, X.data(), strideX); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    std::complex<float> a
  , local_matrix<std::complex<float> >& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    ::cblas_cscal(X.rows(), (void const*) &a, (void*) X.data(), strideX); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    float a
  , local_matrix<std::complex<float> >& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    ::cblas_csscal(X.rows(), a, (void*) X.data(), strideX); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    double a
  , local_matrix<double>& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    ::cblas_dscal(X.rows(), a, X.data(), strideX); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    std::complex<double> a
  , local_matrix<std::complex<double> >& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    ::cblas_zscal(X.rows(), (void const*) &a, (void*) X.data(), strideX); 
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    double a
  , local_matrix<std::complex<double> >& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    ::cblas_zdscal(X.rows(), a, (void*) X.data(), strideX); 
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SWAP 

/// BLAS1: Swaps a vector with another vector. 
inline void swap(
    local_matrix<float>& X
  , local_matrix<float>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_sswap(X.rows(), X.data(), strideX, Y.data(), strideY);
}

/// BLAS1: Swaps a vector with another vector. 
inline void swap(
    local_matrix<std::complex<float> >& X
  , local_matrix<std::complex<float> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_cswap(X.rows(), (void*) X.data(), strideX
                          , (void*) Y.data(), strideY);
}

/// BLAS1: Swaps a vector with another vector. 
inline void swap(
    local_matrix<double>& X
  , local_matrix<double>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_dswap(X.rows(), X.data(), strideX, Y.data(), strideY);
}

/// BLAS1: Swaps a vector with another vector. 
inline void swap(
    local_matrix<std::complex<double> >& X
  , local_matrix<std::complex<double> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    BOOST_ASSERT(1 == Y.columns());
    BOOST_ASSERT(X.rows() == Y.rows());
    ::cblas_zswap(X.rows(), (void*) X.data(), strideX
                          , (void*) Y.data(), strideY);
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ IAMAX

/// BLAS1: Finds the index of the element with maximum absolute value. 
inline std::size_t iamax(
    local_matrix<float> const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_isamax(X.rows(), X.data(), strideX); 
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
inline std::size_t iamax(
    local_matrix<std::complex<float> > const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_icamax(X.rows(), (void const*) X.data(), strideX); 
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
inline std::size_t iamax(
    local_matrix<double> const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_idamax(X.rows(), X.data(), strideX); 
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
inline std::size_t iamax(
    local_matrix<std::complex<double> > const& X
  , std::size_t strideX = 1
    )
{
    BOOST_ASSERT(1 == X.columns());
    return ::cblas_izamax(X.rows(), (void const*) X.data(), strideX); 
}

// }}}
 
}}

#endif // HPXLA_AA7B5EF8_9E19_4F28_B48C_EB9DC2512EA0

