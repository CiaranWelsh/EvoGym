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

namespace evo {

    class RandomNetworkGenerator {

    private:
        const RandomNetworkGeneratorOptions &options_;

        void createCompartments();

        void createFloatingSpecies();

        void createBoundarySpecies();

        std::string selectRandomCompartment();


    public:
        std::unique_ptr<RoadRunner> rr_;

        explicit RandomNetworkGenerator(const RandomNetworkGeneratorOptions &options);

        /**
         *
         * @details We return a pointer so that we do not need to copy or move
         * the instantiated roadrunner instance after its been created. We can
         * simply get a list/vector of pointers to networks.
         */
        RoadRunner generate();

        const RandomNetworkGeneratorOptions &getOptions() const;

        std::vector<std::string> selectRandomSpecies(int n);

        RateLaw getRandomRateLaw() const;

        void createReactions();

        const std::unique_ptr<RoadRunner> &getRR() const;

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

    };
}// namespace evo


#endif//EVOGYM_RANDOMNETWORKGENERATOR_H
