//
// Created by Ciaran Welsh on 27/09/2020.
//

#ifndef EVOGEN_EXPERIMENTSET_H
#define EVOGEN_EXPERIMENTSET_H

#include <vector>
#include "evo/Experiment.h"

namespace evo {

    /**
     * @brief An ExperimentSet is a collection of Experiment objects.
     * @details Uses a vector of non-owning Experiment pointers.
     */
    class ExperimentSet {
        std::vector<Experiment*> experiments_;

    public:
        /**
         * @brief Default constructor for creating an empty ExperimentSet
         */
        ExperimentSet() = default;

        explicit ExperimentSet(std::vector<Experiment*> experiments);

        explicit ExperimentSet(Experiment* experiment);

        ExperimentSet& addExperiment(Experiment* experiment);

        int size();

        using ValidationSet = ExperimentSet;

    };
}


#endif //EVOGEN_EXPERIMENTSET_H
