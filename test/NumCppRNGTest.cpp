//
// Created by Ciaran on 12/09/2020.
//

#include <chrono>
#include "NumCpp.hpp"

class RNGOptions{
private:
    unsigned long long seed_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();

public:
    RNGOptions() {
        setSeed(seed_);
    }
    explicit RNGOptions(unsigned long long seed) {
        setSeed(seed);
    }
    unsigned long long int getSeed() const {
        return seed_;
    }
    void setSeed(unsigned long long int seed) {
        seed_ = seed;
    }
};


class ClassThatUsesRandomNumberGenerator {
    RNGOptions options_;

public:
    ClassThatUsesRandomNumberGenerator() = default;

    explicit ClassThatUsesRandomNumberGenerator(RNGOptions options)
            : options_(options){};

    const RNGOptions &getOptions() const {
        return options_;
    }
    void setOptions(const RNGOptions &options) {
        options_ = options;
    }

    double randomUniformDouble(double low, double high){
        return nc::random::uniform<double>(low, high);
    }

    int randomUniformInt(int low, int high){
        return nc::random::randInt(low, high);
    }
};


int main(){

    // no seed being set
    ClassThatUsesRandomNumberGenerator generator;
    std::cout << generator.getOptions().getSeed() << std::endl; // outputs a different number each time I run the program
    std::cout << generator.randomUniformDouble(0, 100) << std::endl; // outputs 78.6821 each time I run the program
}
