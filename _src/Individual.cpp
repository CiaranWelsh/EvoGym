//
// Created by Ciaran Welsh on 27/09/2020.
//

#include "include/evo/Individual.h"


namespace evo{

    RoadRunnerSharedPtr Individual::getRRPtr() const {
        return rr_;
    }

    Individual::Individual(const RoadRunner& rr) : rr_(std::make_unique<RoadRunner>(rr)) {}

    Individual::Individual(std::shared_ptr<RoadRunner> rr)
        : rr_(std::move(rr)){}

    void Individual::setRR( std::unique_ptr<RoadRunner> rr) {
        rr_ = std::move(rr);
    }

    void Individual::setRank(int rank) {
        rank_ = rank;
    }

    int Individual::getRank() const {
        return rank_;
    }
}

