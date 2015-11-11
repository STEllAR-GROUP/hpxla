# HPXLA: A HPX Linear Algebra Library

### To-Do:
-------------------
* [ ] Switchable assertions/exceptions
* [ ] Add policy template parameter to matrix classes
* [ ] Convert local BLAS functions to accept matrix classes with arbitrary policies

### Building
-------------------
HPXLA depends on HPX, ensure you have a recent hpx build installed to some location. 
If you don't wish to install HPX into your system you can simply set the flag 
`CMAKE_INSTALL_PREFIX` to the location of where you'll be building hpx (e.g. */home/example/build* is hpx will be built to that folder) while following the 
[hpx install tutorial](https://github.com/STEllAR-GROUP/hpx/#build-instructions).

You'll also need either BLAS or CBLAS, the easiest way to obtain either is via 
[atlas](math-atlas.sourceforge.net).

#### Linux
1. clone the master HPXLA git repository
  
   `git clone http://github.com/STEllAR-GROUP/hpxla.git`

2. create a build directory. HPXLA should be an out-of-tree build
  
   ```
   mkdir hpxla_build
   cd hpxla_build
   ```

3. Invoke CMake, note that you'll likely need to specify the same compiler used to build HPX
  
   ```
   cmake -DCMAKE_CXX_COMPILER=/usr/bin/compiler \
          -DHPX_ROOT=/path/to/hpxbuild           \
          /path/to/hpxla/source
   ```

   e.g.

   ```
   cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++  \
          -DHPX_ROOT=/home/dev/hpx_build     \
          ../hpxla
   ```

4. Make to build all targets

   `make`

