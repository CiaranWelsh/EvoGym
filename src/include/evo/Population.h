//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_POPULATION_H
#define EVOGYM_POPULATION_H

#include <list>
#include "rr/rrRoadRunner.h"
#include "evogym_export.h"

using namespace rr;

namespace evo{
    class EVOGYM_EXPORT Population {
        std::list<RoadRunner> population_;

    public:
        Population() = default;

        int size();

    };

}


#endif //EVOGYM_POPULATION_H
