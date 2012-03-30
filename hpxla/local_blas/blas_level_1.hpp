////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_6FC09DCC_8B2D_46C4_A943_E8940370B012)
#define HPXLA_6FC09DCC_8B2D_46C4_A943_E8940370B012

#include <hpxla/config.hpp>

#if   defined(HPXLA_BACKEND_ATLAS)
    #include <hpxla/local_blas/backends/atlas/blas_level_1.hpp>
#elif defined(HPXLA_BACKEND_GSL)
    #include <hpxla/local_blas/backends/gsl/blas_level_1.hpp>
#endif

#include <hpxla/local_matrix.hpp>

namespace hpxla { namespace blas
{

// Forwarding functions for local_matrix<>.

///////////////////////////////////////////////////////////////////////////////
// {{{ ASUM

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline float asum(
    local_matrix<float> const& X
  , std::size_t strideX = 1
    )
{
    return asum(X.view(), strideX);
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline float asum(
    local_matrix<std::complex<float> > const& X
  , std::size_t strideX = 1
    )
{
    return asum(X.view(), strideX);
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline double asum(
    local_matrix<double> const& X
  , std::size_t strideX = 1
    )
{
    return asum(X.view(), strideX);
}

/// BLAS1: Computes the sum of magnitudes of the vector elements.
inline double asum(
    local_matrix<std::complex<double> > const& X
  , std::size_t strideX = 1
    )
{
    return asum(X.view(), strideX);
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
    axpy(a, X.view(), Y.view(), strideX, strideY);
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
    axpy(a, X.view(), Y.view(), strideX, strideY);
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
    axpy(a, X.view(), Y.view(), strideX, strideY);
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
    axpy(a, X.view(), Y.view(), strideX, strideY);
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
    copy(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Copies vector to another vector. 
inline void copy(
    local_matrix<std::complex<float> > const& X
  , local_matrix<std::complex<float> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    copy(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Copies vector to another vector. 
inline void copy(
    local_matrix<double> const& X
  , local_matrix<double>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    copy(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Copies vector to another vector. 
inline void copy(
    local_matrix<std::complex<double> > const& X
  , local_matrix<std::complex<double> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    copy(X.view(), Y.view(), strideX, strideY);
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
    return dot(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Computes a vector-vector dot product.
inline double dot(
    local_matrix<double> const& X
  , local_matrix<double> const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    return dot(X.view(), Y.view(), strideX, strideY);
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
    return sdot(X.view(), Y.view(), sb, strideX, strideY);
}

/// BLAS1: Computes a vector-vector dot product with extended precision.
inline double sdot(
    local_matrix<float> const& X
  , local_matrix<float> const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    return sdot(X.view(), Y.view(), strideX, strideY);
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
    return dotc(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
inline std::complex<double> dotc(
    local_matrix<std::complex<double> > const& X
  , local_matrix<std::complex<double> > const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    return dotc(X.view(), Y.view(), strideX, strideY);
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
    return dotu(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
inline std::complex<double> dotu(
    local_matrix<std::complex<double> > const& X
  , local_matrix<std::complex<double> > const& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    return dotu(X.view(), Y.view(), strideX, strideY);
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
    return nrm2(X.view(), strideX);
}

/// BLAS1: Computes the Euclidean norm of a vector. 
inline float nrm2(
    local_matrix<std::complex<float> > const& X
  , std::size_t strideX = 1
    )
{
    return nrm2(X.view(), strideX);
}

/// BLAS1: Computes the Euclidean norm of a vector. 
inline double nrm2(
    local_matrix<double> const& X
  , std::size_t strideX = 1
    )
{
    return nrm2(X.view(), strideX);
}

/// BLAS1: Computes the Euclidean norm of a vector. 
inline double nrm2(
    local_matrix<std::complex<double> > const& X
  , std::size_t strideX = 1
    )
{
    return nrm2(X.view(), strideX);
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
    rot(X.view(), Y.view(), c, s, strideX, strideY);
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
    rot(X.view(), Y.view(), c, s, strideX, strideY);
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
    rotm(X.view(), Y.view(), param.view(), strideX, strideY);
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
    rotm(X.view(), Y.view(), param, strideX, strideY);
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
    rotm(X.view(), Y.view(), param.view(), strideX, strideY);
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
    rotm(X.view(), Y.view(), param, strideX, strideY);
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
    rotmg(d1, d2, x1, y1, param.view());
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
    rotmg(d1, d2, x1, y1, param.view());
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
    return scal(a, X.view(), strideX);
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    std::complex<float> a
  , local_matrix<std::complex<float> >& X
  , std::size_t strideX = 1
    )
{
    scal(a, X.view(), strideX);
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    float a
  , local_matrix<std::complex<float> >& X
  , std::size_t strideX = 1
    )
{
    scal(a, X.view(), strideX);
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    double a
  , local_matrix<double>& X
  , std::size_t strideX = 1
    )
{
    scal(a, X.view(), strideX);
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    std::complex<double> a
  , local_matrix<std::complex<double> >& X
  , std::size_t strideX = 1
    )
{
    scal(a, X.view(), strideX);
}

/// BLAS1: Computes the product of a vector by a scalar. 
inline void scal(
    double a
  , local_matrix<std::complex<double> >& X
  , std::size_t strideX = 1
    )
{
    scal(a, X.view(), strideX);
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
    swap(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Swaps a vector with another vector. 
inline void swap(
    local_matrix<std::complex<float> >& X
  , local_matrix<std::complex<float> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    swap(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Swaps a vector with another vector. 
inline void swap(
    local_matrix<double>& X
  , local_matrix<double>& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    swap(X.view(), Y.view(), strideX, strideY);
}

/// BLAS1: Swaps a vector with another vector. 
inline void swap(
    local_matrix<std::complex<double> >& X
  , local_matrix<std::complex<double> >& Y
  , std::size_t strideX = 1
  , std::size_t strideY = 1
    )
{
    swap(X.view(), Y.view(), strideX, strideY);
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
    return iamax(X.view(), strideX);
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
inline std::size_t iamax(
    local_matrix<std::complex<float> > const& X
  , std::size_t strideX = 1
    )
{
    return iamax(X.view(), strideX);
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
inline std::size_t iamax(
    local_matrix<double> const& X
  , std::size_t strideX = 1
    )
{
    return iamax(X.view(), strideX);
}

/// BLAS1: Finds the index of the element with maximum absolute value. 
inline std::size_t iamax(
    local_matrix<std::complex<double> > const& X
  , std::size_t strideX = 1
    )
{
    return iamax(X.view(), strideX);
}

// }}}

}}

#endif // HPXLA_6FC09DCC_8B2D_46C4_A943_E8940370B012

