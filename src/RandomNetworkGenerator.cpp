//
// Created by Ciaran on 09/09/2020.
//

#include "evo/RandomNetworkGenerator.h"
#include "NumCpp.hpp"
#include "evo/logger.h"
#include <chrono>
#include <regex>

/*
 * Idea for end to end testing
 * Pick a small network configuration and map out the complete set of
 * possible networks. You'll have to fix parameter values.
 * Then generate many random networks and count frequency. You
 * should get a normal uniform distribution
 *
 * A better name: Nevolution? For network evolution
 *
 * //todo use profiler to see if any optimization can be done for performance.
 *
 *
 */

namespace evo {


    RandomNetworkGenerator::RandomNetworkGenerator(RandomNetworkGeneratorOptions* options)
        : options_(options) {
        if (options->getSeed() == 0) {
            nc::random::seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        } else {
            // I suspect this will be a bug in the grans scheme of things
            // the seed will be set the same for every network generated.
            // so if we generate 10 networks we get 10 identical netowkrs.
            // solution woul dbe to seed at a level above this class.
            // todo reflect more on this when you have more code in place.
            nc::random::seed(options->getSeed());
        }

        createRRModel();
        createCompartments();
        createBoundarySpecies();
        createFloatingSpecies();
        assembleModel();
        // regenerate the finished model.
        getRR()->regenerate(true, false);
    }

    void RandomNetworkGenerator::createRRModel() {
        if (options_->getCoreSBML().empty()) {
            auto *rr = new RoadRunner();
            rr_ = std::unique_ptr<RoadRunner>(rr);
        } else {
            auto *rr = new RoadRunner(options_->getCoreSBML());
            rr_ = std::unique_ptr<RoadRunner>(rr);
        }
    }

    const std::unique_ptr<RoadRunner> &RandomNetworkGenerator::getRR() const {
        return rr_;
    }


    RandomNetworkGeneratorOptions *RandomNetworkGenerator::getOptions() const {
        return options_;
    }

    int RandomNetworkGenerator::selectRandomCompartmentIndex() {
        return nc::random::randInt<int>(0, options_->getNCompartments());
    }

    std::vector<int> RandomNetworkGenerator::sample_with_replacement(int nsamples, int npop) {
        if (nsamples > npop) {
            LOGIC_ERROR("The number of samples cannot be more than the size of the population when sampling"
                        "with replacement");
        }

        std::vector<int> out;
        for (int j = npop - nsamples + 1; j < npop + 1; j++) {
            auto random_number = nc::random::uniform<double>(0.0, 1.0);
            unsigned int t = 1 + (int) j * random_number;
            if (std::find(out.begin(), out.end(), t) != out.end()) {
                out.push_back(j);
            } else {
                out.push_back(t);
            }
        }

        // we subtract 1 from the output so that we have index friendly numbers
        // i.e. algorithm is 1 indexed and C++ is 0 indexed.
        for (int i = 0; i < out.size(); i++) {
            out[i] -= 1;
        }
        return out;
    }

    std::vector<int> RandomNetworkGenerator::selectRandomSpeciesIndex(int n) {
        int nspecies = options_->getNBoundarySpecies() + options_->getNFloatingSpecies();

        // check for the impossible
        if (n > nspecies) {
            std::ostringstream err;
            err << "Requested selecting "
                << n
                << " random boundary species without replacement but only "
                << nspecies << " species exist.";
            LOGIC_ERROR(err.str());
        }
        // do the sampling
        std::vector<int> species_indices = sample_with_replacement(n, nspecies);
        return species_indices;
    }

    void RandomNetworkGenerator::createCompartments() {
        std::ostringstream id;
        for (int i = 0; i < options_->getNCompartments(); i++) {
            double val = options_->getCompartmentUpperBound();
            if (options_->getCompartmentLowerBound() != options_->getCompartmentUpperBound()) {
                val = nc::random::uniform<double>(options_->getCompartmentLowerBound(),
                                                  options_->getCompartmentUpperBound());
            }
            id << "C" << i;
            compartments_.ids.push_back(id.str());
            compartments_.values.push_back(val);
            id.str(std::string());// clear the stream
        }
    }

