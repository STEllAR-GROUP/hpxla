////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_AAA62AA2_6ECE_414A_B0F4_8C9E0A610B30)
#define HPX_AAA62AA2_6ECE_414A_B0F4_8C9E0A610B30

/// By default, try ATLAS.
#if    !defined(HPXLA_BACKEND_ATLAS) \
    && !defined(HPXLA_BACKEND_GSL)
    #define HPXLA_BACKEND_ATLAS
#endif

#endif // HPX_AAA62AA2_6ECE_414A_B0F4_8C9E0A610B30

