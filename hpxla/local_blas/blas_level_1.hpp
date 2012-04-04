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
template <
    typename T
  , typename Policy
>
inline T asum(
    local_matrix<T, Policy> const& X
    )
{
    return asum(X.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ AXPY

/// BLAS1: Computes a vector-scalar product and adds the result to a vector.
template <
    typename T0
  , typename T1
  , typename Policy
>
inline void axpy(
    T0 a
  , local_matrix<T1, Policy> const& X
  , local_matrix<T1, Policy>& Y
    )
{
    axpy(a, X.view(), Y.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ COPY 

/// BLAS1: Copies vector to another vector. 
template <
    typename T
  , typename Policy
>
inline void copy(
    local_matrix<T, Policy> const& X
  , local_matrix<T, Policy>& Y
    )
{
    copy(X.view(), Y.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOT

/// BLAS1: Computes a vector-vector dot product.
template <
    typename T
  , typename Policy
>
inline float dot(
    local_matrix<T, Policy> const& X
  , local_matrix<T, Policy> const& Y
    )
{
    return dot(X.view(), Y.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SDSDOT

/// BLAS1: Computes a vector-vector dot product with extended precision.
template <
    typename Policy
>
inline float sdsdot(
    local_matrix<float, Policy> const& X
  , local_matrix<float, Policy> const& Y
  , float sb = 0.0
    )
{
    return sdsdot(X.view(), Y.view(), sb);
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DSDOT

/// BLAS1: Computes a vector-vector dot product with extended precision.
template <
    typename Policy
>
inline double dsdot(
    local_matrix<float, Policy> const& X
  , local_matrix<float, Policy> const& Y
    )
{
    return dsdot(X.view(), Y.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOTC

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
template <
    typename T
  , typename Policy
>
inline std::complex<T> dotc(
    local_matrix<std::complex<T>, Policy> const& X
  , local_matrix<std::complex<T>, Policy> const& Y
    )
{
    return dotc(X.view(), Y.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ DOTU

/// BLAS1: Computes a dot product of a conjugated vector with another vector.
template <
    typename T
  , typename Policy
>
inline std::complex<T> dotu(
    local_matrix<std::complex<T>, Policy> const& X
  , local_matrix<std::complex<T>, Policy> const& Y
    )
{
    return dotu(X.view(), Y.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ NRM2 

/// BLAS1: Computes the Euclidean norm of a vector. 
template <
    typename T
  , typename Policy
>
inline T nrm2(
    local_matrix<T, Policy> const& X
    )
{
    return nrm2(X.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROT 

/// BLAS1: Performs rotation of points in the plane.
template <
    typename T0
  , typename T1
  , typename T2
  , typename Policy
>
inline void rot(
    local_matrix<T0, Policy>& X
  , local_matrix<T0, Policy>& Y
  , T1 c
  , T2 s
    )
{
    rot(X.view(), Y.view(), c, s);
} 

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROTM 

/// BLAS1: Performs modified Givens rotation of points in the plane.
template <
    typename T
  , typename Policy
>
inline void rotm(
    local_matrix<T, Policy>& X
  , local_matrix<T, Policy>& Y
  , local_matrix<T, Policy> const& param
    )
{
    rotm(X.view(), Y.view(), param.view());
} 

/// BLAS1: Performs modified Givens rotation of points in the plane.
template <
    typename T
  , typename Policy
>
inline void rotm(
    local_matrix<T, Policy>& X
  , local_matrix<T, Policy>& Y
  , boost::array<T, 5> const& param
    )
{
    rotm(X.view(), Y.view(), param);
} 

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ ROTMG 

/// BLAS1: Computes the parameters for a modified Givens rotation.
template <
    typename T0
  , typename T1
  , typename T2
  , typename T3
  , typename T4
  , typename Policy
>
inline void rotmg(
    T0& d1
  , T1& d2
  , T2& x1
  , T3 y1
  , local_matrix<T4, Policy>& param
    )
{
    rotmg(d1, d2, x1, y1, param.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SCAL 

/// BLAS1: Computes the product of a vector by a scalar. 
template <
    typename T0
  , typename T1
  , typename Policy
>
inline void scal(
    T0 a 
  , local_matrix<T1, Policy>& X
    )
{
    return scal(a, X.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ SWAP 

/// BLAS1: Swaps a vector with another vector. 
template <
    typename T
  , typename Policy
>
inline void swap(
    local_matrix<T, Policy>& X
  , local_matrix<T, Policy>& Y
    )
{
    swap(X.view(), Y.view());
}

// }}}

///////////////////////////////////////////////////////////////////////////////
// {{{ IAMAX

/// BLAS1: Finds the index of the element with maximum absolute value. 
template <
    typename T
  , typename Policy
>
inline std::size_t iamax(
    local_matrix<T, Policy> const& X
    )
{
    return iamax(X.view());
}

// }}}

}}

#endif // HPXLA_6FC09DCC_8B2D_46C4_A943_E8940370B012

