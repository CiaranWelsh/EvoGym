//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGYM_NETWORKGENERATIONOPTIONS_H
#define EVOGYM_NETWORKGENERATIONOPTIONS_H

#include <chrono>

#include "rr/Dictionary.h"
#include "sbml/SBMLTypes.h"

#include "evogym_export.h"
#include "evo/RateLaw.h"
#include "evo/Motif.h"

namespace evo {

    class EVOGYM_EXPORT NetworkGenerationOptions {
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

        void validate() const;


    public:
        NetworkGenerationOptions() = default;

        explicit NetworkGenerationOptions(RateLaws rateLaws);

        explicit NetworkGenerationOptions(Motifs motifs);

        NetworkGenerationOptions(RateLaws rateLaws, Motifs motifs);

        unsigned int getTimeNow();

        int getBoundarySpeciesLowerBound() const;

        NetworkGenerationOptions& setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound);

        int getBoundarySpeciesUpperBound() const;

        NetworkGenerationOptions& setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound);

        const Motifs &getMotifs() const;

        NetworkGenerationOptions& setMotifs(const Motifs &motifs);

        int getNMotifs() const;

        NetworkGenerationOptions& setNMotifs(int nMotifs);

        int getNFloatingSpecies() const;

        NetworkGenerationOptions& setNFloatingSpecies(int nFloatingSpecies);

        int getNBoundarySpecies() const;

        NetworkGenerationOptions& setNBoundarySpecies(int nBoundarySpecies);

        int getNReactions() const;

        NetworkGenerationOptions& setNReactions(int nReactions);

        int getNCompartments() const;

        NetworkGenerationOptions& setNCompartments(int nCompartments);

        double getSpeciesLowerBound() const;

        NetworkGenerationOptions& setSpeciesLowerBound(double speciesLowerBound);

        double getSpeciesUpperBound() const;

        NetworkGenerationOptions& setSpeciesUpperBound(double speciesUpperBound);

        double getParameterLowerBound() const;

        NetworkGenerationOptions& setParameterLowerBound(double parameterLowerBound);

        double getParameterUpperBound() const;

        NetworkGenerationOptions& setParameterUpperBound(double parameterUpperBound);

        double getCompartmentLowerBound() const;

        NetworkGenerationOptions& setCompartmentLowerBound(double compartmentLowerBound);

        double getCompartmentUpperBound() const;

        NetworkGenerationOptions& setCompartmentUpperBound(double compartmentUpperBound);

        const RateLaws &getRateLaws() const;

        NetworkGenerationOptions& setRateLaws(const RateLaws &rateLaws);
        const std::string &getCoreSBML() const;
        void setCoreSBML(const std::string &coreSbml);
    };
}


#endif //EVOGYM_NETWORKGENERATIONOPTIONS_H
