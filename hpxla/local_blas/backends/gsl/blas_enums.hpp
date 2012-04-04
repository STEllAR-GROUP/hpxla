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

enum index_order 
{
    row_major       = ::CblasRowMajor
  , column_major    = ::CblasColMajor
};

enum transpose_operation
{
    no_transpose        = ::CblasNoTrans
  , transpose           = ::CblasTrans
  , conjugate_transpose = ::CblasConjTrans
};

}}

#endif // HPXLA_98B04FF7_84CA_4E05_A8C7_A6308D0E934A

