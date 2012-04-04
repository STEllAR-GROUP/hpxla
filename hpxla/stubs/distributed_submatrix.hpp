////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_21A597F4_D338_4005_AC7E_54C2B6C4D40E)
#define HPXLA_21A597F4_D338_4005_AC7E_54C2B6C4D40E

#include <hpxla/server/distributed_submatrix.hpp>

namespace hpx { namespace stubs 
{

template <
    typename T
  , typename Policy = distributed_matrix_policy<> 
>
struct distributed_submatrix 
  : hpx::components::stub_base<server::distributed_submatrix<T, Policy> >
{
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

    ///////////////////////////////////////////////////////////////////////////
    // initialize_from_dimensions

    static void initialize_non_blocking(
        hpx::naming::id_type const& gid
      , size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        typedef typename server_type::initialize_from_dimensions_action
            action_type;
        hpx::applier::apply<action_type>(gid, rows, cols, init, offsets);
    }

    static void initialize_sync(
        hpx::naming::id_type const& gid
      , size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        typedef typename server_type::initialize_from_dimensions_action
            action_type;
        hpx::lcos::async<action_type>(gid, rows, cols, init, offsets).get();
    }

    static hpx::lcos::future<void> initialize_async(
        hpx::naming::id_type const& gid
      , size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
        )
    {
        typedef typename server_type::initialize_from_dimensions_action
            action_type;
        return hpx::lcos::async<action_type>(gid, rows, cols, init, offsets);
    }

    ///////////////////////////////////////////////////////////////////////////
    // initialize_from_matrix

    static void initialize_non_blocking(
        hpx::naming::id_type const& gid
      , local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        hpx::applier::apply<action_type>(gid, m, offsets);
    }

    static void initialize_non_blocking(
        hpx::naming::id_type const& gid
      , BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        // REVIEW: Do I need to use boost::move here?
        hpx::applier::apply<action_type>(gid, boost::move(m), offsets);
    }

    static void initialize_sync(
        hpx::naming::id_type const& gid
      , local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        hpx::lcos::async<action_type>(gid, m, offsets).get();
    }

    static void initialize_sync(
        hpx::naming::id_type const& gid
      , BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        // REVIEW: Do I need to use boost::move here?
        hpx::lcos::async<action_type>(gid, boost::move(m), offsets).get();
    }

    static hpx::lcos::future<void> initialize_async(
        hpx::naming::id_type const& gid
      , local_matrix_type const& m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        return hpx::lcos::async<action_type>(gid, m, offsets);
    }

    static hpx::lcos::future<void> initialize_async(
        hpx::naming::id_type const& gid
      , BOOST_RV_REF(local_matrix_type) m
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
    {
        typedef typename server_type::initialize_from_matrix_action
            action_type;
        // REVIEW: Do I need to use boost::move here?
        return hpx::lcos::async<action_type>(gid, boost::move(m), offsets);
    }

    ///////////////////////////////////////////////////////////////////////////
    // lookup

    static value_type lookup_sync(
        hpx::naming::id_type const& gid
      , size_type rows
      , size_type cols
        )
    {
        typedef typename server_type::lookup_action action_type;
        hpx::lcos::async<action_type>(gid, row, col).get();
    }

    static hpx::lcos::future<value_type> lookup_async(
        hpx::naming::id_type const& gid
      , size_type rows
      , size_type cols
        )
    {
        typedef typename server_type::lookup_action action_type;
        return hpx::lcos::async<action_type>(gid, row, col);
    }
};

}}

#endif // HPXLA_21A597F4_D338_4005_AC7E_54C2B6C4D40E

