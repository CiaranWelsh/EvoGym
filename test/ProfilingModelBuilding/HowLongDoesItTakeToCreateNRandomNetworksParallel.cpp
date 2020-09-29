/**
 * Create N random networks with M cores. The run_simulation optional parameter is boolean and
 * will run a simulation if true.
 *
 * @details networks all have 1 compartment, 1 boundary species, 4 floating species and 10 reactions.
 * The rate laws are randomly selected from uni-uni or uni-bi. Parameter values are drawn from a uniform distribution
 * between 0.1 and 10 for kinetic parameters, 0 and 10 for initial concentration parameters and the compartment size
 * is fixed at 1.
 *
 * Usage:
 *
 *     mpirun -n M HowLongDoesItTaketoCreateNRandomNetworksParallel N [run_simulation]
 */

#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/EvoRateLaw.h"
#include "mpi.h"
#include "rr/rrRoadRunner.h"

using namespace rr;
using namespace evo;

bool string2bool(const std::string &v) {
    return !v.empty() &&
           (strcasecmp(v.c_str(), "true") == 0 ||
            std::atoi(v.c_str()) != 0);
}

int main(int argc, char **argv) {
    auto t1 = std::chrono::high_resolution_clock::now();
    MPI_Init(nullptr, nullptr);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;// injected into program with mpirun command
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);


    int N = std::atoi(argv[1]);
    bool RUN_SIMULATION = false;

    if (argc == 3) {
        RUN_SIMULATION = string2bool(argv[2]);
    }


    int num_per_proc = N / world_size;
    int r = N % world_size;


    SimulateOptions sim_options;
    sim_options.start = 0.0;
    sim_options.duration = 1000;
    sim_options.steps = 1001;

    RateLaws rateLaws;
    rateLaws["uni-bi"] = RateLaw("uni-bi", "k*A", RoleMap({
                                                          {"k", EVO_PARAMETER},
                                                          {"A", EVO_SUBSTRATE},
                                                          {"B", EVO_PRODUCT},
                                                          {"C", EVO_PRODUCT},
                                                  }));
    rateLaws["uni-uni"] = RateLaw("uni-uni", "k*A",
                                  RoleMap({{"k", EVO_PARAMETER},
                                           {"A", EVO_SUBSTRATE},
                                           {"B", EVO_PRODUCT}
                                  }));


    RandomNetworkGeneratorOptions network_options(rateLaws);
    network_options.setNBoundarySpecies(1);
    network_options.setNFloatingSpecies(4);
    network_options.setNReactions(10);
    network_options.setNCompartments(1);

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
            for (int i = nstart; i < nend; i++) {
                RandomNetworkGenerator generator(network_options);

                if (RUN_SIMULATION) {
                    generator.getRR()->simulate(&sim_options);
                }
            }
        }
    }

    //It took : 2443 milliseconds to build 100 models --> build networks only
    // It took : 2698 milliseconds to build 100 models --> plus simulation of 1000 steps
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    if (world_rank == 0) {
        if (RUN_SIMULATION) {
            // only rank 0 prints this out
            std::cout << "It took : " << duration
                      << " milliseconds to build " << N << " models "
                      << "using " << world_size << " cores with 1000 step time series simulation" << std::endl;
        } else {
            // only rank 0 prints this out
            std::cout << "It took : " << duration
                      << " milliseconds to build " << N << " models "
                      << "using " << world_size << " cores without simulation" << std::endl;
        }
    }
    MPI_Finalize();
}