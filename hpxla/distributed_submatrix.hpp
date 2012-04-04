////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_58D663CD_0FE1_4B72_8CE6_903A71926A8C)
#define HPXLA_58D663CD_0FE1_4B72_8CE6_903A71926A8C

#include <hpxla/stubs/distributed_submatrix.hpp>

namespace hpxla
{

template <
    typename T
  , typename Policy = distributed_matrix_policy<> 
>
struct distributed_submatrix 
  : hpx::components::client_base<
        distributed_submatrix<T, Policy>
      , stubs::distributed_submatrix<T, Policy>
    >
{
    typedef hpx::components::client_base<
        distributed_submatrix, stubs::distributed_submatrix<T, Policy>
    > base_type;

    typedef stubs::distributed_submatrix<T, Policy> server_type;

    typedef typename stubs_type::local_matrix_type local_matrix_type;

    typedef typename stubs_type::value_type value_type;
    typedef typename stubs_type::reference reference;
    typedef typename stubs_type::const_reference const_reference;
    typedef typename stubs_type::pointer pointer;
    typedef typename stubs_type::const_pointer const_pointer;
    typedef typename stubs_type::size_type size_type;

    typedef typename stubs_type::policy_type policy_type;
    typedef typename stubs_type::indexing_policy_type indexing_policy_type;
    typedef typename stubs_type::partitioning_policy_type
        partitioning_policy_type;
    typedef typename stubs_type::distribution_policy_type
        distribution_policy_type;
    typedef typename stubs_type::allocation_policy_type allocation_policy_type;

    distributed_submatrix(
        hpx::naming::id_type const& gid
        )
      : base_type(gid)
    {}

    ///////////////////////////////////////////////////////////////////////////
    // initialize_from_dimensions

    void initialize_non_blocking(
        size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        BOOST_ASSERT(this->gid_);
        this->base_type::initialize_non_blocking
            (this->gid_, rows, cols, init, offsets);
    }

    void initialize_sync(
        size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        BOOST_ASSERT(this->gid_);
        this->base_type::initialize_sync(this->gid_, rows, cols, init, offsets);
    }

    hpx::lcos::future<void> initialize_async(
        size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        BOOST_ASSERT(this->gid_);
        return this->base_type::initialize_async
            (this->gid_, rows, cols, init, offsets);
    }

    ///////////////////////////////////////////////////////////////////////////
    // initialize_from_matrix

    void initialize_non_blocking(
        local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        BOOST_ASSERT(this->gid_);
        this->base_type::initialize_non_blocking(this->gid_, m, offsets);
    }

    void initialize_non_blocking(
        BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        BOOST_ASSERT(this->gid_);
        this->base_type::initialize_non_blocking
            (this->gid_, boost::move(m), offsets);
    }

    void initialize_sync(
        local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        BOOST_ASSERT(this->gid_);
        this->base_type::initialize_sync(this->gid_, m, offsets);
    }

    void initialize_sync(
        BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        BOOST_ASSERT(this->gid_);
        // REVIEW: Do I need to use boost::move here?
        this->base_type::initialize_sync(this->gid_, boost::move(m), offsets);
    }

    hpx::lcos::future<void> initialize_async(
        local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        BOOST_ASSERT(this->gid_);
        return this->base_type::initialize_async(this->gid_, m, offsets);
    }

    hpx::lcos::future<void> initialize_async(
        BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        BOOST_ASSERT(this->gid_);
        // REVIEW: Do I need to use boost::move here?
        return this->base_type::initialize_async
            (this->gid_, boost::move(m), offsets);
    }

    ///////////////////////////////////////////////////////////////////////////
    // lookup

    value_type lookup_sync(
        size_type rows
      , size_type cols
        )
    {
        BOOST_ASSERT(this->gid_);
        return this->base_type::lookup_sync(this->gid_, rows, cols);
    }

    hpx::lcos::future<value_type> lookup_async(
        size_type rows
      , size_type cols
        )
    {
        BOOST_ASSERT(this->gid_);
        return this->base_type::lookup_async(this->gid_, rows, cols);
    }
};

}

#endif // HPXLA_58D663CD_0FE1_4B72_8CE6_903A71926A8C

