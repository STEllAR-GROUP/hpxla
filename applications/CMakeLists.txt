# Copyright (c) 2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(subdirs
    smith_waterman   
   )

foreach(subdir ${subdirs})
  add_hpx_pseudo_target(applications.${subdir})
  add_subdirectory(${subdir})
  add_hpx_pseudo_dependencies(applications applications.${subdir})
endforeach()

