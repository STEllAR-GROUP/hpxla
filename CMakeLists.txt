# Copyright (c) 2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# TODO: Add versioning.
# TODO: Add install code.
# TODO: ATLAS/MKL/GSL selection.

cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

project(hpxla CXX)

################################################################################
include_directories(${hpxla_SOURCE_DIR})

# TODO: Move this into a CMake macro.
if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/lib/hpx)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/lib/hpx)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/MinSizeRel/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/MinSizeRel/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/MinSizeRel/lib/hpx)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/RelWithDebInfo/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/RelWithDebInfo/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/RelWithDebInfo/lib/hpx)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/hpx)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/hpx)
endif()

################################################################################
# TODO: Move this into FindHPX.cmake.in.
if(NOT HPX_ROOT)
  if(NOT $ENV{HPX_LOCATION} STREQUAL "")
    set(HPX_ROOT $ENV{HPX_LOCATION})
  elseif(NOT $ENV{HPX_ROOT} STREQUAL "")
    set(HPX_ROOT $ENV{HPX_ROOT})
  endif()
endif()

set(HPX_ROOT "${HPX_ROOT}" CACHE PATH "The HPX installation to use." FORCE)

set(CMAKE_MODULE_PATH ${HPX_ROOT}/share/cmake-2.8/Modules)

find_package(HPX)

################################################################################
find_package(HPX_BLAS)
include_directories(${BLAS_INCLUDE_DIR})
link_directories(${BLAS_LIBRARY_DIR})

################################################################################
add_hpx_pseudo_target(tests)
add_subdirectory(tests)

