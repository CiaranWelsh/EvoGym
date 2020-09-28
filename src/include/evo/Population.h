//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_POPULATION_H
#define EVOGYM_POPULATION_H

#include <list>
#include "rr/rrRoadRunner.h"
#include "evo/evogym_export.h"
#include "evo/Individual.h"

using namespace rr;

namespace evo{
    /**
     * @brief A Population is a collection of Individuals.
     * @details A Population is only ever owned by Rank 0 from a MPI perspective.
     * The Individuals in the Population are pointers to blocks of memory
     * which may be on other nodes (non 0 MPI Rank).
     */
    class EVOGYM_EXPORT Population {

        std::list<std::unique_ptr<Individual>> population_;

    public:
        Population() = default;

        int size();

    };

}


#endif //EVOGYM_POPULATION_H
