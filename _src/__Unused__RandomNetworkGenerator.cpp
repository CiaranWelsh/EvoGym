//
// Created by Ciaran on 09/09/2020.
//

#include "evo/RandomNetworkGenerator.h"
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

/*******************************************************************************************
 * RandomNetworkGenerator Base class
 *
 * Constructors
 *
 */
    __Unused__RandomNetworkGenerator::__Unused__RandomNetworkGenerator(const RandomNetworkGeneratorOptions &options)
            : options_(options) {
        setRandomSeed();
    }

/*******************************************************************************************
* RandomNetworkGenerator Protected methods
*/

    void __Unused__RandomNetworkGenerator::setSeed(const long long &to) {
        LOG("settting seed to :" << to);
        nc::random::seed(to);
    }

    int __Unused__RandomNetworkGenerator::selectRandomCompartmentIndex() {
        return nc::random::randInt<int>(0, options_.getNCompartments());
    }

    EvoRateLaw __Unused__RandomNetworkGenerator::getRandomRateLaw() const {
        // select a rate law at random.
        std::vector<EvoRateLaw> keys;
        for (auto &it : options_.getRateLaws()) {
            keys.push_back(it.second);
        }

        if (options_.getRateLaws().empty()) {
            INVALID_ARGUMENT_ERROR << "The RateLaw field of RandomNetworkGeneratorOptions is "
                                      "empty. Please give some rate laws to continue";
        }
        int random_rate_law_index = nc::random::randInt<int>(0, (int) options_.getRateLaws().size());
        return keys[random_rate_law_index];
    }

    std::unordered_map<std::string, double> __Unused__RandomNetworkGenerator::getExistingModelParameters(RoadRunner &rr) {
        std::unordered_map<std::string, double> map;
        const int &N = rr.getModel()->getNumGlobalParameters();
        const std::vector<std::string> ids = rr.getGlobalParameterIds();
        for (int i = 0; i < rr.getGlobalParameterIds().size(); i++) {
            const std::string &name = ids[i];
            map[name] = rr.getGlobalParameterByName(name);
        }
        return map;
    }


    std::unique_ptr<RoadRunner> __Unused__RandomNetworkGenerator::createRRModel() {
        auto *rr = new RoadRunner();
        return std::move(std::unique_ptr<RoadRunner>(rr));
//        if (options_.getCoreSBML().empty()) {
//        } else {
//            auto *rr = new RoadRunner(options_.getCoreSBML());
//            existing_model_parameters_ = getExistingModelParameters(rr);
//            return std::move(std::unique_ptr<RoadRunner>(rr));
//        }
    }

    std::vector<int> __Unused__RandomNetworkGenerator::sample_with_replacement(int nsamples, int npop) {
        if (nsamples > npop) {
            LOGIC_ERROR << "The number of samples cannot be more than the size of the population when sampling"
                           "with replacement";
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

    std::string __Unused__RandomNetworkGenerator::generateUniqueParameterID(int number, const std::string &base_name) const {
        StringVector existing_parameter_ids;
        for (auto &i: existing_model_parameters_)
            existing_parameter_ids.push_back(i.first);

        std::ostringstream proposal;
        proposal << base_name << number;
        if (std::find(existing_parameter_ids.begin(), existing_parameter_ids.end(), proposal.str()) !=
            existing_parameter_ids.end()) {
            // id already used
            number += 1;
            proposal.str("");// clear the proposal
            return generateUniqueParameterID(number, base_name);
        } else {
            return proposal.str();
        }
    }


    std::vector<int> __Unused__RandomNetworkGenerator::selectRandomSpeciesIndex(int n) {
        int nspecies = options_.getNBoundarySpecies() + options_.getNFloatingSpecies();

        // check for the impossible
        if (n > nspecies) {
            std::ostringstream err;
            err << "Requested selecting "
                << n
                << " random boundary species without replacement but only "
                << nspecies << " species exist.";
            LOGIC_ERROR << err.str();
        }
        // do the sampling
        std::vector<int> species_indices = sample_with_replacement(n, nspecies);
        return species_indices;
    }


    const RandomNetworkGeneratorOptions &__Unused__RandomNetworkGenerator::getOptions() const {
        return options_;
    }

    std::unique_ptr<RoadRunner> __Unused__RandomNetworkGenerator::generate() {
        std::unique_ptr<RoadRunner> rr_ptr = createRRModel();
        Compartments compartments = createCompartments();

        for (int i = 0; i < compartments.ids.size(); i++) {
            rr_ptr->addCompartment(
                    compartments.ids[i],
                    compartments.values[i],
                    false);
        }

        BoundarySpecies boundarySpecies = createBoundarySpecies();

        // create boundary species
        for (int i = 0; i < boundarySpecies.ids.size(); i++) {
            rr_ptr->addSpecies(
                    boundarySpecies.ids[i],
                    compartments.ids[boundarySpecies.compartment_index[i]],
                    boundarySpecies.values[i],
                    false,
                    true,
                    "",
                    false
            );
        }
        // create floating species
        FloatingSpecies floatingSpecies = createFloatingSpecies();
        for (int i = 0; i < floatingSpecies.ids.size(); i++) {
            rr_ptr->addSpecies(
                    floatingSpecies.ids[i],
                    compartments.ids[floatingSpecies.compartment_index[i]],
                    floatingSpecies.values[i],
                    false,
                    false,
                    "",
                    false
            );
        }
        LOG("HERE");

        Reactions reactions = createReactions();
        LOG("HERE");
        for (int reaction_number = 0; reaction_number < options_.getNReactions(); reaction_number++) {

            LOG("HERE");

            StringVector substrates;
            LOG("HERE");
            for (auto &substrate_id: reactions.substrates[reaction_number])
                substrates.push_back(convertSpeciesIndexToString(boundarySpecies, floatingSpecies, substrate_id));
            LOG("HERE");

            StringVector products;
            for (auto &products_id: reactions.products[reaction_number])
                products.push_back(convertSpeciesIndexToString(boundarySpecies, floatingSpecies, products_id));
            LOG("HERE");

            StringVector modifiers;
            for (auto &mod_id: reactions.substrates[reaction_number])
                modifiers.push_back(convertSpeciesIndexToString(boundarySpecies, floatingSpecies, mod_id));
            LOG("HERE");

            // unpack ingredients for this reaction
            const EvoRateLaw &rate_law = reactions.rate_laws[reaction_number];
            const RoleMap &roles = rate_law.getRoles();
            std::string rate_law_string = rate_law.getRateLawString(); // need a copy
            LOG("HERE");
            for (auto &it : roles) {
                const std::string &rate_law_component = it.first;
                const RoleType &role = it.second;
                // Regex defined here as its the same expression for all cases.
                // \b matches a word boundary (\\b escapes the first \)
                std::regex reg(it.first + "\\b");//
                LOG("role is:" << role);
                switch (role) {
                    LOG("HERE");
                    case (EVO_PARAMETER): {
                        LOG("HERE");
                        // sample between specified boundaries and add to the model
                        LOG("HERE");
                        auto val = nc::random::uniform<double>(options_.getParameterLowerBound(),
                                                               options_.getParameterUpperBound());
                        LOG("HERE");
                        // ensure unique parameter name. We pass in reference to used parameter names
                        // so we do not have to reload the model each time we add a parameter (performance reasons).
                        std::string parameter_name = generateUniqueParameterID(0, rate_law_component);
                        LOG("HERE");
                        existing_model_parameters_[parameter_name] = val;
                        LOG("HERE");
                        // now ensure the placeholder (it.first) contains the newly generated parameter name
                        rate_law_string = regex_replace(rate_law_string, reg, parameter_name);
                        LOG("HERE");
                        break;
                    }
                    case (EVO_SUBSTRATE): {
                        // we pink a substrate off the end of the list of substrates
                        LOG("HERE");
                        const std::string &substrate = substrates[substrates.size() - 1];
                        // then resize the substrates vector to remove the end
                        substrates.resize(substrates.size() - 2);
                        LOG("HERE");
                        // now ensure the placeholder (it.first) contains the species
                        rate_law_string = regex_replace(rate_law_string, reg, substrate);
                        LOG("HERE");
                        break;
                    }
                    case (EVO_PRODUCT): {
                        // we pink a substrate off the end of the list of substrates
                        LOG("HERE");
                        const std::string &product = products[products.size() - 1];
                        LOG("HERE");
                        // then resize the substrates vector to remove the end
                        products.resize(products.size() - 2);
                        LOG("HERE");
                        // now ensure the placeholder (it.first) contains the species
                        LOG("HERE");
                        rate_law_string = regex_replace(rate_law_string, reg, product);
                        LOG("HERE");
                        break;
                    }
                    case (EVO_MODIFIER): {
                        // we pink a substrate off the end of the list of substrates
                        const std::string &modifier = modifiers[modifiers.size() - 1];
                        LOG("HERE");
                        LOG("HERE");
                        // then resize the substrates vector to remove the end
                        LOG("HERE");
                        modifiers.resize(modifiers.size() - 2);
                        LOG("HERE");
                        // now ensure the placeholder (it.first) contains the species
                        LOG("HERE");
                        rate_law_string = regex_replace(rate_law_string, reg, modifier);
                        LOG("HERE");
                        break;
                    }
                    default:
                        LOGIC_ERROR << "Unknown role specified. ";
                }
            }
        }

        return std::move(rr_ptr);
    }

    std::string __Unused__RandomNetworkGenerator::convertSpeciesIndexToString(const BoundarySpecies &boundarySpecies,
                                                                              const FloatingSpecies &floatingSpecies,
                                                                              int idx) {
        StringVector species_ids = boundarySpecies.ids;
        species_ids.insert(species_ids.begin(), floatingSpecies.ids.begin(), floatingSpecies.ids.end());
        if (idx < boundarySpecies.ids.size())
            return boundarySpecies.ids[idx];
        else
            return floatingSpecies.ids[boundarySpecies.ids.size() + idx]; // offset by num boundary species
    }


/********************************************************************************************
 *  NaiveRandomNetworkGenerator
 */

    Compartments NaiveRandomNetworkGenerator::createCompartments() {
        Compartments compartments;
        std::ostringstream id;
        for (int i = 0; i < options_.getNCompartments(); i++) {
            double val = options_.getCompartmentUpperBound();
            if (options_.getCompartmentLowerBound() != options_.getCompartmentUpperBound()) {
                val = nc::random::uniform<double>(options_.getCompartmentLowerBound(),
                                                  options_.getCompartmentUpperBound());
            }
            id << "C" << i;
            compartments.ids.push_back(id.str());
            compartments.values.push_back(val);
            id.str(std::string());// clear the stream
        }
        return compartments;
    }

    FloatingSpecies NaiveRandomNetworkGenerator::createFloatingSpecies() {
        FloatingSpecies floatingSpecies;
        std::ostringstream id;
        for (int i = 0; i < options_.getNFloatingSpecies(); i++) {
            id << "S" << i;
            double val = options_.getSpeciesUpperBound();
            if (options_.getSpeciesLowerBound() != options_.getSpeciesUpperBound()) {
                val = nc::random::uniform<double>(options_.getSpeciesLowerBound(),
                                                  options_.getSpeciesUpperBound());
            }
            // With single compartment models, go and get the compartment name
            // with multiple compartment models, random selection
            int comp_index;
            if (options_.getNCompartments() == 1) {
                comp_index = 0;
            } else {
                comp_index = selectRandomCompartmentIndex();
            }
            floatingSpecies.ids.push_back(id.str());
            floatingSpecies.values.push_back(val);
            floatingSpecies.compartment_index.push_back(comp_index);
            id.str(std::string());
        }
        return floatingSpecies;
    }

    BoundarySpecies NaiveRandomNetworkGenerator::createBoundarySpecies() {
        BoundarySpecies boundarySpecies;
        std::ostringstream id;
        for (int i = 0; i < options_.getNBoundarySpecies(); i++) {
            id << "I" << i;
            double val = options_.getBoundarySpeciesUpperBound();
            if (options_.getBoundarySpeciesLowerBound() != options_.getBoundarySpeciesUpperBound()) {
                val = nc::random::uniform<double>(options_.getBoundarySpeciesLowerBound(),
                                                  options_.getBoundarySpeciesUpperBound());
            }
            // With single compartment models, go and get the compartment name
            // with multiple compartment models, random selection
            int comp_index;
            if (options_.getNCompartments() == 1) {
                comp_index = 0;
            } else {
                comp_index = selectRandomCompartmentIndex();
            }
            boundarySpecies.ids.push_back(id.str());
            boundarySpecies.values.push_back(val);
            boundarySpecies.compartment_index.push_back(comp_index);
            id.str(std::string());
        }
        return boundarySpecies;
    }

    Reactions NaiveRandomNetworkGenerator::createReactions() {
        Reactions reactions(options_.getNReactions());

        std::ostringstream reaction_name;
        for (int reaction_number = 0; reaction_number < options_.getNReactions(); reaction_number++) {
            // generate reaction name;
            reaction_name << "R" << reaction_number;
            reactions.ids[reaction_number] = reaction_name.str();
            reaction_name.str("");// clear the stream

            // select a random rate law
            EvoRateLaw rateLaw = getRandomRateLaw();
            reactions.rate_laws[reaction_number] = rateLaw;


            const RoleMap &roles = rateLaw.getRoles();// from user input

            // work out how many randomly selected species we need
            int num_random_species =
                    rateLaw.numSubstrates() + rateLaw.numProducts() + rateLaw.numModifiers();
            int total_num_species_possible = options_.getNBoundarySpecies() + options_.getNFloatingSpecies();

            // check that it makes sense to randomly generate num_random_species species
            if (num_random_species > total_num_species_possible) {
                LOGIC_ERROR << "Rate law \"" << rateLaw.getName() << "\" requires " << num_random_species
                            << " species "
                            << "but your configurations only allow for " << total_num_species_possible
                            << ". Please change your configuration options either by allowing more Floating or Boundary species or "
                               "using different rate laws.";
            }

            // randomly sample without replacement
            std::vector<int> species_indices = selectRandomSpeciesIndex(num_random_species);
            assert(species_indices.size() == num_random_species); // this will always be true

            // dish out the species indices to reaction substrates, products or modifiers.
            for (int s = 0; s < rateLaw.numSubstrates(); s++) {
                const int &species_idx = species_indices[species_indices.size() - 1];
                reactions.substrates[reaction_number].push_back(species_idx);
                species_indices.resize(species_indices.size() - 1);
            }
            for (int s = 0; s < rateLaw.numProducts(); s++) {
                const int &species_idx = species_indices[species_indices.size() - 1];
                reactions.products[reaction_number].push_back(species_idx);
                species_indices.resize(species_indices.size() - 1);
            }
            for (int s = 0; s < rateLaw.numModifiers(); s++) {
                const int &species_idx = species_indices[species_indices.size() - 1];
                reactions.modifiers[reaction_number].push_back(species_idx);
                species_indices.resize(species_indices.size() - 1);
            }
            assert(species_indices.empty());
        }
        return reactions;
    }




//            std::string rate_law_string = rateLaw.getRateLawString();
//            for (auto &it : roles) {
//                const std::string &rate_law_component = it.first;
//                const RoleType &role = it.second;
//                // Regex defined here as its the same expression for all cases.
//                // \b matches a word boundary (\\b escapes the first \)
//                std::regex reg(it.first + "\\b");//
//                switch (role) {
//                    case (EVO_PARAMETER): {
//                        // sample between specified boundaries and add to the model
//                        auto val = nc::random::uniform<double>(options_.getParameterLowerBound(),
//                                                               options_.getParameterUpperBound());
//                        // ensure unique parameter name. We pass in reference to used parameter names
//                        // so we do not have to reload the model each time we add a parameter (performance reasons).
//                        std::string parameter_name = generateUniqueParameterID(0, rate_law_component);
//                        existing_model_parameters_[parameter_name] = val;
//                        // now ensure the placeholder (it.first) contains the newly generated parameter name
//                        rate_law_string = regex_replace(rate_law_string, reg, parameter_name);
//                        break;
//                    }
//                    case (EVO_SUBSTRATE): {
////                        std::string substrate = species_ids[species_ids.size() - 1];
//                        substrates.push_back(substrate);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, substrate);
//                        break;
//                    }
//                    case (EVO_PRODUCT): {
//                        std::string product = species_ids[species_ids.size() - 1];
//                        products.push_back(product);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, product);
//                        break;
//                    }
//                    case (EVO_MODIFIER): {
//                        std::string modifier = species_ids[species_ids.size() - 1];
//                        modifiers.push_back(modifier);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, modifier);
//                        break;
//                    }
//                    default:
//                        LOGIC_ERROR << "Unknown it specified";
//                }
//            }

//        }















//            // untangle boundary and non boundary and collect the species ids
//            std::vector<std::string> species_ids;
//            for (int i = 0; i < species.size(); i++) {
//                int species_idx = species[i];
//                if (species_idx < options_.getNBoundarySpecies())
//                    species_ids.push_back(boundary_species_.ids[species_idx]);
//                else {
//                    species_idx = species_idx - options_.getNBoundarySpecies();
//                    species_ids.push_back(floating_species_.ids[species_idx]);
//                }
//            }
//
//            assert(species_ids.size() == num_random_species);
//            // some vectors to store Species by role
//            std::vector<std::string> substrates;
//            std::vector<std::string> products;
//            std::vector<std::string> modifiers;
//
//            // make a copy of the rate law string. We will modify this for use in addReaction
//            // as the rate law contains only place holders.
//            std::string rate_law_string = rateLaw.getRateLawString();
//            for (auto &it : roles) {
//                const std::string &rate_law_component = it.first;
//                const RoleType &role = it.second;
//                // Regex defined here as its the same expression for all cases.
//                // \b matches a word boundary (\\b escapes the first \)
//                std::regex reg(it.first + "\\b");//
//                switch (role) {
//                    case (EVO_PARAMETER): {
//                        // sample between specified boundaries and add to the model
//                        auto val = nc::random::uniform<double>(options_.getParameterLowerBound(),
//                                                               options_.getParameterUpperBound());
//                        // ensure unique parameter name. We pass in reference to used parameter names
//                        // so we do not have to reload the model each time we add a parameter (performance reasons).
//                        std::string parameter_name = generateUniqueParameterID(0, rate_law_component);
////                        rr_->addParameter(parameter_name, val, false);
//                        existing_model_parameters_.push_back(parameter_name);// add to list of parameter names
//                        // now ensure the placeholder (it.first) contains the newly generated parameter name
//                        rate_law_string = regex_replace(rate_law_string, reg, parameter_name);
//                        break;
//                    }
//                    case (EVO_SUBSTRATE): {
////                        std::string substrate = species_ids[species_ids.size() - 1];
//                        substrates.push_back(substrate);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, substrate);
//                        break;
//                    }
//                    case (EVO_PRODUCT): {
//                        std::string product = species_ids[species_ids.size() - 1];
//                        products.push_back(product);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, product);
//                        break;
//                    }
//                    case (EVO_MODIFIER): {
//                        std::string modifier = species_ids[species_ids.size() - 1];
//                        modifiers.push_back(modifier);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, modifier);
//                        break;
//                    }
//                    default:
//                        LOGIC_ERROR << "Unknown it specified";
//                }
//            }
//
//            getRR()->addReaction(reaction_name.str(), substrates, products, rate_law_string, false);
//        }
//

//    }
//

//
//        // now procede with creating reactions.
//        // since this is the final step - after which we will regenerate the model
//        // it is simpler not to create the intermediatary storage like we have done for
//        // other network components
//
//        std::ostringstream reaction_name;
//        std::vector<std::string> current_model_parameters = rr_->getGlobalParameterIds();
//        for (int reaction_number = 0; reaction_number < options_.getNReactions(); reaction_number++) {
//            // select a random rate law
//            EvoRateLaw rateLaw = getRandomRateLaw();
////            LOG("creating reaction "<< reaction_number << " with rate law " << rateLaw.getName());
//
//            const RoleMap &roles = rateLaw.getRoles();// from user input
//            // count number of parameters
//            int parameter_count = 0;
//            for (auto &it : roles) {
//                if (it.second == EVO_PARAMETER)
//                    parameter_count += 1;
//            }
//            if (parameter_count > roles.size()) {
//                LOGIC_ERROR << "Number of parameters counted is larger than the number of roles "
//                               "in your rate law, this is weird.";
//            }
//            if (parameter_count == 0) {
//                LOGIC_ERROR << "Counted 0 kinetic parameters in your rate law. This"
//                               "is highly unusual and probably wrong.";
//            }
//
//            // work out how many randomly selected species we need
//            int num_random_species = (int) roles.size() - parameter_count;
//            int num_species = options_.getNBoundarySpecies() + options_.getNFloatingSpecies();
//            if (num_random_species > num_species) {
//                std::ostringstream err;
//                err << "Rate law \"" << rateLaw.getName() << "\" requires " << num_random_species << " species ";
//                err << "but your configurations only allow for " << num_species
//                    << ". Please change your configuration options.";
//                LOGIC_ERROR << err.str();
//            }
//
//            // randomly sample without replacement
//            std::vector<int> species = selectRandomSpeciesIndex(num_random_species);
//
//            // untangle boundary and non boundary and collect the species ids
//            std::vector<std::string> species_ids;
//            for (int i = 0; i < species.size(); i++) {
//                int species_idx = species[i];
//                if (species_idx < options_.getNBoundarySpecies())
//                    species_ids.push_back(boundary_species_.ids[species_idx]);
//                else {
//                    species_idx = species_idx - options_.getNBoundarySpecies();
//                    species_ids.push_back(floating_species_.ids[species_idx]);
//                }
//            }
//
//            assert(species_ids.size() == num_random_species);
//            // some vectors to store Species by role
//            std::vector<std::string> substrates;
//            std::vector<std::string> products;
//            std::vector<std::string> modifiers;
//
//            // make a copy of the rate law string. We will modify this for use in addReaction
//            // as the rate law contains only place holders.
//            std::string rate_law_string = rateLaw.getRateLawString();
//            for (auto &it : roles) {
//                const std::string &rate_law_component = it.first;
//                const RoleType &role = it.second;
//                // Regex defined here as its the same expression for all cases.
//                // \b matches a word boundary (\\b escapes the first \)
//                std::regex reg(it.first + "\\b");//
//                switch (role) {
//                    case (EVO_PARAMETER): {
//                        // sample between specified boundaries and add to the model
//                        auto val = nc::random::uniform<double>(options_.getParameterLowerBound(),
//                                                               options_.getParameterUpperBound());
//                        // ensure unique parameter name. We pass in reference to used parameter names
//                        // so we do not have to reload the model each time we add a parameter (performance reasons).
//                        std::string parameter_name = generateUniqueParameterID(0, rate_law_component,
//                                                                               current_model_parameters);
//                        rr_->addParameter(parameter_name, val, false);
//                        current_model_parameters.push_back(parameter_name);// add to list of parameter names
//                        // now ensure the placeholder (it.first) contains the newly generated parameter name
//                        rate_law_string = regex_replace(rate_law_string, reg, parameter_name);
//                        break;
//                    }
//                    case (EVO_SUBSTRATE): {
//                        std::string substrate = species_ids[species_ids.size() - 1];
//                        substrates.push_back(substrate);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, substrate);
//                        break;
//                    }
//                    case (EVO_PRODUCT): {
//                        std::string product = species_ids[species_ids.size() - 1];
//                        products.push_back(product);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, product);
//                        break;
//                    }
//                    case (EVO_MODIFIER): {
//                        std::string modifier = species_ids[species_ids.size() - 1];
//                        modifiers.push_back(modifier);
//                        species_ids.resize(species_ids.size() - 1);
//                        // now ensure the placeholder (it.first) contains the species
//                        rate_law_string = regex_replace(rate_law_string, reg, modifier);
//                        break;
//                    }
//                    default:
//                        LOGIC_ERROR << "Unknown it specified";
//                }
//            }
//            reaction_name << "R" << reaction_number;
//            getRR()->addReaction(reaction_name.str(), substrates, products, rate_law_string, false);
//            reaction_name.str("");// clear the stream
//        }

//    }


}// namespace evo