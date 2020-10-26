
#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/TypeDefs.h"
#include "mpi.h"

#include "rr/rrRoadRunner.h"

using namespace evo;
using namespace rr;


int main(){

    long long avg_duration = 0.0;
    long long sum_of_durations = 0.0;
    auto start_time = std::chrono::high_resolution_clock::now();

    int N = 10000;

    // initialize MPI
    MPI_Init(nullptr, nullptr);

    // Find out rank and world size
    int world_rank;
    int world_size;// injected into program with mpirun command. Default is 1.

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//    LOG("World rank: " << world_rank << "; world size: " << world_size);

    // create our storage structure to have the world_size elements
    NestedRoadRunnerPtrVector rr_vec(world_size);

    int num_per_proc = N / world_size;
    int r = N % world_size;

//    LOG("Number per rocesses: " << num_per_proc << " ; remainder: " << r);

    // todo think about how we can generalize this logic so that we do
    // not need to rewrite it for everything that we do with mpi.
    // note it might be possible to follow the decorator pattern.


    RandomNetworkGeneratorOptions options(massActionRateLaws());
    NaiveRandomNetworkGenerator generator(options);
    for (int rank = 0; rank < world_size; rank++) {

        // only when this nodes rank comes up do we do anything
        if (rank == world_rank) {

            int nstart;
            int nend;
            if (rank < r) {// handle remainder
                nstart = rank * (num_per_proc + 1);
                nend = nstart + num_per_proc;
            } else {
                nstart = rank * num_per_proc + r;
                nend = nstart + (num_per_proc - 1);
            }
//            std::cout << "rank " << rank << "; nstart: " << nstart << "; nend: " << nend << std::endl;
//            LOG("doing rank: " << rank << "'s work, which starts on " << nstart << " and ends on " << nend);
            for (int i = nstart; i < nend + 1; i++) { // nend + 1 so that we have open intervals (0, 3) for instance is 4 items
                auto t1 = std::chrono::high_resolution_clock::now();
                if (i % 100 == 0){
                    long long time_remaining = ((N/world_size)-i) * avg_duration;
                    std::cout << "building model " << i << "; Estimated time remaining is: " << time_remaining << " milliseconds or " << time_remaining/1000  << " seconds or "<< time_remaining/(1000*60)  << " minutes" << std::endl;
                }
                rr_vec[rank].push_back(generator.generate());
                auto t2 = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();


                sum_of_durations += duration;
                long long target = (1/((N/world_size)-1)) *sum_of_durations;
                avg_duration = duration + (1/(N/world_size))*(target - duration);
            }
        }
    }

    MPI_Finalize();

    return 0;
}

















