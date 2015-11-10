#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <hpxla/distributed_submatrix.hpp>


using hpxla::distributed_submatrix;
using hpxla::server::rfc_distributed_submatrix;
using hpxla::distributed_matrix_policy;
using hpxla::policy::column_major_indexing;

using hpx::find_here;

int hpx_main()
{
    {
        typedef rfc_distributed_submatrix matrix_type;
        typedef distributed_submatrix<
            float
          , distributed_matrix_policy<
                column_major_indexing> 
        > distributed_submatrix_type;
        
        distributed_submatrix_type dsm( 
            hpx::components::new_<matrix_type>(find_here()));

        dsm.initialize_non_blocking(5, 5, 1);

        for(int r = 0; r < 5; r++) {
            for(int c = 0; c < 5; c++) {
                HPX_TEST_EQ(dsm.lookup_sync(r, c), 1);
            }
        }

    }
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}