    void RandomNetworkGenerator::createFloatingSpecies() {
        std::ostringstream id;
        for (int i = 0; i < options_->getNFloatingSpecies(); i++) {
            id << "S" << i;
            double val = options_->getSpeciesUpperBound();
            if (options_->getSpeciesLowerBound() != options_->getSpeciesUpperBound()) {
                val = nc::random::uniform<double>(options_->getSpeciesLowerBound(),
                                                  options_->getSpeciesUpperBound());
            }
            // With single compartment models, go and get the compartment name
            // with multiple compartment models, random selection
            int comp_index;
            if (options_->getNCompartments() == 1) {
                comp_index = 0;
            } else {
                comp_index = selectRandomCompartmentIndex();
            }
            floating_species_.ids.push_back(id.str());
            floating_species_.values.push_back(val);
            floating_species_.compartment_index.push_back(comp_index);
            id.str(std::string());
        }
    }
    void RandomNetworkGenerator::createBoundarySpecies() {
        std::ostringstream id;
        for (int i = 0; i < options_->getNBoundarySpecies(); i++) {
            id << "I" << i;
            double val = options_->getBoundarySpeciesUpperBound();
            if (options_->getBoundarySpeciesLowerBound() != options_->getBoundarySpeciesUpperBound()) {
                val = nc::random::uniform<double>(options_->getBoundarySpeciesLowerBound(),
                                                  options_->getBoundarySpeciesUpperBound());
            }
            // With single compartment models, go and get the compartment name
            // with multiple compartment models, random selection
            int comp_index;
            if (options_->getNCompartments() == 1) {
                comp_index = 0;
            } else {
                comp_index = selectRandomCompartmentIndex();
            }
            boundary_species_.ids.push_back(id.str());
            boundary_species_.values.push_back(val);
            boundary_species_.compartment_index.push_back(comp_index);
            id.str(std::string());
        }
    }

    RateLaw RandomNetworkGenerator::getRandomRateLaw() const {
        // select a rate law at random.
        std::vector<RateLaw> keys;
        for (auto &it : options_->getRateLaws()) {
            keys.push_back(it.second);
        }

        if (options_->getRateLaws().empty()) {
            INVALID_ARGUMENT_ERROR("The RateLaw field of RandomNetworkGeneratorOptions is "
                                   "empty. Please give some rate laws to continue");
        }
        int random_rate_law_index = nc::random::randInt<int>(0, (int) options_->getRateLaws().size());
        return keys[random_rate_law_index];
    }

    std::string RandomNetworkGenerator::generateUniqueParameterID(int number, const std::string &base_name, std::vector<std::string> &exclusion_list) const {
        std::ostringstream proposal;
        proposal << base_name << number;
        if (std::find(exclusion_list.begin(), exclusion_list.end(), proposal.str()) != exclusion_list.end()) {
            // id already used
            number += 1;
            proposal.str("");// clear the proposal
            return generateUniqueParameterID(number, base_name, exclusion_list);
        } else {
            return proposal.str();
        }
    }

