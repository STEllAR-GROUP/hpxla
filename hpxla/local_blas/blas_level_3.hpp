////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_F18A8EB7_E4D7_4BB5_9425_C59B868F48B2)
#define HPXLA_F18A8EB7_E4D7_4BB5_9425_C59B868F48B2

#include <hpxla/config.hpp>

#if   defined(HPXLA_BACKEND_ATLAS)
    #include <hpxla/local_blas/backends/atlas/blas_level_3.hpp>
#elif defined(HPXLA_BACKEND_GSL)
    #include <hpxla/local_blas/backends/gsl/blas_level_3.hpp>
#endif

#include <hpxla/local_matrix.hpp>

namespace hpxla { namespace blas
{

// IMPLEMENT: local_matrix forwarders.

}}

#endif // HPXLA_F18A8EB7_E4D7_4BB5_9425_C59B868F48B2

