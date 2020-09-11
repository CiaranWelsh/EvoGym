//
// Created by Ciaran on 09/09/2020.
//

#include "evo/RandomNetworkGenerator.h"
#include "NumCpp.hpp"
#include <chrono>
#include <regex>


/*
 * Idea for end to end testing
 * Pick a small network configuration and map out the complete set of
 * possible networks. You'll have to fix parameter values.
 * Then generate many random networks and count frequency. You
 * should get a normal uniform distribution
 */

namespace evo {

    RandomNetworkGenerator::RandomNetworkGenerator(const NetworkGenerationOptions &options)
        : options_(options) {
        createRRModel();
        createCompartments();
        createBoundarySpecies();
        createFloatingSpecies();
        createReactions();
        rr_->regenerate(true, false);
    }

    void RandomNetworkGenerator::createRRModel() {
        if (options_.getCoreSBML().empty()) {
            rr_ = std::make_unique<RoadRunner>(RoadRunner());
        } else {
            rr_ = std::make_unique<RoadRunner>(options_.getCoreSBML());
        }
    }

    const std::unique_ptr<RoadRunner> &RandomNetworkGenerator::getRR() const {
        return rr_;
    }


    const NetworkGenerationOptions &RandomNetworkGenerator::getOptions() const {
        return options_;
    }

    std::string RandomNetworkGenerator::selectRandomCompartment() {
        int random_index = nc::random::randInt<int>(0, options_.getNCompartments());
        return getRR()->getCompartmentIds()[random_index];
    }

    std::vector<int> RandomNetworkGenerator::sample_with_replacement(int nsamples, int npop) {
        if (nsamples > npop) {
            LOGIC_ERROR("The number of samples cannot be more than the size of the population when sampling"
                        "with replacement");
        }

        std::vector<int> out;
        for (int j = npop - nsamples + 1; j < npop + 1; j++) {
            auto random_number = nc::random::uniform<double>(0.0, 1.0);
            unsigned int t = 1 + j * (int) random_number;
            if (std::find(out.begin(), out.end(), t) != out.end()) {
                out.push_back(j);
            } else {
                out.push_back(t);
            }
        }// if(replace)

        // we subtract 1 from the output so that we have index friendly numbers
        // i.e. algorithm is 1 indexed and C++ is 0 indexed.
        for (int &i : out) {
            i -= 1;
        }
        return out;
    }

