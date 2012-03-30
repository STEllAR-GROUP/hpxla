////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_6EFCC1B0_166B_4F8A_B9D1_B1CE987F9EEC)
#define HPXLA_6EFCC1B0_166B_4F8A_B9D1_B1CE987F9EEC

#include <cblas.h>

namespace hpxla { namespace blas
{

typedef ::CBLAS_ORDER index_order;

#define HPXLA_ROW_MAJOR_ORDER    ::CblasRowMajor
#define HPXLA_COLUMN_MAJOR_ORDER ::CblasColMajor

}}

#endif // HPXLA_6EFCC1B0_166B_4F8A_B9D1_B1CE987F9EEC