    void RandomNetworkGenerator::assembleModel() {
        // first create compartments
        for (int i = 0; i < compartments_.ids.size(); i++) {
            rr_->addCompartment(
                    compartments_.ids[i],
                    compartments_.values[i],
                    false);
        }

        // create boundary species
        for (int i = 0; i < boundary_species_.ids.size(); i++){
//            LOG("adding boundary species "<<boundary_species_.ids[i]);
            rr_->addSpecies(
                    boundary_species_.ids[i],
                    compartments_.ids[boundary_species_.compartment_index[i]],
                    boundary_species_.values[i],
                    false,
                    true,
                    "",
                    false
                    );
        }
        // create floating species
        for (int i = 0; i < floating_species_.ids.size(); i++){
//            LOG("adding floating species "<<floating_species_.ids[i]);
            rr_->addSpecies(
                    floating_species_.ids[i],
                    compartments_.ids[floating_species_.compartment_index[i]],
                    floating_species_.values[i],
                    false,
                    false,
                    "",
                    false
                    );
        }

        // now procede with creating reactions.
        // since this is the final step - after which we will regenerate the model
        // it is simpler not to create the intermediatary storage like we have done for
        // other network components

        std::ostringstream reaction_name;
        std::vector<std::string> current_model_parameters = rr_->getGlobalParameterIds();
        for (int reaction_number = 0; reaction_number < options_->getNReactions(); reaction_number++) {
            // select a random rate law
            RateLaw rateLaw = getRandomRateLaw();
//            LOG("creating reaction "<< reaction_number << " with rate law " << rateLaw.getName());

            const RoleMap &roles = rateLaw.getRoles();// from user input
            // count number of parameters
            int parameter_count = 0;
            for (auto &it : roles) {
                if (it.second == EVO_PARAMETER)
                    parameter_count += 1;
            }
            if (parameter_count > roles.size()) {
                LOGIC_ERROR("Number of parameters counted is larger than the number of roles "
                            "in your rate law, this is weird.");
            }
            if (parameter_count == 0) {
                LOGIC_ERROR("Counted 0 kinetic parameters in your rate law. This"
                            "is highly unusual and probably wrong.");
            }

            // work out how many randomly selected species we need
            int num_random_species = (int) roles.size() - parameter_count;
            int num_species = options_->getNBoundarySpecies() + options_->getNFloatingSpecies();
            if (num_random_species > num_species) {
                std::ostringstream err;
                err << "Rate law \"" << rateLaw.getName() << "\" requires " << num_random_species << " species ";
                err << "but your configurations only allow for " << num_species << ". Please change your configuration options.";
                LOGIC_ERROR(err.str());
            }

            // randomly sample without replacement
            std::vector<int> species = selectRandomSpeciesIndex(num_random_species);

            // untangle boundary and non boundary and collect the species ids
            std::vector<std::string> species_ids;
            for (int i=0; i<species.size(); i++){
                int species_idx = species[i];
                if (species_idx < options_->getNBoundarySpecies())
                    species_ids.push_back(boundary_species_.ids[species_idx]);
                else {
                    species_idx = species_idx - options_->getNBoundarySpecies();
                    species_ids.push_back(floating_species_.ids[species_idx]);
                }
            }

            assert(species_ids.size() == num_random_species);
            // some vectors to store Species by role
            std::vector<std::string> substrates;
            std::vector<std::string> products;
            std::vector<std::string> modifiers;

            // make a copy of the rate law string. We will modify this for use in addReaction
            // as the rate law contains only place holders.
            std::string rate_law_string = rateLaw.getRateLawString();
            for (auto &it : roles) {
                const std::string& rate_law_component = it.first;
                const RoleType& role = it.second;
                // Regex defined here as its the same expression for all cases.
                // \b matches a word boundary (\\b escapes the first \)
                std::regex reg(it.first + "\\b");//
                switch (role) {
                    case (EVO_PARAMETER): {
                        // sample between specified boundaries and add to the model
                        auto val = nc::random::uniform<double>(options_->getParameterLowerBound(), options_->getParameterUpperBound());
                        // ensure unique parameter name. We pass in reference to used parameter names
                        // so we do not have to reload the model each time we add a parameter (performance reasons).
                        std::string parameter_name = generateUniqueParameterID(0, rate_law_component, current_model_parameters);
                        rr_->addParameter(parameter_name, val, false);
                        current_model_parameters.push_back(parameter_name);// add to list of parameter names
                        // now ensure the placeholder (it.first) contains the newly generated parameter name
                        rate_law_string = regex_replace(rate_law_string, reg, parameter_name);
                        break;
                    }
                    case (EVO_SUBSTRATE): {
                        std::string substrate = species_ids[species_ids.size() - 1];
                        substrates.push_back(substrate);
                        species_ids.resize(species_ids.size() - 1);
                        // now ensure the placeholder (it.first) contains the species
                        rate_law_string = regex_replace(rate_law_string, reg, substrate);
                        break;
                    }
                    case (EVO_PRODUCT): {
                        std::string product = species_ids[species_ids.size() - 1];
                        products.push_back(product);
                        species_ids.resize(species_ids.size() - 1);
                        // now ensure the placeholder (it.first) contains the species
                        rate_law_string = regex_replace(rate_law_string, reg, product);
                        break;
                    }
                    case (EVO_MODIFIER): {
                        std::string modifier = species_ids[species_ids.size() - 1];
                        modifiers.push_back(modifier);
                        species_ids.resize(species_ids.size() - 1);
                        // now ensure the placeholder (it.first) contains the species
                        rate_law_string = regex_replace(rate_law_string, reg, modifier);
                        break;
                    }
                    default:
                        LOGIC_ERROR("Unknown it specified");
                }
            }
            reaction_name << "R" << reaction_number;
            getRR()->addReaction(reaction_name.str(), substrates, products, rate_law_string, false);
            reaction_name.str("");// clear the stream
        }

    }
    RandomNetworkGenerator::~RandomNetworkGenerator() = default;
    //    std::unique_ptr<RoadRunner> RandomNetworkGenerator::generate() {
//        createRRModel();
//        createCompartments();
//        createBoundarySpecies();
//        createFloatingSpecies();
//        assembleModel();
//        // regenerate the finished model.
//        getRR()->regenerate(true, false);
//        return std::move(rr_);
//    }


}// namespace evo