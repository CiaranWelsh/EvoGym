//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_RANDOMNETWORKGENERATOR_H
#define EVOGYM_RANDOMNETWORKGENERATOR_H

#include "NumCpp.hpp"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/evo_error.h"
#include "evo/TypeDefs.h"
#include "evo/Population.h"
#include "rr/rrExecutableModel.h"
#include "rr/rrRoadRunner.h"
#include "evo/NetworkComponent.h"

using namespace rr;

/**
 *  todo turn random network generator into an interface
 *  create a "generate" method which will actually produce a roadrunner model Individual
 *  Maybe have MPI functionailty built in?
 *  I need to create a Reaction struct for the inheritance
 *  virtual methods become createCompartment, createFloatingSpecies, createBoundarySpecies
 *  and createReactions. Then generate will call these methods and generate a network.
 *  This is the plan, but will not be implemented just yet. Instead I'll try and work out
 *  more of the program before perfecting the implementation.
 *
 *  Next I need an Individual and a population data structure.
 *
 *  We need to implement a RandomNetworkGenerator that doesn't allow duplicate reactions
 *  It would be cool to have a reinforcement learning selected RandomNetworkGenerator
 */

namespace evo {

    class __Unused__RandomNetworkGenerator {

        /**
         * @brief create a Compartments object
         * @details Subclasses implement their own strategy
         * for creating a Compartments object
         */
        virtual Compartments createCompartments() = 0;

        /**
         * @brief Create a FloatingSpecies object.
         * @details Subclasses implement their own strategy
         * for creating a FloatingSpecies object
         */
        virtual FloatingSpecies createFloatingSpecies() = 0;

        /**
         * @brief Create a BoundarySpecies object.
         * @details Subclasses implement their own strategy
         * for creating a BoundarySpecies object
         */
        virtual BoundarySpecies createBoundarySpecies() = 0;

        /**
         * @brief Create a Reactions object.
         * @details Subclasses implement their own strategy
         * for creating a Reactions object
         */
        virtual Reactions createReactions() = 0;


    protected:
        /**
         * @brief constructs and returns an unordered map of parameters : parameter values.
         */
        [[nodiscard]] static std::unordered_map<std::string, double> getExistingModelParameters(RoadRunner &rr);

        const RandomNetworkGeneratorOptions &options_{};

        /**
         * @brief store existing model parameter here. These
         * names cannot be used again
         */
        std::unordered_map<std::string, double> existing_model_parameters_;

        /**
         * @brief Samples from a discrete uniform distribution between
         * 0 and options.getNCompartments().
         * @returns the integer for the compartment index that was selected.
         */
        int selectRandomCompartmentIndex();

        /**
         * @brief pick a random ratelaw using a discrete uniform distribution.
         * @details the set of RateLaws defined for this RandomNetworkGenerator
         * is given as user input to RandomNetworkGeneratorOptions
         */
        [[nodiscard]] EvoRateLaw getRandomRateLaw() const;

        /**
         * @brief create a roadrunner model.
         * @details If a sbml string was given to
         * evo::RandomNetworkGeneratorOptions::core_sbml_ (via the
         * evo::RandomNetworkGeneratorOptions::setCoreSBML method) then this core
         * network will a subgraph in the random network. Otherwise,
         * an empty rr::RoadRunner model instance is created. When a submodel
         * is given, the options in evo::RandomNetworkGeneratorOptions are in addition to
         * those already present in the core SBML model. I.e. if the sbml model has
         * 5 nodes and you specify you want 2 boundary and 3 Floating nodes, you'll
         * have a network with 10 nodes.
         */
        std::unique_ptr<RoadRunner> createRRModel();

        /**
         * @Brief Take a sample of size @param nsamples from a population of size @param npop
         */
        static IntVector sample_with_replacement(int nsamples, int npop);

        /**
         * @brief Creates a parameter id for use in the model
         */
        [[nodiscard]] std::string generateUniqueParameterID(int number, const string &base_name) const;

        IntVector selectRandomSpeciesIndex(int n);

        /**
         * @brief given an integer @param idx, return the string
         * for the id of the species that resides at that index
         * @details The species are indexed up to numSpecies = numBoundarySpecies + numFloatingSpecies
         * An @param idx less than numBoundarySpecies indexes boundary species and
         * floating species indexes are all offset by numBoundarySpecies.
         * : [Boundary, Boundary, Floating, floating, floating]
         *       0         1         2         3          4
         */
        static std::string
        convertSpeciesIndexToString(const BoundarySpecies &boundarySpecies, const FloatingSpecies &floatingSpecies,
                                    int idx);

        /**
         * @brief set random number generator seed to @param seed
         */
        static void setSeed(const long long &seed);

    public:

        explicit __Unused__RandomNetworkGenerator(const RandomNetworkGeneratorOptions &options);

        __Unused__RandomNetworkGenerator() = default;

        virtual ~__Unused__RandomNetworkGenerator() = default;

        /**
         * @brief use high resolution clock to set the random
         * number generator seed
         */
        static void setRandomSeed() {
            std::cout << "etting random seed" << std::endl;
            nc::random::seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        }

        /**
         * @brief use this random network generator to create
         * @param n RoadRunner instances with random model topologies
         * @returns A Population containing the roadrunner instances
         *
         */
        Population generate(int n);

        /**
         * @brief Use this RandomNetworkGenerator to create a single RoadRunner
         * instance and @returns a unique pointer to the newly created model.
         */
        std::unique_ptr<RoadRunner> generate();

        /**
         * @brief get the options associated with this RandomNetworkGenerator.
         */
        [[nodiscard]] const RandomNetworkGeneratorOptions &getOptions() const;

    };


    class NaiveRandomNetworkGenerator : public __Unused__RandomNetworkGenerator {
    public:
        using __Unused__RandomNetworkGenerator::__Unused__RandomNetworkGenerator;

        Compartments createCompartments() override;

        BoundarySpecies createBoundarySpecies() override;

        FloatingSpecies createFloatingSpecies() override;

        Reactions createReactions() override;
    };


}// namespace evo


#endif//EVOGYM_RANDOMNETWORKGENERATOR_H
