//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGEN_RANDOMNETWORKGENERATOROPTIONS_H
#define EVOGEN_RANDOMNETWORKGENERATOROPTIONS_H

#include <chrono>

#include "rr/Dictionary.h"
#include "sbml/SBMLTypes.h"

//#include "evo/Motif.h"
#include "evoRateLaw.h"
#include "rng_export.h"

namespace evo {

    class RNG_EXPORT RNGOptions {
    private:
        int nFloatingSpecies_ = 3;
        int nBoundarySpecies_ = 1;
        int nReactions_ = 4;
        int nCompartments_ = 1;

        double floatingSpeciesLowerBound_ = 0.0;
        double floatingSpeciesUpperBound_ = 10.0;
        int boundarySpeciesLowerBound_ = 0;
        int boundarySpeciesUpperBound_ = 1;
        double parameterLowerBound_ = 0.1;
        double parameterUpperBound_ = 10.0;
        double compartmentLowerBound_ = 1.0;
        double compartmentUpperBound_ = 1.0;

        RateLaws rate_laws_;

        // for when we want the random model with a core component
        std::string core_sbml_;

        unsigned long long seed_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        void validate() const;

    public:
        RNGOptions() = default;

        explicit RNGOptions(RateLaws rateLaws);

        [[nodiscard]] unsigned long long int getSeed() const;

        RNGOptions &setSeed(unsigned long long int seed);

        [[nodiscard]] int getBoundarySpeciesLowerBound() const;

        RNGOptions &setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound);

        [[nodiscard]] int getBoundarySpeciesUpperBound() const;

        RNGOptions &setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound);

        [[nodiscard]] int getNFloatingSpecies() const;

        RNGOptions &setNFloatingSpecies(int nFloatingSpecies);

        [[nodiscard]] int getNBoundarySpecies() const;

        RNGOptions &setNBoundarySpecies(int nBoundarySpecies);

        [[nodiscard]] int getNReactions() const;

        RNGOptions &setNReactions(int nReactions);

        [[nodiscard]] int getNCompartments() const;

        RNGOptions &setNCompartments(int nCompartments);

        [[nodiscard]] double getFloatingSpeciesLowerBound() const;

        RNGOptions &setFloatingSpeciesLowerBound(double speciesLowerBound);

        [[nodiscard]] double getFloatingSpeciesUpperBound() const;

        RNGOptions &setFloatingSpeciesUpperBound(double speciesUpperBound);

        [[nodiscard]] double getParameterLowerBound() const;

        RNGOptions &setParameterLowerBound(double parameterLowerBound);

        [[nodiscard]] double getParameterUpperBound() const;

        RNGOptions &setParameterUpperBound(double parameterUpperBound);

        [[nodiscard]] double getCompartmentLowerBound() const;

        RNGOptions &setCompartmentLowerBound(double compartmentLowerBound);

        [[nodiscard]] double getCompartmentUpperBound() const;

        RNGOptions &setCompartmentUpperBound(double compartmentUpperBound);

        [[nodiscard]] const RateLaws &getRateLaws() const;

        RNGOptions &setRateLaws(const RateLaws &rateLaws);

        [[nodiscard]] const std::string &getCoreSBML() const;

        void setCoreSBML(const std::string &coreSbml);

    };
}// namespace evo


#endif//EVOGEN_RANDOMNETWORKGENERATOROPTIONS_H
