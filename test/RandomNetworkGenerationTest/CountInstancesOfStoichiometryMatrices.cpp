#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/StoicCounter.h"

#include "rr/rrRoadRunner.h"

using namespace evo;
using namespace rr;

int main(int argc, char **argv) {
    int N = 100;

    RateLaws rateLaws;
    rateLaws["uni-uni"] = RateLaw("uni-uni", "k*A",
                                  RoleMap({{"k", EVO_PARAMETER},
                                           {"A", EVO_SUBSTRATE},
                                           {"B", EVO_PRODUCT}}));

    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNReactions(2);
    options.setNFloatingSpecies(2);
    options.setNBoundarySpecies(1);

    VectorOfMatrices<double> stoic;

    long long avg_duration = 0.0;
    long long sum_of_durations = 0.0;
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        auto t1 = std::chrono::high_resolution_clock::now();

        if (i % 100 == 0){
            long long time_remaining = (N-i) * avg_duration;
            std::cout << "building model " << i << "; Estimated time remaining is: " << time_remaining << " milliseconds or " << time_remaining/1000  << " seconds or "<< time_remaining/(1000*60)  << " minutes" << std::endl;
        }
        RandomNetworkGenerator generator(&options);
        stoic.push_back( generator.getRR()->getFullStoichiometryMatrix().getValues());
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();


        sum_of_durations += duration;
        long long target = (1/(N-1)) *sum_of_durations;
        avg_duration = duration + (1/N)*(target - duration);

    }

    StoicCounter<double> counter(stoic);
    std::cout << counter << std::endl;

    auto setIt = counter.getSetOfMatrices().begin();




    /*
     * output when N == 10000
     *{
        0: 249,
        1: 555,
        2: 567,
        3: 268,
        4: 572,
        5: 1038,
        6: 1134,
        7: 582,
        8: 581,
        9: 275,
        10: 1079,
        11: 558,
        12: 1158,
        13: 581,
        14: 495,
        15: 308
        }
     *
     *
     */

    /*
     * output when N = 100,000
     *
     * {
	0: 2771,
	1: 5615,
	2: 5526,
	3: 2793,
	4: 5531,
	5: 11233,
	6: 11000,
	7: 5573,
	8: 5459,
	9: 2796,
	10: 11039,
	11: 5512,
	12: 11158,
	13: 5500,
	14: 5635,
	15: 2859
}
     */
}
