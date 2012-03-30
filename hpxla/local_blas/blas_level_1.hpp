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

// IMPLEMENT: local_matrix forwarders.

}}

#endif // HPXLA_6FC09DCC_8B2D_46C4_A943_E8940370B012

