//
// Created by Ciaran on 09/09/2020.
//

#include "evo/Population.h"


namespace evo{

    Population::Population(const RandomNetworkGeneratorOptions& options, int population_size)
        : options_(options), size_(population_size){
        NaiveRandomNetworkGenerator rng(options);
        population_ = rng.generate(population_size);
    }


//    int Population::size() {
//        int size;
//        for (auto & i : population_)
//            size += i.size();
//        return size;
//    }

//    const std::vector<std::vector<std::unique_ptr<Individual>>> &Population::getPopulation() const {
//        return population_;
//    }

//    void Population::setPopulation(const std::vector<std::vector<std::unique_ptr<Individual>>> &population) {
//        population_ = population;
//    }


}