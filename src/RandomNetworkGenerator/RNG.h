//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGEN_RNG_H
#define EVOGEN_RNG_H

#include "NumCpp.hpp"
#include "RNGOptions.h"
#include "../evo_error.h"
#include "TypeDefs.h"
#include "NetworkComponent.h"
#include "rr/rrExecutableModel.h"
#include "rr/rrRoadRunner.h"

#include <memory>

using namespace rr;

namespace evo {

    class RNGAbstract {
        /**
         * @brief variable to hold the current value of parameter id.
         * Parameter IDs are k0 through k-whatever. The algorithm that creates this id
         * (generateUniqueID) is recursive and will keep adding 1 to Parameter ids until
         * it encounters an unseen id. This is inefficient when we start at 0 each time
         * so instead we start with current_parameter_id_number_.
         */
        unsigned long long current_parameter_id_number_ = 0;

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

    public:
        std::unique_ptr<RNGOptions> options_ = nullptr;

        /**
         * @brief store existing model parameter here. These
         * names cannot be used again
         */
        std::unordered_map<std::string, double> existing_model_parameters_;

        /**
         * @brief get a reference to the RNGOptions pointer
         */
        [[nodiscard]] const std::unique_ptr<RNGOptions> &getOptions() const;

        /**
         * @brief set the RNGOptions pointer with a pointer
         */
        void setOptions( std::unique_ptr<RNGOptions> &options);

        /**
         * @brief set the RNGOptions pointer
         */
        void setOptions( const RNGOptions& options);

        /**
         * @brief default constructor for RNG2
         * @details users of the default constructor must set the options_ field
         * before a RNG2::generate can be called
         */
        RNGAbstract() = default;

        /**
         * @brief Constructor for RNG2 that takes a
         * @param options object as argument.
         * @details a unique pointer is constructed automatically from the
         * RNGOptions passed in by user.
         */
        explicit RNGAbstract(const RNGOptions& options);

        /**
         * @brief Use this RNG to create a single RoadRunner
         * instance and @returns a unique pointer to the newly created model.
         */
        RoadRunnerPtr generate();

        /**
         * @brief Use this RNG to create a @param n RoadRunner using MPI
         * instance and @returns a vector of unique pointera to the newly created models.         *
         */
        NestedRoadRunnerPtrVector generateMPI(int n);

        /**
         * @brief Use this RNG to create a @param n RoadRunner using MPI
         * instance and @returns a vector of unique pointera to the newly created models.         *
         */
        RoadRunnerPtrVector generate(int n);


    protected:
        /**
         * @brief create a roadrunner model.
         * @details If a sbml string was given to
         * evo::RNGOptions::core_sbml_ (via the
         * evo::RNGOptions::setCoreSBML method) then this core
         * network will a subgraph in the random network. Otherwise,
         * an empty rr::RoadRunner model instance is created. When a submodel
         * is given, the options in evo::RNGOptions are in addition to
         * those already present in the core SBML model. I.e. if the sbml model has
         * 5 nodes and you specify you want 2 boundary and 3 Floating nodes, you'll
         * have a network with 10 nodes.
         */
        [[nodiscard]] std::unique_ptr<RoadRunner> createRRModel() const;

        /**
         * @brief pick a random ratelaw using a discrete uniform distribution.
         * @details the set of RateLaws defined for this RNG
         * is given as user input to RNGOptions
         */
        [[nodiscard]] evoRateLaw getRandomRateLaw() const;

        /**
         * @brief pick random number between 0 and numFloatingSpecies + numBoundarySpecies
         * @param n The number of random numbers to pick
         */
        [[nodiscard]] IntVector selectRandomSpeciesIndex(int n) const;


        /**
         * @Brief Take a sample of size @param nsamples from a population of size @param npop
         * @details implements Floyds Algorithm
         */
        static IntVector sample_with_replacement(int nsamples, int npop);

        /**
         * @brief Creates a parameter id for use in the model
         */
        [[nodiscard]] std::string generateUniqueParameterID(unsigned long long number, const std::string &base_name) const;

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
        };

    class BasicRNG : public RNGAbstract {
    public:
        using RNGAbstract::RNGAbstract;

        Compartments createCompartments() override;

        BoundarySpecies createBoundarySpecies() override;

        FloatingSpecies createFloatingSpecies() override;

        Reactions createReactions() override;
    };

    class UniqueReactionsRNG : public BasicRNG {
        int max_recursion_ = 1000;

    public:
        using BasicRNG::BasicRNG;

        /**
         * @brief Constructor for UniqueReactionsRNG that takes a
         * @param options object as argument.
         * @param max_recursion if a random reaction has been found to be already present in the model
         * this many times, the curent reactions will be returned without any further reactions.
         */
        explicit UniqueReactionsRNG(const RNGOptions& options, int max_recursion);


        Reactions createReactions() override;

        Reaction createReaction(Reactions &reactions, int reaction_number, int recursion_count);
    };

    enum eRNG {
        BASIC,
        UNIQUE_REACTIONS,
    };

    std::unique_ptr<RNGAbstract> RNGFactory(const RNGOptions &options, eRNG which);


}// namespace evo


#endif//EVOGEN_RNG_H
