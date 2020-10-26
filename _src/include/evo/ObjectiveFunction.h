//
// Created by Ciaran Welsh on 27/09/2020.
//

#ifndef EVOGEN_OBJECTIVEFUNCTION_H
#define EVOGEN_OBJECTIVEFUNCTION_H

#include "evo/ExperimentSet.h"
#include "rr/rrRoadRunner.h"

/**
 * Plan
 * -----
 * - Some objective function can only be used on some experiment types.
 * - For instance:
 *      timeseries_rss = sum [ (exp_ti - sim_ti)^2 / err_ti ]
 *   Would be inappropriate for for perturbation data
 * - Objective function needs to take experiment as argument
 */

using namespace rr;

namespace evo {

    enum ObjectiveFunctionType {
        EVO_TIMESERIES_RSS,
        EVO_PERTURBATION_RSS,
        EVO_TIMESERIES_LIKELIHOOD,
    };

    class ObjectiveFunction {

        /**
         * @brief returns an ObjectiveFunctionType indication as to
         * this ObjectiveFunction objects type. Not implemented in the
         * base class and subclasses must implement.
         */
        virtual ObjectiveFunctionType getObjectiveFunctionType() = 0;

        ExperimentSet& experimentSet_;

    public:

        double fitness;

        /**
         * @brief Instantiate an ObjectiveFunction
         * @details Experiment is passed in by pointer to support polymorphism
         */
        ObjectiveFunction(const ExperimentSet& experimentSet, const RoadRunner& rr);

        virtual double compute() = 0;
    };


    class TimeseriesRSS;
}

#endif //EVOGEN_OBJECTIVEFUNCTION_H
