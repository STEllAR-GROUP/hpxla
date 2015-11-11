////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_58D663CD_0FE1_4B72_8CE6_903A71926A8C)
#define HPXLA_58D663CD_0FE1_4B72_8CE6_903A71926A8C

//include <hpxla/stubs/distributed_submatrix.hpp>
#include <hpxla/server/distributed_submatrix.hpp>

namespace hpxla
{

template <
    typename T
  , typename Policy = distributed_matrix_policy<> 
>
struct distributed_submatrix 
  : hpx::components::client_base<
        distributed_submatrix<T, Policy>
      , server::distributed_submatrix<T, Policy>
    >
{
    typedef hpx::components::client_base<
        distributed_submatrix<T, Policy>, server::distributed_submatrix<T, Policy>
    > base_type;
    
    typedef server::distributed_submatrix<T, Policy> server_type;

    typedef typename server_type::local_matrix_type local_matrix_type;

    typedef typename server_type::value_type value_type;
    typedef typename server_type::reference reference;
    typedef typename server_type::const_reference const_reference;
    typedef typename server_type::pointer pointer;
    typedef typename server_type::const_pointer const_pointer;
    typedef typename server_type::size_type size_type;

    typedef typename server_type::policy_type policy_type;
    typedef typename server_type::indexing_policy_type indexing_policy_type;
    typedef typename server_type::partitioning_policy_type
        partitioning_policy_type;
    typedef typename server_type::distribution_policy_type
        distribution_policy_type;
    typedef typename server_type::allocation_policy_type allocation_policy_type;
    distributed_submatrix(
        hpx::future<hpx::naming::id_type> && gid
        )
      : base_type(std::move(gid))
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
        typedef typename server_type::initialize_from_dimensions_action
            action_type;
        BOOST_ASSERT(this->get_id());
        hpx::apply<action_type>(this->get_id(), rows, cols, init, offsets);
    }

    void initialize_sync(
        size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        typedef typename server_type::initialize_from_dimensions_action
            action_type;
        BOOST_ASSERT(this->get_id());
        hpx::async<action_type>(this->get_id(), rows, cols, init, offsets).get();
    }

    hpx::lcos::future<void> initialize_async(
        size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        typedef typename server_type::initialize_from_dimensions_action
            action_type;
        BOOST_ASSERT(this->get_id());
        return hpx::async<action_type>(this->get_id(), rows, cols, init, offsets);
    }

    ///////////////////////////////////////////////////////////////////////////
    // initialize_from_matrix

    void initialize_non_blocking(
        local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        BOOST_ASSERT(this->get_id());
        hpx::apply<action_type>(this->get_id(), m, offsets);
    }

    void initialize_non_blocking(
        BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        BOOST_ASSERT(this->get_id());
        // Note, boost::move needed here or no?
        hpx::apply<action_type>(this->get_id(), boost::move(m), offsets);
    }

    void initialize_sync(
        local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        BOOST_ASSERT(this->get_id());
        hpx::async<action_type>(this->get_id(), boost::move(m), offsets).get();
    }

    void initialize_sync(
        BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        BOOST_ASSERT(this->get_id());
        // Note, boost::move needed here or no?
        hpx::async<action_type>(this->get_id(), boost::move(m), offsets).get();
    }

    hpx::lcos::future<void> initialize_async(
        local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        BOOST_ASSERT(this->get_id());
        return hpx::async<action_type>(this->get_id(), m, offsets);
    }

    hpx::lcos::future<void> initialize_async(
        BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        BOOST_ASSERT(this->get_id());
        // REVIEW: Do I need to use boost::move here?
        return hpx::async<action_type>(this->get_id(), boost::move(m), offsets);
    }

    ///////////////////////////////////////////////////////////////////////////
    // lookup

    value_type lookup_sync(
        size_type rows
      , size_type cols
        )
    {
        typedef typename server_type::lookup_action action_type;
        BOOST_ASSERT(this->get_id());
        hpx::async<action_type>(this->get_id(), rows, cols).get();
    }

    hpx::lcos::future<value_type> lookup_async(
        size_type rows
      , size_type cols
        )
    {
        typedef typename server_type::lookup_action action_type;
        BOOST_ASSERT(this->get_id());
        return hpx::async<action_type>(this->get_id(), rows, cols);
    }
};

}

#include <hpxla/policies.hpp>

#endif // HPXLA_58D663CD_0FE1_4B72_8CE6_903A71926A8C

