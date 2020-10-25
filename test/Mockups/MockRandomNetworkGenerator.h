//
// Created by Ciaran Welsh on 03/10/2020.
//

#ifndef EVOGEN_MOCKRANDOMNETWORKGENERATOR_H
#define EVOGEN_MOCKRANDOMNETWORKGENERATOR_H

#include "gmock/gmock.h"
#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"

using namespace evo;
using namespace ::testing;

class MockRandomNetworkGenerator : public RandomNetworkGenerator {
public:
    MOCK_METHOD(Compartments, createCompartments, (),  (override));

    MOCK_METHOD(BoundarySpecies, createBoundarySpecies, (),  (override));

    MOCK_METHOD(FloatingSpecies, createFloatingSpecies, (),  (override));

    MOCK_METHOD(Reactions, createReactions, (),  (override));
};


#endif //EVOGEN_MOCKRANDOMNETWORKGENERATOR_H
