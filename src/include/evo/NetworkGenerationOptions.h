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

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

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

        unsigned int getSeed() const;

        NetworkGenerationOptions& setSeed(unsigned int seed);

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


    };
}


#endif //EVOGYM_NETWORKGENERATIONOPTIONS_H
