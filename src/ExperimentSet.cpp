//
// Created by Ciaran Welsh on 27/09/2020.
//

#include "include/evo/ExperimentSet.h"

#include <utility>

namespace evo{

    ExperimentSet::ExperimentSet(std::vector<Experiment*> experiments)
        : experiments_(std::move(experiments)){}

    ExperimentSet::ExperimentSet(Experiment* experiment) {
        experiments_.push_back(experiment);
    }

    ExperimentSet &ExperimentSet::addExperiment(Experiment* experiment) {
        experiments_.push_back(experiment);
        return *this;
    }

    int ExperimentSet::size() {
        return experiments_.size();
    }
}















