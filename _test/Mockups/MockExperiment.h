//
// Created by Ciaran Welsh on 28/09/2020.
//

#ifndef EVOGEN_MOCKEXPERIMENT_H
#define EVOGEN_MOCKEXPERIMENT_H

#include "gmock/gmock.h"
#include "evo/Experiment.h"

using namespace evo;
using namespace ::testing;

class MockExperiment : public Experiment {
public:
    MOCK_METHOD(void, calculateAverages, ());
    MOCK_METHOD(ExperimentType, experimentType, (),  (const));

};

#endif //EVOGEN_MOCKEXPERIMENT_H
