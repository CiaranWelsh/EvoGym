//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGYM_RANDOMNETWORKGENERATOROPTIONS_H
#define EVOGYM_RANDOMNETWORKGENERATOROPTIONS_H

#include <chrono>

#include "rr/Dictionary.h"
#include "sbml/SBMLTypes.h"

#include "evo/Motif.h"
#include "evo/EvoRateLaw.h"
#include "evo/evogym_export.h"

namespace evo {

    class EVOGYM_EXPORT RandomNetworkGeneratorOptions {
    private:
        int nFloatingSpecies_ = 3;
        int nBoundarySpecies_ = 1;
        int nReactions_ = 4;
        int nMotifs = 0;
        int nCompartments_ = 1;

        double floatingSpeciesLowerBound = 0.0;
        double floatingSpeciesUpperBound = 10.0;
        int boundarySpeciesLowerBound = 0;
        int boundarySpeciesUpperBound = 1;
        double parameterLowerBound = 0.1;
        double parameterUpperBound = 10.0;
        double compartmentLowerBound = 1.0;
        double compartmentUpperBound = 1.0;

        RateLaws rate_laws_;
        Motifs motifs_;

        // for when we want the random model with a core component
        std::string core_sbml_;

        unsigned long long seed_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        void validate() const;

    public:
        RandomNetworkGeneratorOptions() = default;

        explicit RandomNetworkGeneratorOptions(RateLaws rateLaws);

        explicit RandomNetworkGeneratorOptions(Motifs motifs);

        RandomNetworkGeneratorOptions(RateLaws rateLaws, Motifs motifs);

        [[nodiscard]] const std::string &getCoreSbml() const;

        RandomNetworkGeneratorOptions &setCoreSbml(const std::string &coreSbml);

        [[nodiscard]] unsigned long long int getSeed() const;

        RandomNetworkGeneratorOptions &setSeed(unsigned long long int seed);

        [[nodiscard]] int getBoundarySpeciesLowerBound() const;

        RandomNetworkGeneratorOptions &setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound);

        [[nodiscard]] int getBoundarySpeciesUpperBound() const;

        RandomNetworkGeneratorOptions &setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound);

        [[nodiscard]] const Motifs &getMotifs() const;

        RandomNetworkGeneratorOptions &setMotifs(const Motifs &motifs);

        [[nodiscard]] int getNMotifs() const;

        RandomNetworkGeneratorOptions &setNMotifs(int nMotifs);

        [[nodiscard]] int getNFloatingSpecies() const;

        RandomNetworkGeneratorOptions &setNFloatingSpecies(int nFloatingSpecies);

        [[nodiscard]] int getNBoundarySpecies() const;

        RandomNetworkGeneratorOptions &setNBoundarySpecies(int nBoundarySpecies);

        [[nodiscard]] int getNReactions() const;

        RandomNetworkGeneratorOptions &setNReactions(int nReactions);

        [[nodiscard]] int getNCompartments() const;

        RandomNetworkGeneratorOptions &setNCompartments(int nCompartments);

        [[nodiscard]] double getSpeciesLowerBound() const;

        RandomNetworkGeneratorOptions &setFloatingSpeciesLowerBound(double speciesLowerBound);

        [[nodiscard]] double getSpeciesUpperBound() const;

        RandomNetworkGeneratorOptions &setFloatingSpeciesUpperBound(double speciesUpperBound);

        [[nodiscard]] double getParameterLowerBound() const;

        RandomNetworkGeneratorOptions &setParameterLowerBound(double parameterLowerBound);

        [[nodiscard]] double getParameterUpperBound() const;

        RandomNetworkGeneratorOptions &setParameterUpperBound(double parameterUpperBound);

        [[nodiscard]] double getCompartmentLowerBound() const;

        RandomNetworkGeneratorOptions &setCompartmentLowerBound(double compartmentLowerBound);

        [[nodiscard]] double getCompartmentUpperBound() const;

        RandomNetworkGeneratorOptions &setCompartmentUpperBound(double compartmentUpperBound);

        [[nodiscard]] const RateLaws &getRateLaws() const;

        RandomNetworkGeneratorOptions &setRateLaws(const RateLaws &rateLaws);
        [[nodiscard]] const std::string &getCoreSBML() const;
        void setCoreSBML(const std::string &coreSbml);
    };
}// namespace evo


#endif//EVOGYM_RANDOMNETWORKGENERATOROPTIONS_H
