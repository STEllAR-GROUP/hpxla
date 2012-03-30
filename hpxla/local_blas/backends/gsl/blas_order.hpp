////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_98B04FF7_84CA_4E05_A8C7_A6308D0E934A)
#define HPXLA_98B04FF7_84CA_4E05_A8C7_A6308D0E934A

#include <gsl/gsl_cblas.h>

namespace hpxla { namespace blas
{

typedef ::CBLAS_ORDER index_order;

#define HPXLA_ROW_MAJOR_ORDER    ::CblasRowMajor
#define HPXLA_COLUMN_MAJOR_ORDER ::CblasColMajor

}}

#endif // HPXLA_98B04FF7_84CA_4E05_A8C7_A6308D0E934A

