//
// Created by Ciaran on 10/09/2020.
//

#ifndef EVOGYM_SEED_H
#define EVOGYM_SEED_H

#include "NumCpp.hpp"

#ifndef CLOCK_SEED
#define CLOCK_SEED std::chrono::system_clock::now().time_since_epoch().count()
#endif

namespace evo {

    /**
    * @brief an alternative to the macro for setting random seed
    */
//    void setSeed(unsigned int seed);

}// namespace evo

#endif//EVOGYM_SEED_H
