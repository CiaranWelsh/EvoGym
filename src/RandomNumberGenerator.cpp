//
// Created by Ciaran on 11/09/2020.
//
#include "evo/RandomNumberGenerator.h"

namespace evo {


    RandomNumberGenerator::RandomNumberGenerator(unsigned int seed){
        generator_.seed(seed);
    }


    double RandomNumberGenerator::uniform_real(double low, double high){
        std::uniform_real_distribution<double> unif(low, high);
        return unif(generator_);
    }

    int RandomNumberGenerator::uniform_int(int low, int high){
        std::uniform_int_distribution<int> unif(low, high);
        return unif(generator_);
    }
    void RandomNumberGenerator::setSeed(unsigned int seed) {
        generator_.seed(seed);
    }
    void RandomNumberGenerator::useClockSeed() {
        generator_.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }
    RandomNumberGenerator::RandomNumberGenerator() {
        useClockSeed();
    }


}// namespace evo
