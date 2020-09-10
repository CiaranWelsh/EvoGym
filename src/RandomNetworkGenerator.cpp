//
// Created by Ciaran on 09/09/2020.
//

#include "evo/RandomNetworkGenerator.h"
#include <chrono>

namespace evo {

    RandomNetworkGenerator::RandomNetworkGenerator(const NetworkGenerationOptions &options)
        : options_(options) {
        createCompartments();
    }

    const NetworkGenerationOptions &RandomNetworkGenerator::getOptions() const {
        return options_;
    }

    const RoadRunner &RandomNetworkGenerator::getRr() const {
        return rr;
    }

    double RandomNetworkGenerator::getRandomDouble(double lower, double higher) {
        nc::random::randn<double>(nc::Shape(3,4))

        if (lower == higher) {
            return lower;
        } else {
            return stats::runif(lower, higher);
        }
    }

    std::string RandomNetworkGenerator::selectRandomCompartment() {
        if (rr.getNumberOfCompartments() == 1) {
            return rr.getCompartmentIds()[0];
        } else {
            int compartment_index;
            if (getOptions().getNCompartments() > 1) {
                compartment_index =
                        std::rand() % getOptions().getNCompartments() + 1;// +1 for inclusive open boundaries
            }
            return rr.getCompartmentIds()[compartment_index];
        }
    }

    std::string RandomNetworkGenerator::selectRandomSpecies() {
        std::vector<std::string> species = rr.getBoundarySpeciesIds();
        std::vector<std::string> floating = rr.getFloatingSpeciesIds();
        // all species
        species.insert(floating.end(), floating.begin(), floating.end());
        return species[getRandomInt(0, species.size())];
    }

    void RandomNetworkGenerator::createCompartments() {
        std::ostringstream id;
        for (int i = 0; i < options_.getNCompartments(); i++) {
            double val = getRandomDouble(getOptions().getCompartmentLowerBound(),
                                         getOptions().getCompartmentUpperBound());
            id << "C" << i;
            rr.addCompartment(id.str(), val, false);
            id.flush();
        }
    }

    void RandomNetworkGenerator::createFloatingSpecies() {
        for (int i = 0; i < getOptions().getNFloatingSpecies(); i++) {
            double val = getRandomDouble(
                    getOptions().getSpeciesLowerBound(),
                    getOptions().getSpeciesUpperBound());
            std::ostringstream id;
            id << "S" << i;
            std::string comp = selectRandomCompartment();
            rr.addSpecies(id.str(), comp, val, false, false, "", false);
        }
    }


    int RandomNetworkGenerator::getRandomInt(int lower, int higher) const {


        int open_interval = getOptions().getBoundarySpeciesUpperBound() - getOptions().getBoundarySpeciesLowerBound();
        if (open_interval == 0) {
            return lower;
        } else {
            return std::rand() % higher + lower + 1;
        }
    }


    void RandomNetworkGenerator::createBoundarySpecies() {
        for (int i = 0; i < getOptions().getNBoundarySpecies(); i++) {
            // When >1 compartment, generate random assignment
            std::string comp = selectRandomCompartment();
            double val = getRandomInt(
                    getOptions().getBoundarySpeciesLowerBound(),
                    getOptions().getBoundarySpeciesUpperBound());
            std::ostringstream id;
            id << "S" << i;
            rr.addSpecies(id.str(), comp, val, true, true, "", false);
            id.flush();
        }
    }

    RateLaw RandomNetworkGenerator::getRandomRateLaw() const {
        // select a rate law at random.
        std::cout <<__FILE__<<":"<<__LINE__<<std::endl;

        std::vector<RateLaw> keys;
        std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
        for (auto &it : getOptions().getRateLaws()) {
            std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
            keys.push_back(it.second);
        }
        std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
        int random_rate_law_index = getRandomInt(0, getOptions().getRateLaws().size());
        std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
        return keys[random_rate_law_index];
    }

    void RandomNetworkGenerator::createReactions() {
        // select a random rate law
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        RateLaw rateLaw = getRandomRateLaw();
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        //        const RoleMap& roles = rateLaw.getRoles() ;
        //        std::cout << roles.size() << std::endl;
        //        for (auto &it: roles){
        //            std::cout << "first: " << it.first << ", second: " << it.second << std::endl;
        //        }
        //        rr.addReaction()
    }

    double RandomNetworkGenerator::createParameterValue() {
        return 0;
    }

    RoadRunner *RandomNetworkGenerator::generate() {
        return nullptr;
    }
}// namespace evo