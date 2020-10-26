//
// Created by Ciaran on 08/09/2020.
//

#include "rr/rrRoadRunner.h"
using namespace rr;


int main() {

    bool RUN_SIMULATION = true;

    auto t1 = std::chrono::high_resolution_clock::now();

    int N = 100;

    SimulateOptions options;
    options.start = 0.0;
    options.duration = 1000;
    options.steps = 1001;

    for (int i = 0; i < N; i++) {
        RoadRunner rr;

        rr.addCompartment("Comp", 1, false);
        rr.addSpecies("S1", "Comp", 10.0, false, false, "", false);
        rr.addSpecies("S2", "Comp", 0.0, false, false, "", false);
        rr.addParameter("k1", 0.1, false);
        rr.addReaction("R1", std::vector<std::string>({"S1"}), std::vector<std::string>({"S2"}), "k1*S1", true);

        if (RUN_SIMULATION)
            rr.simulate(&options);

    }
    //It took : 2443 milliseconds to build 100 models --> build networks only
    // It took : 2698 milliseconds to build 100 models --> plus simulation of 1000 steps
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "It took : " << duration << " milliseconds to build " << N << " models.";
}