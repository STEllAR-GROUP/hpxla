////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_D771701C_D339_4D01_B1BE_7F941F53D83D)
#define HPXLA_D771701C_D339_4D01_B1BE_7F941F53D83D

#include <cblas.h>

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

#endif // HPXLA_D771701C_D339_4D01_B1BE_7F941F53D83D

