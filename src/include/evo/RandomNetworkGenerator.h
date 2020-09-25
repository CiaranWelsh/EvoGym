//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_RANDOMNETWORKGENERATOR_H
#define EVOGYM_RANDOMNETWORKGENERATOR_H

#include "NumCpp.hpp"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/evo_error.h"
#include "rr/rrExecutableModel.h"
#include "rr/rrRoadRunner.h"

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


    struct Compartments {
        std::vector<std::string> ids;
        std::vector<double> values;
    };

    struct BoundarySpecies {
        std::vector<std::string> ids;
        std::vector<int> compartment_index;
        std::vector<int> values;
    };

    struct FloatingSpecies {
        std::vector<std::string> ids;
        std::vector<int> compartment_index;
        std::vector<double> values;
    };

    class RandomNetworkGenerator {
        RandomNetworkGeneratorOptions* options_{};

        Compartments compartments_;
        BoundarySpecies boundary_species_;
        FloatingSpecies floating_species_;


        void createCompartments();

        void createFloatingSpecies();

        void createBoundarySpecies();

        int selectRandomCompartmentIndex();


    public:
        std::unique_ptr<RoadRunner> rr_;

        RandomNetworkGenerator() = default;

        explicit RandomNetworkGenerator(RandomNetworkGeneratorOptions* options);

        ~RandomNetworkGenerator();

        /**
         *
         * @details We return a pointer so that we do not need to copy or move
         * the instantiated roadrunner instance after its been created. We can
         * simply get a list/vector of pointers to networks.
         */
//        std::unique_ptr<RoadRunner> generate();


        [[nodiscard]] RandomNetworkGeneratorOptions *getOptions() const;

        [[nodiscard]] RateLaw getRandomRateLaw() const;

        [[nodiscard]] const std::unique_ptr<RoadRunner> &getRR() const;

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
        void createRRModel();

        /**
         * @Brief Take a sample of size @param nsamples from a population of size @param npop
         */
        static std::vector<int> sample_with_replacement(int nsamples, int npop);

        string generateUniqueParameterID(int number, const string &base_name, std::vector<std::string> &exclusion_list) const;

        std::vector<int> selectRandomSpeciesIndex(int n);
        void assembleModel();
    };
}// namespace evo


#endif//EVOGYM_RANDOMNETWORKGENERATOR_H
