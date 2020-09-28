//
// Created by Ciaran Welsh on 27/09/2020.
//

#include "include/evo/Individual.h"


namespace evo{

    const RoadRunner &Individual::getRR() const {
        return *rr_;
    }

    Individual::Individual(RoadRunner rr) : rr_(std::make_unique<RoadRunner>(rr)) {}

    void Individual::setRR( std::unique_ptr<RoadRunner> rr) {
        rr_ = std::move(rr);
    }

    int Individual::getRank() const {
        return rank;
    }
}

