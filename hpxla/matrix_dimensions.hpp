////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_43D42878_0320_4C79_BE46_F85E77CFDA23)
#define HPXLA_43D42878_0320_4C79_BE46_F85E77CFDA23

#include <boost/cstdint.hpp>
#include <boost/fusion/include/define_struct.hpp>

BOOST_FUSION_DEFINE_TPL_STRUCT(
    (T), (hpxla), matrix_dimensions,
    (T, rows)
    (T, cols))

namespace hpxla
{
    typedef matrix_dimensions<boost::uint64_t> matrix_bounds;
    typedef matrix_dimensions<boost::int64_t> matrix_offsets;
}

namespace boost { namespace serialization
{

template <
    typename T
  , typename Archive
>
void serialize(
    Archive& ar
  , hpxla::matrix_dimensions<T>& md
  , unsigned int
    )
{
    ar & md.rows & md.cols;
}

}}

#endif // HPXLA_43D42878_0320_4C79_BE46_F85E77CFDA23

