////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_9CB2E52C_DA45_498C_B44F_FDB93A90F66A)
#define HPXLA_9CB2E52C_DA45_498C_B44F_FDB93A90F66A

#include <hpxla/local_matrix.hpp>

#if !defined(HPXLA_NO_LIBHPX)
    #include <hpx/runtime/naming/name.hpp>
#endif

namespace hpxla { namespace policy
{

#if !defined(HPXLA_NO_LIBHPX)
    template <
        typename LocalMatrixPolicy  
    >
    struct prime_factor_partitioning
    {
        typedef local_matrix<boost::int64_t, LocalMatrixPolicy> offset_matrix;
        typedef local_matrix<hpx::naming::id_type, LocalMatrixPolicy> gid_matrix;
    
        static matrix_bounds submatrix_dimensions( 
            boost::uint64_t partitions
          , matrix_bounds bounds
            )
        {
            // IMPLEMENT
            return matrix_bounds();
        }
    
        static offset_matrix create_offsets(
            boost::uint64_t partitions
          , matrix_bounds bounds
            )
        {
            // IMPLEMENT
            return offset_matrix();
        }
    };
#endif

}}

#endif // HPXLA_9CB2E52C_DA45_498C_B44F_FDB93A90F66A

