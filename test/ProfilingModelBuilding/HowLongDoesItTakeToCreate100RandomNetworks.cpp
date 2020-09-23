//
// Created by Ciaran on 08/09/2020.
//

#include "rr/rrRoadRunner.h"
#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/RateLaw.h"

using namespace rr;
using namespace evo;

int main() {

    bool RUN_SIMULATION = true;

    auto t1 = std::chrono::high_resolution_clock::now();

    int N = 100;

    SimulateOptions sim_options;
    sim_options.start = 0.0;
    sim_options.duration = 1000;
    sim_options.steps = 1001;

    RateLaws rateLaws;
    rateLaws["uni-bi"] = RateLaw("uni-bi", "k*A", RoleMap({{"k", EVO_PARAMETER}, {"A", EVO_SUBSTRATE}, {"B", EVO_PRODUCT}}));
    rateLaws["uni-uni"] = RateLaw("uni-uni", "k*A",
                    RoleMap({
                            {"k", EVO_PARAMETER},
                            {"A", EVO_SUBSTRATE}
                    }));


    RandomNetworkGeneratorOptions network_options(rateLaws);
    network_options.setNBoundarySpecies(1);
    network_options.setNFloatingSpecies(4);
    network_options.setNReactions(10);
    network_options.setNCompartments(1);


    for (int i = 0; i < N; i++) {
        RandomNetworkGenerator generator(network_options);
    }
    //It took : 2443 milliseconds to build 100 models --> build networks only
    // It took : 2698 milliseconds to build 100 models --> plus simulation of 1000 steps
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "It took : " << duration << " milliseconds to build " << N << " models.";
}