////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_570F6284_5CCA_46C7_B8FC_9EEB2E804885)
#define HPXLA_570F6284_5CCA_46C7_B8FC_9EEB2E804885

#include <boost/geometry/util/select_most_precise.hpp>

#include <limits>

namespace hpxla
{

template <
    typename T0
  , typename T1
>
inline bool compare_real(
    T0 x
  , T1 y
    )
{
    typedef typename boost::geometry::select_most_precise<T0, T1>::type
        real_type;

    real_type const epsilon = std::numeric_limits<real_type>::epsilon();
 
    if (   (real_type(x) + epsilon >= real_type(y))
       &&  (real_type(x) - epsilon <= real_type(y)))
        return true;
    else
        return false;
}

template <
    typename T0
  , typename T1
  , typename T2
>
inline bool compare_real(
    T0 x
  , T1 y
  , T2 epsilon
    )
{
    typedef typename boost::geometry::select_most_precise<
        typename boost::geometry::select_most_precise<T0, T1>::type, T2
    >::type real_type;

    if (  (real_type(x) + real_type(epsilon) >= real_type(y))
       && (real_type(x) - real_type(epsilon) <= real_type(y)))
        return true;
    else
        return false;
}

}

#endif // HPXLA_570F6284_5CCA_46C7_B8FC_9EEB2E804885