    std::vector<std::string> RandomNetworkGenerator::selectRandomSpecies(int n) {
        std::vector<std::string> species = getRR()->getBoundarySpeciesIds();
        std::vector<std::string> floating = getRR()->getFloatingSpeciesIds();

        // all species
        species.insert(species.end(), floating.begin(), floating.end());

        // check for the impossible
        if (n > species.size()) {
            std::ostringstream err;
            err << "Requested selecting "
                << n
                << " random species without replacement but only "
                << species.size() << " species exist.";
            LOGIC_ERROR(err.str());
        }
        // do the sampling
        std::vector<int> species_indices = sample_with_replacement(n, species.size());

        for (auto i : species_indices) {
            std::cout << "i: " << i << std::endl;
        }

        // convert indices into the strings we need.
        std::vector<std::string> out;
        for (auto &i : species_indices) {
            std::cout << "I1: " << i << std::endl;
            if (i < options_.getNBoundarySpecies()) {
                out.push_back(getRR()->getBoundarySpeciesIds()[i]);
            } else {
                int idx = i - options_.getNBoundarySpecies();
                out.push_back(getRR()->getFloatingSpeciesIds()[idx]);
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
            getRR()->addCompartment(id.str(), val, forceRegenerate);// regenerate model on last iter
            id.str(std::string());                                  // clear the stream
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
            getRR()->addSpecies(id.str(), comp, val, false, false, "", forceRegenerate);
            id.str(std::string());
        }
    }

    void RandomNetworkGenerator::createBoundarySpecies() {
        std::ostringstream id;
        for (int i = 0; i < options_.getNBoundarySpecies(); i++) {
            id << "I" << i;
            int val = options_.getBoundarySpeciesUpperBound();
            if (options_.getBoundarySpeciesLowerBound() != options_.getBoundarySpeciesUpperBound()) {
                val = nc::random::randInt(options_.getBoundarySpeciesLowerBound(),
                                          options_.getBoundarySpeciesUpperBound());
            }
            bool forceRegenerate = false;
            if (i == options_.getNBoundarySpecies() - 1)
                forceRegenerate = true;
            std::string comp = selectRandomCompartment();
            getRR()->addSpecies(id.str(), comp, val, false, true, "", forceRegenerate);
            id.str(std::string());
        }
    }

    RateLaw RandomNetworkGenerator::getRandomRateLaw() const {
        // select a rate law at random.
        std::vector<RateLaw> keys;
        for (auto &it : options_.getRateLaws()) {
            keys.push_back(it.second);
        }
        if (options_.getRateLaws().empty()) {
            INVALID_ARGUMENT_ERROR("The RateLaw field of RandomNetworkGeneratorOptions is "
                                   "empty. Please give some rate laws to continue");
        }
        int random_rate_law_index = nc::random::randInt<int>(0, options_.getRateLaws().size());
        return keys[random_rate_law_index];
    }

    //    std::string RandomNetworkGenerator::generateUniqueParameterID(const std::string& base_name, std::vector<std::string>& exclusion_list) const{
    //        std::vector<std::string> existing_parameter_names = rr_->getGlobalParameterIds();
    //
    //        //concat the exclusion list.
    //        existing_parameter_names.insert(existing_parameter_names.end(), exclusion_list.begin(), exclusion_list.end());
    //        int number = 0;
    //        std::ostringstream proposal;
    //        proposal << base_name << number;
    //        while(std::find(existing_parameter_names.begin(), existing_parameter_names.end(), proposal.str()) != existing_parameter_names.end()){
    //            number +=1;
    //            proposal.str("");
    //            proposal << base_name << number;
    //        }
    //        return proposal.str();
    //    }
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

    /**
     * This strategy could be dangerous in that if there is no match at all we'll
     * get stuck in an infinite loop.
     *
     * Therefore it is essential that the calling function first checks that the match_string is
     * actually present in the rate law string. If not, no enter this function. If so, we use this
     * strategy to locate the parameter in question.
     *
     * Note that this beats the regex strategy which will get complicated as soon as were in double
     * triple digits.
     */
    std::string RandomNetworkGenerator::substituteRateLawComponent(libsbml::ASTNode *rate_law_term, const std::string& match_string, const std::string& substitute) {
        if (rate_law_term->getNumChildren() == 0) {
            std::string term_string = libsbml::SBML_formulaToString(rate_law_term);
            if (term_string == match_string) {
                return term_string;
            } else {
                return std::string();
            }
        } else {
            for (int i = 0; i < rate_law_term->getNumChildren(); i++) {
                return substituteRateLawComponent(rate_law_term->getChild(i), match_string, substitute);
            }
        }
    }

    void RandomNetworkGenerator::createReactions() {
        // this will be empty if no core sbml has been used.
        std::ostringstream reaction_name;
        std::vector<std::string> current_model_parameters = rr_->getGlobalParameterIds();
        for (int reaction_number = 0; reaction_number < options_.getNReactions(); reaction_number++) {
            // select a random rate law
            RateLaw rateLaw = getRandomRateLaw();

            //            rr_->addRateRule(rateLaw.getName(), rateLaw.getRateLawString(), false);
            std::cout << rateLaw.getName() << std::endl;
            const RoleMap &roles = rateLaw.getRoles();

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
            int num_species = rr_->getNumberOfIndependentSpecies() + rr_->getNumberOfDependentSpecies();
            if (num_random_species < num_species) {
                std::ostringstream err;
                err << "Rate law \"" << rateLaw.getName() << "\" requires " << num_random_species << " species ";
                err << "but your configurations only allow for " << num_species << ". Please change your configuration options.";
                LOGIC_ERROR(err.str());
            }

            // randomly sample without replacement
            std::vector<std::string> species = selectRandomSpecies(num_random_species);

            assert(species.size() == num_random_species);

            // some vectors to store Species, sorted by role
            std::vector<std::string> substrates;
            std::vector<std::string> products;
            std::vector<std::string> modifiers;

            // make a copy of the rate law string. In order to create a reaction
            // we will need to generate a new parameter id and use regular expression
            // to replace the placeholder with the new string
            std::string rate_law_string = rateLaw.getRateLawString();
            for (auto &it : roles) {
                std::regex reg(it.first);// non-greedy match
                std::cout << "first: " << it.first << ", second: " << it.second << std::endl;
                switch (it.second) {
                    case (EVO_PARAMETER): {
                        // sample between specified boundaries and add to the model
                        double val = nc::random::uniform(options_.getParameterLowerBound(), options_.getParameterUpperBound());
                        // ensure unique parameter name. We pass in reference to used parameter names
                        // so we do not have to reload the model each time we add a parameter (performance reasons).
                        std::string parameter_name = generateUniqueParameterID(0, it.first, current_model_parameters);
                        std::cout << "parameter_name: " << parameter_name << std::endl;
                        rr_->addParameter(parameter_name, val, false);
                        current_model_parameters.push_back(parameter_name);// add to list of parameter names

                        // now ensure the placeholder (it.first) contains the newly generated parameter name
                        rate_law_string = regex_replace(rate_law_string, reg, parameter_name);

                        break;
                    }
                    case (EVO_SUBSTRATE): {
                        std::string substrate = species[species.size() - 1];
                        substrates.push_back(substrate);
                        species.resize(species.size() - 1);

                        // now ensure the placeholder (it.first) contains the species
                        rate_law_string = regex_replace(rate_law_string, reg, substrate);
                        break;
                    }
                    case (EVO_PRODUCT): {
                        std::string product = species[species.size() - 1];
                        products.push_back(product);
                        species.resize(species.size() - 1);

                        // now ensure the placeholder (it.first) contains the species
                        rate_law_string = regex_replace(rate_law_string, reg, product);
                        break;
                    }
                    case (EVO_MODIFIER): {
                        std::string modifier = species[species.size() - 1];
                        modifiers.push_back(modifier);
                        species.resize(species.size() - 1);
                        // now ensure the placeholder (it.first) contains the species
                        rate_law_string = regex_replace(rate_law_string, reg, modifier);
                        break;
                    }
                    default:
                        LOGIC_ERROR("Unknown role specified");
                }
            }
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            reaction_name << "R" << reaction_number;
            getRR()->addReaction(reaction_name.str(), substrates, products, rate_law_string, false);
            reaction_name.str("");// clear the stream
        }
    }

    RoadRunner *RandomNetworkGenerator::generate() {
        return nullptr;
    }
}// namespace evo