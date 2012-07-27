# Copyright (c) 2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(apps
    serial_smith_waterman
    naive_smp_smith_waterman
    blocked_smp_smith_waterman
   )

set(serial_smith_waterman_FLAGS
    DEPENDENCIES ${HPX_BOOST_PROGRAM_OPTIONS_LIBRARY} NOLIBS)

add_definitions(-DHPX_ACTION_ARGUMENT_LIMIT=10)
add_definitions(-DHPX_FUNCTION_LIMIT=13)

foreach(app ${apps})
  add_hpx_executable(${app} SOURCES ${app}.cpp ${${apps}_FLAGS}) 

  # Add a custom target for this example.
  add_hpx_pseudo_target(applications.smith_waterman.${app})

  # Make pseudo-targets depend on master pseudo-target.
  add_hpx_pseudo_dependencies(applications.smith_waterman
                              applications.smith_waterman.${app})

  # Add dependencies to pseudo-target.
  add_hpx_pseudo_dependencies(applications.smith_waterman.${app} ${app}_exe)
endforeach()

set_target_properties(serial_smith_waterman_exe PROPERTIES
                      COMPILE_FLAGS -DHPXLA_NO_LIBHPX)

