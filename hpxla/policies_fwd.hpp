////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_9B468CF3_FEEA_4716_AB59_4C4329D65D85)
#define HPXLA_9B468CF3_FEEA_4716_AB59_4C4329D65D85

#include <memory>

#include <hpx/util/unused.hpp>

namespace hpxla { namespace policy
{

struct column_major_indexing;
struct row_major_indexing;

}

template <
    typename IndexingPolicy = policy::column_major_indexing
  , typename AllocationPolicy = std::allocator<hpx::util::unused_type>
>
struct local_matrix_policy
{
    typedef IndexingPolicy indexing_policy_type;
    typedef AllocationPolicy allocation_policy_type;
};

template <
    typename IndexingPolicy = policy::column_major_indexing
  , typename PartitioningPolicy = hpx::util::unused_type
  , typename DistributionPolicy = hpx::util::unused_type
  , typename AllocationPolicy = std::allocator<hpx::util::unused_type>
>
struct distributed_matrix_policy
{
    typedef local_matrix_policy<
        IndexingPolicy
      , AllocationPolicy
    > local_policy_type;

    typedef IndexingPolicy indexing_policy_type;
    typedef PartitioningPolicy partitioning_policy_type;
    typedef DistributionPolicy distribution_policy_type;
    typedef AllocationPolicy allocation_policy_type;
};

}

#endif // HPXLA_9B468CF3_FEEA_4716_AB59_4C4329D65D85

