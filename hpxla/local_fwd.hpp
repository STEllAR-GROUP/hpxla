////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84)
#define HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84

#include <hpxla/policies_fwd.hpp>

namespace hpxla
{

template <
    typename T
  , typename Policy = local_matrix_policy<> 
>
struct local_matrix_view;

template <
    typename T
  , typename Policy = local_matrix_policy<>  
>
struct local_matrix;

}

#endif // HPXLA_F1C9159C_DE88_4AAB_A4F2_5F186B3C6B84

