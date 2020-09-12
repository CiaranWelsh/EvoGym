#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"

using namespace evo;

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    RateLaw uni_uni = RateLaw(
            "uni-uni",
            "k*A",
            RoleMap({
                    {"k", EVO_PARAMETER},
                    {"A", EVO_SUBSTRATE}})
            );
    RateLaw uni_bi = RateLaw(
            "uni-bi",
            "k*A",
            RoleMap({
                    {"k", EVO_PARAMETER},
                    {"A", EVO_SUBSTRATE},
                    {"B", EVO_PRODUCT},
            }));
    RateLaws rateLaws;
    rateLaws["uni-uni"] = uni_uni;
    rateLaws["uni-bi"] = uni_bi;

    // N iterations
    int N = 100;

    RandomNetworkGeneratorOptions options(rateLaws);
    // These are defaults
    options.setNReactions(3)
            .setNFloatingSpecies(3)
            .setNBoundarySpecies(1)
            .setNCompartments(1)
            .setSpeciesLowerBound(0.1)      // uniform lower
            .setSpeciesUpperBound(10)       // uniform upper
            .setBoundarySpeciesLowerBound(0)// uniform discrete
            .setBoundarySpeciesUpperBound(1)// essentially on or off
            .setCompartmentLowerBound(1)    // fix compartment vol
            .setCompartmentUpperBound(1);

    for (int i = 0; i < N; i++) {
        RandomNetworkGenerator rng(options);
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "It took : " << duration << " milliseconds to build " << N << " models.";
}
