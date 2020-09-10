//
// Created by Ciaran on 08/09/2020.
//

#include "evo/NetworkGenerationOptions.h"

#include <utility>
#include "evogym_export.h"


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

    void NetworkGenerationOptions::setNFloatingSpecies(int nFloatingSpecies) {
        nFloatingSpecies_ = nFloatingSpecies;
    }

    int NetworkGenerationOptions::getNBoundarySpecies() const {
        return nBoundarySpecies_;
    }

    void NetworkGenerationOptions::setNBoundarySpecies(int nBoundarySpecies) {
        nBoundarySpecies_ = nBoundarySpecies;
    }

    int NetworkGenerationOptions::getNReactions() const {
        return nReactions_;
    }

    void NetworkGenerationOptions::setNReactions(int nReactions) {
        nReactions_ = nReactions;
    }

    int NetworkGenerationOptions::getNCompartments() const {
        return nCompartments_;
    }

    void NetworkGenerationOptions::setNCompartments(int nCompartments) {
        nCompartments_ = nCompartments;
    }

    double NetworkGenerationOptions::getSpeciesLowerBound() const {
        return speciesLowerBound;
    }

    void NetworkGenerationOptions::setSpeciesLowerBound(double speciesLowerBound) {
        NetworkGenerationOptions::speciesLowerBound = speciesLowerBound;
    }

    double NetworkGenerationOptions::getSpeciesUpperBound() const {
        return speciesUpperBound;
    }

    void NetworkGenerationOptions::setSpeciesUpperBound(double speciesUpperBound) {
        NetworkGenerationOptions::speciesUpperBound = speciesUpperBound;
    }

    double NetworkGenerationOptions::getParameterLowerBound() const {
        return parameterLowerBound;
    }

    void NetworkGenerationOptions::setParameterLowerBound(double parameterLowerBound) {
        NetworkGenerationOptions::parameterLowerBound = parameterLowerBound;
    }

    double NetworkGenerationOptions::getParameterUpperBound() const {
        return parameterUpperBound;
    }

    void NetworkGenerationOptions::setParameterUpperBound(double parameterUpperBound) {
        NetworkGenerationOptions::parameterUpperBound = parameterUpperBound;
    }

    double NetworkGenerationOptions::getCompartmentLowerBound() const {
        return compartmentLowerBound;
    }

    void NetworkGenerationOptions::setCompartmentLowerBound(double compartmentLowerBound) {
        NetworkGenerationOptions::compartmentLowerBound = compartmentLowerBound;
    }

    double NetworkGenerationOptions::getCompartmentUpperBound() const {
        return compartmentUpperBound;
    }

    void NetworkGenerationOptions::setCompartmentUpperBound(double compartmentUpperBound) {
        NetworkGenerationOptions::compartmentUpperBound = compartmentUpperBound;
    }

    const RateLaws &NetworkGenerationOptions::getRateLaws() const {
        return rate_laws_;
    }

    void NetworkGenerationOptions::setRateLaws(const RateLaws &rateLaws) {
        rate_laws_ = rateLaws;
    }

    int NetworkGenerationOptions::getNMotifs() const {
        return nMotifs;
    }

    void NetworkGenerationOptions::setNMotifs(int nMotifs) {
        NetworkGenerationOptions::nMotifs = nMotifs;
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

    void NetworkGenerationOptions::setMotifs(const Motifs &motifs) {
        motifs_ = motifs;
    }

    int NetworkGenerationOptions::getBoundarySpeciesLowerBound() const {
        return boundarySpeciesLowerBound;
    }

    void NetworkGenerationOptions::setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound) {
        NetworkGenerationOptions::boundarySpeciesLowerBound = boundarySpeciesLowerBound;
    }

    int NetworkGenerationOptions::getBoundarySpeciesUpperBound() const {
        return boundarySpeciesUpperBound;
    }

    void NetworkGenerationOptions::setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound) {
        NetworkGenerationOptions::boundarySpeciesUpperBound = boundarySpeciesUpperBound;
    }

}













