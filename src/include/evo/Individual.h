//
// Created by Ciaran Welsh on 27/09/2020.
//

#ifndef EVOGEN_INDIVIDUAL_H
#define EVOGEN_INDIVIDUAL_H

#include "rr/rrRoadRunner.h"
#include "evo/TypeDefs.h"

using namespace rr;


namespace evo {


    /**
     * @brief an Individual has a RoadRunner instance
     */
    class Individual {

        /**
         * @brief Refers to the MPI rank that this Individual belongs to
         * @details 0 when MPI world size is 1 else 0 <= rank <= world_size
         */
        int rank_ = 0;

        /**
         * @brief the underlying model that performs the simulation
         */
        RoadRunnerSharedPtr rr_;

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
        explicit Individual(const RoadRunner &rr);

        /**
         * @brief construct an Individual from a ptr to RoadRunner instance
         */
        explicit Individual(RoadRunnerSharedPtr rr);

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
         * @brief get the RoadRunner model that is bound to this Individual.
         * @returns shared pointer to the RoadRunner instance.
         */
        [[nodiscard]] RoadRunnerSharedPtr getRRPtr() const;

        void setRR(std::unique_ptr<RoadRunner> rr);

        void setRank(int rank);

    };

    using IndividualPtr = std::unique_ptr<Individual>;


    /**
     * @brief A vector of unique pointers to Individual, which contains RoadRunner Model
     */
    using IndividualPtrVector = std::vector<IndividualPtr>;

    /**
     * @brief a vector of vectors containing unique pointers to Individual objects
     * which contain RoadRunner models.
     * @details this structure is used for MPI, where the first index is
     * the MPI rank and the second contains IndividualPtr objecst.
     */
    using NestedIndividualPtrVector = std::vector<IndividualPtrVector>;

}

#endif //EVOGEN_INDIVIDUAL_H
