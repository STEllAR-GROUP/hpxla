////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_8F16F3F2_9DEB_4D29_9657_19EA59788895)
#define HPXLA_8F16F3F2_9DEB_4D29_9657_19EA59788895

#include <hpxla/local_matrix.hpp>

#include <hpx/hpx_fwd.hpp>
#include <hpx/include/components.hpp>
#include <hpx/util/function.hpp>

#include <boost/serialization/complex.hpp>

namespace hpxla { namespace server
{

template <
    typename T
  , typename Policy = distributed_matrix_policy<> 
>
struct HPX_COMPONENT_EXPORT distributed_submatrix
  : hpx::components::managed_component_base<distributed_submatrix<T, Policy> >
{
    typedef local_matrix<T, typename Policy::local_policy_type>
        local_matrix_type;

    typedef typename local_matrix_type::value_type value_type;
    typedef typename local_matrix_type::reference reference;
    typedef typename local_matrix_type::const_reference const_reference;
    typedef typename local_matrix_type::pointer pointer;
    typedef typename local_matrix_type::const_pointer const_pointer;
    typedef typename local_matrix_type::size_type size_type;

    typedef hpx::util::function<
        void(local_matrix_type&, matrix_bounds, matrix_bounds)
    > apply_function_type;

    typedef Policy policy_type;
    typedef typename Policy::indexing_policy_type indexing_policy_type;
    typedef typename Policy::partitioning_policy_type partitioning_policy_type;
    typedef typename Policy::distribution_policy_type distribution_policy_type;
    typedef typename Policy::allocation_policy_type allocation_policy_type;

  private:
    local_matrix_type data_;

  public:
    void initialize_from_dimensions(
        size_type rows
      , size_type cols
      , const_reference init
      , matrix_offsets offsets 
        )
    {
        data_ = boost::move(local_matrix_type(rows, cols, init, offsets));
    }

    void initialize_from_matrix(
        local_matrix_type const& m
      , matrix_offsets offsets 
        )
    {
        data_ = boost::move(local_matrix_type(m, offsets));
    }

    value_type lookup(
        size_type row
      , size_type col
        )
    {
        return data_(row, col);
    }

    // TODO: Allow functions with return values to be used.
    void apply(
        apply_function_type const& f
      , matrix_bounds lower
      , matrix_bounds upper
        )
    {
        // TODO: Range checks.
        f(data_, lower, upper);
    }

    enum action_codes
    {
        action_initialize_from_dimensions
      , action_initialize_from_matrix
      , action_lookup
      , action_apply
    };

    HPX_DEFINE_COMPONENT_ACTION(distributed_submatrix, initialize_from_dimensions);
    HPX_DEFINE_COMPONENT_ACTION(distributed_submatrix, initialize_from_matrix);
    HPX_DEFINE_COMPONENT_ACTION(distributed_submatrix, lookup);
    HPX_DEFINE_COMPONENT_ACTION(distributed_submatrix, apply);
};

typedef distributed_submatrix<
    float
  , distributed_matrix_policy<
        policy::column_major_indexing
    >
> rfc_distributed_submatrix;

typedef distributed_submatrix<
    float
  , distributed_matrix_policy<
        policy::row_major_indexing
    >
> rfr_distributed_submatrix;

typedef distributed_submatrix<
    double
  , distributed_matrix_policy<
        policy::column_major_indexing
    >
> rdc_distributed_submatrix;

typedef distributed_submatrix<
    double
  , distributed_matrix_policy<
        policy::row_major_indexing
    >
> rdr_distributed_submatrix;

typedef distributed_submatrix<
    std::complex<float>
  , distributed_matrix_policy<
        policy::column_major_indexing
    >
> cfc_distributed_submatrix;

typedef distributed_submatrix<
    std::complex<float>
  , distributed_matrix_policy<
        policy::row_major_indexing
    >
> cfr_distributed_submatrix;

typedef distributed_submatrix<
    std::complex<double>
  , distributed_matrix_policy<
        policy::column_major_indexing
    >
> cdc_distributed_submatrix;

typedef distributed_submatrix<
    std::complex<double>
  , distributed_matrix_policy<
        policy::row_major_indexing
    >
> cdr_distributed_submatrix;

}}

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfc_distributed_submatrix::initialize_from_dimensions_action
  , rfc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfc_distributed_submatrix::initialize_from_matrix_action
  , rfc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfc_distributed_submatrix::lookup_action
  , rfc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfc_distributed_submatrix::apply_action
  , rfc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfr_distributed_submatrix::initialize_from_dimensions_action
  , rfr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfr_distributed_submatrix::initialize_from_matrix_action
  , rfr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfr_distributed_submatrix::lookup_action
  , rfr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rfr_distributed_submatrix::apply_action
  , rfr_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdc_distributed_submatrix::initialize_from_dimensions_action
  , rdc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdc_distributed_submatrix::initialize_from_matrix_action
  , rdc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdc_distributed_submatrix::lookup_action
  , rdc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdc_distributed_submatrix::apply_action
  , rdc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdr_distributed_submatrix::initialize_from_dimensions_action
  , rdr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdr_distributed_submatrix::initialize_from_matrix_action
  , rdr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdr_distributed_submatrix::lookup_action
  , rdr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::rdr_distributed_submatrix::apply_action
  , rdr_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfc_distributed_submatrix::initialize_from_dimensions_action
  , cfc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfc_distributed_submatrix::initialize_from_matrix_action
  , cfc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfc_distributed_submatrix::lookup_action
  , cfc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfc_distributed_submatrix::apply_action
  , cfc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfr_distributed_submatrix::initialize_from_dimensions_action
  , cfr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfr_distributed_submatrix::initialize_from_matrix_action
  , cfr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfr_distributed_submatrix::lookup_action
  , cfr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cfr_distributed_submatrix::apply_action
  , cfr_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdc_distributed_submatrix::initialize_from_dimensions_action
  , cdc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdc_distributed_submatrix::initialize_from_matrix_action
  , cdc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdc_distributed_submatrix::lookup_action
  , cdc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdc_distributed_submatrix::apply_action
  , cdc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdr_distributed_submatrix::initialize_from_dimensions_action
  , cdr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdr_distributed_submatrix::initialize_from_matrix_action
  , cdr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdr_distributed_submatrix::lookup_action
  , cdr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION_DECLARATION(
    hpxla::server::cdr_distributed_submatrix::apply_action
  , cdr_distributed_submatrix_apply_action);

#endif // HPXLA_8F16F3F2_9DEB_4D29_9657_19EA59788895

