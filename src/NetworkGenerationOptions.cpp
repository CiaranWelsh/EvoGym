//
// Created by Ciaran on 08/09/2020.
//

#include "evo/NetworkGenerationOptions.h"

#include <utility>
#include "evogym_export.h"
#include "NumCpp.hpp"

namespace evo {

    NetworkGenerationOptions::NetworkGenerationOptions(RateLaws rateLaws) :
            rate_laws_(std::move(rateLaws)) {
        validate();
    }

    NetworkGenerationOptions::NetworkGenerationOptions(Motifs motifs)
        : motifs_(std::move(motifs)){}

    NetworkGenerationOptions::NetworkGenerationOptions(RateLaws rateLaws, Motifs motifs)
            : rate_laws_(std::move(rateLaws)), motifs_(std::move(motifs)) {}

    int NetworkGenerationOptions::getNFloatingSpecies() const {
        return nFloatingSpecies_;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setNFloatingSpecies(int nFloatingSpecies) {
        nFloatingSpecies_ = nFloatingSpecies;
        return *this;
    }

    int NetworkGenerationOptions::getNBoundarySpecies() const {
        return nBoundarySpecies_;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setNBoundarySpecies(int nBoundarySpecies) {
        nBoundarySpecies_ = nBoundarySpecies;
        return *this;
    }

    int NetworkGenerationOptions::getNReactions() const {
        return nReactions_;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setNReactions(int nReactions) {
        nReactions_ = nReactions;
        return *this;
    }

    int NetworkGenerationOptions::getNCompartments() const {
        return nCompartments_;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setNCompartments(int nCompartments) {
        nCompartments_ = nCompartments;
        return *this;
    }

    double NetworkGenerationOptions::getSpeciesLowerBound() const {
        return speciesLowerBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setSpeciesLowerBound(double speciesLowerBound) {
        NetworkGenerationOptions::speciesLowerBound = speciesLowerBound;
        return *this;
    }

    double NetworkGenerationOptions::getSpeciesUpperBound() const {
        return speciesUpperBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setSpeciesUpperBound(double speciesUpperBound) {
        NetworkGenerationOptions::speciesUpperBound = speciesUpperBound;
        return *this;
    }

    double NetworkGenerationOptions::getParameterLowerBound() const {
        return parameterLowerBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setParameterLowerBound(double parameterLowerBound) {
        NetworkGenerationOptions::parameterLowerBound = parameterLowerBound;
        return *this;
    }

    double NetworkGenerationOptions::getParameterUpperBound() const {
        return parameterUpperBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setParameterUpperBound(double parameterUpperBound) {
        NetworkGenerationOptions::parameterUpperBound = parameterUpperBound;
        return *this;
    }

    double NetworkGenerationOptions::getCompartmentLowerBound() const {
        return compartmentLowerBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setCompartmentLowerBound(double compartmentLowerBound) {
        NetworkGenerationOptions::compartmentLowerBound = compartmentLowerBound;
        return *this;
    }

    double NetworkGenerationOptions::getCompartmentUpperBound() const {
        return compartmentUpperBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setCompartmentUpperBound(double compartmentUpperBound) {
        NetworkGenerationOptions::compartmentUpperBound = compartmentUpperBound;
        return *this;
    }

    const RateLaws &NetworkGenerationOptions::getRateLaws() const {
        return rate_laws_;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setRateLaws(const RateLaws &rateLaws) {
        rate_laws_ = rateLaws;
        return *this;
    }

    int NetworkGenerationOptions::getNMotifs() const {
        return nMotifs;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setNMotifs(int nMotifs) {
        NetworkGenerationOptions::nMotifs = nMotifs;
        return *this;
    }

    void NetworkGenerationOptions::validate() const {
        if (getNMotifs() == 0 && getNReactions() == 0) {
            throw std::logic_error("Both nReactions and nMotifs are 0, meaning that "
                                   "you are trying to randomize the generation of a network "
                                   "without any reactions.");
        }
    }

    const Motifs &NetworkGenerationOptions::getMotifs() const {
        return motifs_;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setMotifs(const Motifs &motifs) {
        motifs_ = motifs;
        return *this;
    }

    int NetworkGenerationOptions::getBoundarySpeciesLowerBound() const {
        return boundarySpeciesLowerBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound) {
        NetworkGenerationOptions::boundarySpeciesLowerBound = boundarySpeciesLowerBound;
        return *this;
        return *this;
    }

    int NetworkGenerationOptions::getBoundarySpeciesUpperBound() const {
        return boundarySpeciesUpperBound;
    }

    NetworkGenerationOptions& NetworkGenerationOptions::setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound) {
        NetworkGenerationOptions::boundarySpeciesUpperBound = boundarySpeciesUpperBound;
        return *this;
    }
    unsigned int NetworkGenerationOptions::getSeed() const {
        return seed;
    }
    NetworkGenerationOptions& NetworkGenerationOptions::setSeed(unsigned int seed) {
        NetworkGenerationOptions::seed = seed;
        nc::random::seed(seed);
        return *this;
    }

}













