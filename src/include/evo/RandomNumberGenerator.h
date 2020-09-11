//
// Created by Ciaran on 11/09/2020.
//

#ifndef EVOGYM_RANDOMNUMBERGENERATOR_H
#define EVOGYM_RANDOMNUMBERGENERATOR_H

#include <chrono>
#include <memory>
#include <random>

#ifndef CLOCK_SEED
#define CLOCK_SEED std::chrono::system_clock::now().time_since_epoch().count()
#endif

namespace evo {

    class RandomNumberGenerator {
    private:

        std::mt19937_64 generator_;

    public:
        RandomNumberGenerator();

        explicit RandomNumberGenerator(unsigned int seed);

        void setSeed(unsigned int seed);

        void useClockSeed();

        double uniform_real(double low, double high);

        int uniform_int(int low, int high);
    };


}

#endif//EVOGYM_RANDOMNUMBERGENERATOR_H
