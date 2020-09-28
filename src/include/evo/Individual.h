//
// Created by Ciaran Welsh on 27/09/2020.
//

#ifndef EVOGEN_INDIVIDUAL_H
#define EVOGEN_INDIVIDUAL_H

#include "rr/rrRoadRunner.h"

using namespace rr;


namespace evo {


    /**
     * @brief an Individual has a RoadRunner instance
     */
    class Individual {


        int rank = 0;

        std::unique_ptr<RoadRunner> rr_;

    public:

        /**
         * @brief default constructor for an Individual
         * @details When the default constructor is used the caller
         * must use setRR to bind a RoadRunner instance to this Individual.
         */
        Individual() = default;

        /**
         * @brief construct an Individual from a RoadRunner instance
         */
        explicit Individual(RoadRunner rr);

        /**
         * @brief the rank refers to the MPI rank or
         * core of the process that instantiated this
         * Individual. When MPI is not being used,
         * the rank is 0. When MPI is being used,
         * this can be any integer between 0 and the number of
         * processes/cores being used.
         */
        [[nodiscard]] int getRank() const;

        /**
         * @brief get the RoadRunner model that is bound to this Invididual.
         * @returns the dereferenced unique pointer to the RoadRunner instane.
         */
        [[nodiscard]] const RoadRunner & getRR() const;

        void setRR( std::unique_ptr<RoadRunner> rr);

    };
}

#endif //EVOGEN_INDIVIDUAL_H
