# Copyright (c) 2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(non_hpx_tests
    std_complex_cblas_compatibility
    local_matrix
    local_matrix_view
    local_blas_level_1
    local_blas_level_2
    local_blas_level_3
   )

foreach(test ${non_hpx_tests})
  add_hpx_executable(${test}_test SOURCES ${test}.cpp
                     DEPENDENCIES ${BLAS_LIBRARY} NOLIBS) 

  # Add a custom target for this example.
  add_hpx_pseudo_target(tests.${test})

  # Make pseudo-targets depend on master pseudo-target.
  add_hpx_pseudo_dependencies(tests tests.${test})

  # Add dependencies to pseudo-target.
  add_hpx_pseudo_dependencies(tests.${test} ${test}_test_exe)
endforeach()

