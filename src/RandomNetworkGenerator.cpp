//
// Created by Ciaran on 09/09/2020.
//

#include "evo/RandomNetworkGenerator.h"
#include "../third_party/NumCpp/include/NumCpp/NdArray.hpp"
#include "../third_party/NumCpp/include/NumCpp/Random/randInt.hpp"
#include <chrono>


namespace evo {

    RandomNetworkGenerator::RandomNetworkGenerator(const NetworkGenerationOptions &options)
        : options_(options) {
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        createCompartments();
        //        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        //        createBoundarySpecies();
        //        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        //        createFloatingSpecies();
        //        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        //        createReactions();
        //        selectRandomCompartment();
        //        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        //        selectRandomSpecies(2);
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        //        createCompartments();
    }

    const NetworkGenerationOptions &RandomNetworkGenerator::getOptions() const {
        return options_;
    }

    const RoadRunner &RandomNetworkGenerator::getRr() const {
        return rr;
    }

    std::string RandomNetworkGenerator::selectRandomCompartment() {
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        //        if (getOptions().getNCompartments() != rr.getNumberOfCompartments()) {
        //            std::ostringstream err;
        //            err << "Expected to have " << rr.getNumberOfCompartments()
        //                << " compartments in model \""
        //                << rr.getModelName() << "\" but instead found " << getOptions().getNCompartments();
        //            THROW_LOGIC_ERROR(err.str());
        //        }
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        int random_index = nc::random::randInt<int>(0, options_.getNCompartments());
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        return rr.getCompartmentIds()[random_index];
    }

    std::vector<std::string> RandomNetworkGenerator::selectRandomSpecies(int n) {
        std::vector<std::string> species = rr.getBoundarySpeciesIds();
        std::vector<std::string> floating = rr.getFloatingSpeciesIds();

        // all species
        species.insert(floating.end(), floating.begin(), floating.end());

        nc::NdArray<int> s(species.size());
        std::cout << s << std::endl;

        if (n > species.size()) {
            std::ostringstream err;
            err << "Requested selecting "
                << n
                << " random species without replacement but only "
                << species.size() << " species exist.";
            LOGIC_ERROR(err.str());
        }
        // do the sampling
        nc::NdArray<int> species_indices = nc::random::choice(s, n, false);

        // convert indices into the strings we need.
        std::vector<std::string> out;
        for (auto &i : species_indices) {
            if (i < options_.getNBoundarySpecies()) {
                out.push_back(rr.getBoundarySpeciesIds()[i]);
            } else {
                int idx = i - options_.getNBoundarySpecies();
                out.push_back(rr.getFloatingSpeciesIds()[idx]);
            }
        }
        return out;
    }

    void RandomNetworkGenerator::createCompartments() {
        std::ostringstream id;
        for (int i = 0; i < options_.getNCompartments(); i++) {
            double val = options_.getCompartmentUpperBound();
            if (options_.getCompartmentLowerBound() != options_.getCompartmentUpperBound()) {
                val = nc::random::uniform(options_.getCompartmentLowerBound(),
                                          options_.getCompartmentUpperBound());
            }
            bool forceRegenerate = false;
            if (i == options_.getNCompartments() - 1)
                forceRegenerate = true;
            id << "C" << i;
            rr.addCompartment(id.str(), val, forceRegenerate);// regenerate model on last iter
            id.str(std::string());                            // clear the stream
        }
    }

    void RandomNetworkGenerator::createFloatingSpecies() {
        std::ostringstream id;
        for (int i = 0; i < options_.getNFloatingSpecies(); i++) {
            id << "S" << i;
            double val = options_.getSpeciesUpperBound();
            if (options_.getSpeciesLowerBound() != options_.getSpeciesUpperBound()) {
                val = nc::random::uniform(options_.getSpeciesLowerBound(),
                                          options_.getSpeciesUpperBound());
            }
            bool forceRegenerate = false;
            if (i == options_.getNFloatingSpecies() - 1)
                forceRegenerate = true;
            std::string comp = selectRandomCompartment();
            rr.addSpecies(id.str(), comp, val, false, false, "", forceRegenerate);
            id.str(std::string());
        }
    }

    void RandomNetworkGenerator::createBoundarySpecies() {
        std::ostringstream id;
        for (int i = 0; i < options_.getNBoundarySpecies(); i++) {
            id << "S" << i;
            int val = options_.getBoundarySpeciesUpperBound();
            if (options_.getBoundarySpeciesLowerBound() != options_.getBoundarySpeciesUpperBound()) {
                val = nc::random::randInt(options_.getBoundarySpeciesLowerBound(),
                                          options_.getBoundarySpeciesUpperBound());
            }
            bool forceRegenerate = false;
            if (i == options_.getNBoundarySpecies() - 1)
                forceRegenerate = true;
            std::string comp = selectRandomCompartment();
            rr.addSpecies(id.str(), comp, val, false, true, "", forceRegenerate);
            id.str(std::string());
        }
    }

    RateLaw RandomNetworkGenerator::getRandomRateLaw() const {
        // select a rate law at random.
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        std::vector<RateLaw> keys;
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        for (auto &it : options_.getRateLaws()) {
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            keys.push_back(it.second);
        }
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        if (options_.getRateLaws().empty()) {
            INVALID_ARGUMENT_ERROR("The RateLaw field of RandomNetworkGeneratorOptions is "
                                   "empty. Please give some rate laws to continue");
        }
        int random_rate_law_index = nc::random::randInt<int>(0, options_.getRateLaws().size());
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
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