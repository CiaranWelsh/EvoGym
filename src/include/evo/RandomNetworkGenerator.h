//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_RANDOMNETWORKGENERATOR_H
#define EVOGYM_RANDOMNETWORKGENERATOR_H

#include "stats.hpp"
#include "NumCpp.hpp"
#include "rr/rrRoadRunner.h"
#include "evo/NetworkGenerationOptions.h"
#include "evo/evo_error.h"


using namespace rr;

namespace evo{

    class RandomNetworkGenerator {
        const NetworkGenerationOptions& options_;

        void createCompartments();

        void createFloatingSpecies();

        void createBoundarySpecies();

        /**
         *
         * @details factory like method for generating parameter
         * values based on the appropriate fields inside RandomNetworkGenerator::options.
         * Parameters are randomly drawn from a uniform distribution, other distributions may
         * be supported later.
         */
        double createParameterValue();

        std::string selectRandomCompartment();


    public:
        RoadRunner rr;

        explicit RandomNetworkGenerator(const NetworkGenerationOptions& options );

        /**
         *
         * @details We return a pointer so that we do not need to copy or move
         * the instantiated roadrunner instance after its been created. We can
         * simply get a list/vector of pointers to networks.
         */
        RoadRunner* generate();

        const NetworkGenerationOptions &getOptions() const;

        const RoadRunner &getRr() const;

        static double getRandomDouble(double lower, double higher);

        int getRandomInt(int lower, int higher) const;

        std::vector<std::string> selectRandomSpecies(int n);

        RateLaw getRandomRateLaw() const;

        void createReactions();
    };
}



#endif //EVOGYM_RANDOMNETWORKGENERATOR_H
