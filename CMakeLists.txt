# Copyright (c) 2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# TODO: Add versioning.
# TODO: Add install code.
# TODO: ATLAS/MKL/GSL selection.

cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(hpxla CXX)

################################################################################
include_directories(${hpxla_SOURCE_DIR})

if(HPX_ROOT)
    set(HPX_DIR "${HPX_ROOT}/lib/cmake/HPX")
endif()

if(HPX_DIR)
    message(STATUS "Searching for HPX in \"${HPX_ROOT}\" ...")
endif()

find_package(HPX REQUIRED)
include_directories(${HPX_INCLUDE_DIR})
link_directories(${HPX_LIBRARY_DIR})

message(STATUS "Found HPX: ${HPX_PREFIX}")

find_package(CBLAS)
link_directories(${CBLAS_LIBRARIES})

message(STATUS "Found BLAS: ${BLAS_LIBRARIES}")

################################################################################
add_hpx_pseudo_target(tests)
add_subdirectory(tests)

################################################################################
add_hpx_pseudo_target(applications)
add_subdirectory(applications)

################################################################################
add_subdirectory(src)

