//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGYM_NETWORKGENERATIONOPTIONS_H
#define EVOGYM_NETWORKGENERATIONOPTIONS_H

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

        // The cheapest way of randomly generating a network and storing
        // it in a data structure with other randomly generated networks
        // is to create it at the same location from which it will be used.
        // The alternative is to create the network and then move or copy the
        // network into the data structure.
        // todo consider this more

        void validate() const;

    public:
        NetworkGenerationOptions() = default;

        explicit NetworkGenerationOptions(RateLaws rateLaws);

        explicit NetworkGenerationOptions(Motifs motifs);

        NetworkGenerationOptions(RateLaws rateLaws, Motifs motifs);

        int getBoundarySpeciesLowerBound() const;

        void setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound);

        int getBoundarySpeciesUpperBound() const;

        void setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound);

        const Motifs &getMotifs() const;

        void setMotifs(const Motifs &motifs);

        int getNMotifs() const;

        void setNMotifs(int nMotifs);

        int getNFloatingSpecies() const;

        void setNFloatingSpecies(int nFloatingSpecies);

        int getNBoundarySpecies() const;

        void setNBoundarySpecies(int nBoundarySpecies);

        int getNReactions() const;

        void setNReactions(int nReactions);

        int getNCompartments() const;

        void setNCompartments(int nCompartments);

        double getSpeciesLowerBound() const;

        void setSpeciesLowerBound(double speciesLowerBound);

        double getSpeciesUpperBound() const;

        void setSpeciesUpperBound(double speciesUpperBound);

        double getParameterLowerBound() const;

        void setParameterLowerBound(double parameterLowerBound);

        double getParameterUpperBound() const;

        void setParameterUpperBound(double parameterUpperBound);

        double getCompartmentLowerBound() const;

        void setCompartmentLowerBound(double compartmentLowerBound);

        double getCompartmentUpperBound() const;

        void setCompartmentUpperBound(double compartmentUpperBound);

        const RateLaws &getRateLaws() const;

        void setRateLaws(const RateLaws &rateLaws);


    };
}


#endif //EVOGYM_NETWORKGENERATIONOPTIONS_H
