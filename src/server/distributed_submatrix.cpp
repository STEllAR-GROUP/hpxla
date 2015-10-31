////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpxla/server/distributed_submatrix.hpp>

HPX_REGISTER_COMPONENT_MODULE();

typedef hpx::components::managed_component<
    hpxla::server::rfc_distributed_submatrix
> rfc_distributed_submatrix_type;

typedef hpx::components::managed_component<
    hpxla::server::rfr_distributed_submatrix
> rfr_distributed_submatrix_type;

typedef hpx::components::managed_component<
    hpxla::server::rdc_distributed_submatrix
> rdc_distributed_submatrix_type;

typedef hpx::components::managed_component<
    hpxla::server::rdr_distributed_submatrix
> rdr_distributed_submatrix_type;

typedef hpx::components::managed_component<
    hpxla::server::cfc_distributed_submatrix
> cfc_distributed_submatrix_type;

typedef hpx::components::managed_component<
    hpxla::server::cfr_distributed_submatrix
> cfr_distributed_submatrix_type;

typedef hpx::components::managed_component<
    hpxla::server::cdc_distributed_submatrix
> cdc_distributed_submatrix_type;

typedef hpx::components::managed_component<
    hpxla::server::cdr_distributed_submatrix
> cdr_distributed_submatrix_type;

HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    rfc_distributed_submatrix_type, rfc_distributed_submatrix);
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    rfr_distributed_submatrix_type, rfr_distributed_submatrix);
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    rdc_distributed_submatrix_type, rdc_distributed_submatrix);
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    rdr_distributed_submatrix_type, rdr_distributed_submatrix);
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    cfc_distributed_submatrix_type, cfc_distributed_submatrix);
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    cfr_distributed_submatrix_type, cfr_distributed_submatrix);
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    cdc_distributed_submatrix_type, cdc_distributed_submatrix);
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    cdr_distributed_submatrix_type, cdr_distributed_submatrix);

//HPX_DEFINE_GET_COMPONENT_TYPE(rfc_distributed_submatrix_type::wrapped_type);
//HPX_DEFINE_GET_COMPONENT_TYPE(rfr_distributed_submatrix_type::wrapped_type);
//HPX_DEFINE_GET_COMPONENT_TYPE(rdc_distributed_submatrix_type::wrapped_type);
//HPX_DEFINE_GET_COMPONENT_TYPE(rdr_distributed_submatrix_type::wrapped_type);
//HPX_DEFINE_GET_COMPONENT_TYPE(cfc_distributed_submatrix_type::wrapped_type);
//HPX_DEFINE_GET_COMPONENT_TYPE(cfr_distributed_submatrix_type::wrapped_type);
//HPX_DEFINE_GET_COMPONENT_TYPE(cdc_distributed_submatrix_type::wrapped_type);
//HPX_DEFINE_GET_COMPONENT_TYPE(cdr_distributed_submatrix_type::wrapped_type);

HPX_REGISTER_ACTION(
    hpxla::server::rfc_distributed_submatrix::initialize_from_dimensions_action
  , rfc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::rfc_distributed_submatrix::initialize_from_matrix_action
  , rfc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::rfc_distributed_submatrix::lookup_action
  , rfc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::rfc_distributed_submatrix::apply_action
  , rfc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION(
    hpxla::server::rfr_distributed_submatrix::initialize_from_dimensions_action
  , rfr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::rfr_distributed_submatrix::initialize_from_matrix_action
  , rfr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::rfr_distributed_submatrix::lookup_action
  , rfr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::rfr_distributed_submatrix::apply_action
  , rfr_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION(
    hpxla::server::rdc_distributed_submatrix::initialize_from_dimensions_action
  , rdc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::rdc_distributed_submatrix::initialize_from_matrix_action
  , rdc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::rdc_distributed_submatrix::lookup_action
  , rdc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::rdc_distributed_submatrix::apply_action
  , rdc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION(
    hpxla::server::rdr_distributed_submatrix::initialize_from_dimensions_action
  , rdr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::rdr_distributed_submatrix::initialize_from_matrix_action
  , rdr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::rdr_distributed_submatrix::lookup_action
  , rdr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::rdr_distributed_submatrix::apply_action
  , rdr_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION(
    hpxla::server::cfc_distributed_submatrix::initialize_from_dimensions_action
  , cfc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::cfc_distributed_submatrix::initialize_from_matrix_action
  , cfc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::cfc_distributed_submatrix::lookup_action
  , cfc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::cfc_distributed_submatrix::apply_action
  , cfc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION(
    hpxla::server::cfr_distributed_submatrix::initialize_from_dimensions_action
  , cfr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::cfr_distributed_submatrix::initialize_from_matrix_action
  , cfr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::cfr_distributed_submatrix::lookup_action
  , cfr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::cfr_distributed_submatrix::apply_action
  , cfr_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION(
    hpxla::server::cdc_distributed_submatrix::initialize_from_dimensions_action
  , cdc_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::cdc_distributed_submatrix::initialize_from_matrix_action
  , cdc_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::cdc_distributed_submatrix::lookup_action
  , cdc_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::cdc_distributed_submatrix::apply_action
  , cdc_distributed_submatrix_apply_action);

HPX_REGISTER_ACTION(
    hpxla::server::cdr_distributed_submatrix::initialize_from_dimensions_action
  , cdr_distributed_submatrix_initialize_from_dimensions_action);
HPX_REGISTER_ACTION(
    hpxla::server::cdr_distributed_submatrix::initialize_from_matrix_action
  , cdr_distributed_submatrix_initialize_from_matrix_action);
HPX_REGISTER_ACTION(
    hpxla::server::cdr_distributed_submatrix::lookup_action
  , cdr_distributed_submatrix_lookup_action);
HPX_REGISTER_ACTION(
    hpxla::server::cdr_distributed_submatrix::apply_action
  , cdr_distributed_submatrix_apply_action);


