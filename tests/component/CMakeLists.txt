# Copyright (c) 2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(component_tests
    distributed_submatrix
   )

foreach(test ${component_tests})
  
  add_hpx_executable(${test}_test 
    SOURCES ${test}.cpp
    DEPENDENCIES ${BLAS_LIBRARIES} 
    COMPONENT_DEPENDENCIES iostreams la)
  
  # Add a custom target for this example.
  add_hpx_pseudo_target(tests.component.${test})

  # Make pseudo-targets depend on master pseudo-target.
  add_hpx_pseudo_dependencies(tests tests.component.${test})

  # Add dependencies to pseudo-target.
  add_hpx_pseudo_dependencies(tests.component.${test} ${test}_test_exe)
endforeach()
