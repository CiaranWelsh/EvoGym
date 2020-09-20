//
// Created by Ciaran on 08/09/2020.
//
#include "mpi.h"
#include "rr/rrRoadRunner.h"
#include <algorithm>

using namespace rr;


int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    MPI_Init(NULL, NULL);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    bool RUN_SIMULATION = true;


    int N = 100;
    int num_per_proc = N / world_size;
    int r = N % world_size;

    SimulateOptions options;
    options.start = 0.0;
    options.duration = 1000;
    options.steps = 1001;

    /*
     * >>> 0 + 17
            17
            >>> 17+17
            34
            >>> 34+17
            51
            >>> 51+17
            68
            >>> 68 + 16
            84
            >>> 84 + 16
            100
            >>>
     */
    for (int rank = 0; rank < world_size; rank++) {
        if (rank == world_rank) {
            int nstart;
            int nend;
            if (rank < r){
                nstart = rank * (num_per_proc + 1);
                nend = nstart + num_per_proc;
            } else{
                nstart = rank * num_per_proc + r;
                nend = nstart + (num_per_proc - 1);
            }
            for (int i=nstart; i < nend; i ++){
                RoadRunner rr;
                rr.addCompartment("Comp", 1, false);
                rr.addSpecies("S1", "Comp", 10.0, false, false, "", false);
                rr.addSpecies("S2", "Comp", 0.0, false, false, "", false);
                rr.addParameter("k1", 0.1, false);
                rr.addReaction("R1", std::vector<std::string>({"S1"}), std::vector<std::string>({"S2"}), "k1*S1", true);
            }
            auto t2 = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();


            std::cout << "rank: " << rank << ": It took: " << duration << " milliseconds to build " << N << " models." << std::endl;
//            std::cout << "world size: " << world_size
//                      << "; rank: " << world_rank
//                      << "; rank < r: " << (rank < r)
//                      << "; r: " << r
//                      << "; n per rank: " << num_per_proc
//                      << "; nstart: " << nstart
//                      << "; nend: " << nend
//                      << std::endl;
        }
    }

    //
    //    for (int i = 0; i < N; i++) {
    //        RoadRunner rr;
    //
    //        rr.addCompartment("Comp", 1, false);
    //        rr.addSpecies("S1", "Comp", 10.0, false, false, "", false);
    //        rr.addSpecies("S2", "Comp", 0.0, false, false, "", false);
    //        rr.addParameter("k1", 0.1, false);
    //        rr.addReaction("R1", std::vector<std::string>({"S1"}), std::vector<std::string>({"S2"}), "k1*S1", true);
    //
    //        if (RUN_SIMULATION)
    //            rr.simulate(&options);
    //
    //    }options
    //It took : 2443 milliseconds to build 100 models --> build networks only
    MPI_Finalize();
    // It took : 2698 milliseconds to build 100 models --> plus simulation of 1000 steps

}