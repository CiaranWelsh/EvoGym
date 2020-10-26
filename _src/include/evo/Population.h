//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_POPULATION_H
#define EVOGYM_POPULATION_H

#include <list>
#include "rr/rrRoadRunner.h"
#include "evo/evogym_export.h"
#include "evo/Individual.h"
#include "evo/TypeDefs.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/RandomNetworkGenerator.h"

using namespace rr;

namespace evo{
    /**
     * @brief A Population is a collection of Individuals.
     * @details A Population is only ever owned by Rank 0 from a MPI perspective.
     * The Individuals in the Population are pointers to blocks of memory
     * which may be on other nodes (non 0 MPI Rank).
     */
    class EVOGYM_EXPORT Population {

        const RandomNetworkGeneratorOptions& options_ = RandomNetworkGeneratorOptions();
        NestedIndividualPtrVector population_;
        int size_;

        

    public:
        /**
         * @brief default constructor for Population
         * @details when the default constructor is used
         * the caller must also manually set the population_
         * field using setPopulation
         */
        Population() = default;


        explicit Population(const RandomNetworkGeneratorOptions& options, int n_pop );
//
//        int size();
//
//        [[nodiscard]] const std::vector<std::vector<std::unique_ptr<Individual>>> &getPopulation() const;
//
//        void setPopulation(const std::vector<std::vector<std::unique_ptr<Individual>>> &population);


    };

}


#endif //EVOGYM_POPULATION_H
