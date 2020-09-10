//
// Created by Ciaran on 10/09/2020.
//

#ifndef EVOGYM_SEED_H
#define EVOGYM_SEED_H

#include "NumCpp.hpp"

#ifndef SEED
#define SEED std::chrono::system_clock::now().time_since_epoch().count()
#endif

#define SET_CLOCK_SEED nc::random::seed(SEED);

#endif//EVOGYM_SEED_H
