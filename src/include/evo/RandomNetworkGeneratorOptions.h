//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGYM_RANDOMNETWORKGENERATOROPTIONS_H
#define EVOGYM_RANDOMNETWORKGENERATOROPTIONS_H

#include <chrono>

#include "rr/Dictionary.h"
#include "sbml/SBMLTypes.h"

#include "evo/Motif.h"
#include "evo/RateLaw.h"
#include "evo/evogym_export.h"

namespace evo {

    class EVOGYM_EXPORT RandomNetworkGeneratorOptions {
    private:
        int nFloatingSpecies_ = 3;
        int nBoundarySpecies_ = 1;
        int nReactions_ = 4;
        int nMotifs = 0;
        int nCompartments_ = 1;

        double speciesLowerBound = 0.0;
        double speciesUpperBound = 10.0;
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

        /* place for user specified seed. Default 0 means use random seed */
        unsigned long long seed_ = 0;

        void validate() const;

    public:
        RandomNetworkGeneratorOptions() = default;

        explicit RandomNetworkGeneratorOptions(RateLaws rateLaws);

        explicit RandomNetworkGeneratorOptions(Motifs motifs);

        RandomNetworkGeneratorOptions(RateLaws rateLaws, Motifs motifs);

        const std::string &getCoreSbml() const;

        RandomNetworkGeneratorOptions &setCoreSbml(const std::string &coreSbml);

        unsigned long long int getSeed() const;

        RandomNetworkGeneratorOptions &setSeed(unsigned long long int seed);

        int getBoundarySpeciesLowerBound() const;

        RandomNetworkGeneratorOptions &setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound);

        int getBoundarySpeciesUpperBound() const;

        RandomNetworkGeneratorOptions &setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound);

        const Motifs &getMotifs() const;

        RandomNetworkGeneratorOptions &setMotifs(const Motifs &motifs);

        int getNMotifs() const;

        RandomNetworkGeneratorOptions &setNMotifs(int nMotifs);

        int getNFloatingSpecies() const;

        RandomNetworkGeneratorOptions &setNFloatingSpecies(int nFloatingSpecies);

        int getNBoundarySpecies() const;

        RandomNetworkGeneratorOptions &setNBoundarySpecies(int nBoundarySpecies);

        int getNReactions() const;

        RandomNetworkGeneratorOptions &setNReactions(int nReactions);

        int getNCompartments() const;

        RandomNetworkGeneratorOptions &setNCompartments(int nCompartments);

        double getSpeciesLowerBound() const;

        RandomNetworkGeneratorOptions &setSpeciesLowerBound(double speciesLowerBound);

        double getSpeciesUpperBound() const;

        RandomNetworkGeneratorOptions &setSpeciesUpperBound(double speciesUpperBound);

        double getParameterLowerBound() const;

        RandomNetworkGeneratorOptions &setParameterLowerBound(double parameterLowerBound);

        double getParameterUpperBound() const;

        RandomNetworkGeneratorOptions &setParameterUpperBound(double parameterUpperBound);

        double getCompartmentLowerBound() const;

        RandomNetworkGeneratorOptions &setCompartmentLowerBound(double compartmentLowerBound);

        double getCompartmentUpperBound() const;

        RandomNetworkGeneratorOptions &setCompartmentUpperBound(double compartmentUpperBound);

        const RateLaws &getRateLaws() const;

        RandomNetworkGeneratorOptions &setRateLaws(const RateLaws &rateLaws);
        const std::string &getCoreSBML() const;
        void setCoreSBML(const std::string &coreSbml);
    };
}// namespace evo


#endif//EVOGYM_RANDOMNETWORKGENERATOROPTIONS_H
