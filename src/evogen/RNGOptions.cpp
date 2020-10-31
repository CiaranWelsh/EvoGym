//
// Created by Ciaran on 08/09/2020.
//

#include "RNGOptions.h"

#include <utility>
#include "rng_export.h"

namespace evo {

    RNGOptions::RNGOptions(RateLaws rateLaws) :
            rate_laws_(std::move(rateLaws)) {
        validate();
    }

    const std::string &RNGOptions::getCoreSBML() const {
        return core_sbml_;
    }
    void RNGOptions::setCoreSBML(const std::string &coreSbml) {
        core_sbml_ = coreSbml;
    }

    int RNGOptions::getNFloatingSpecies() const {
        return nFloatingSpecies_;
    }

    RNGOptions &RNGOptions::setNFloatingSpecies(int nFloatingSpecies) {
        nFloatingSpecies_ = nFloatingSpecies;
        return *this;
    }

    int RNGOptions::getNBoundarySpecies() const {
        return nBoundarySpecies_;
    }

    RNGOptions &RNGOptions::setNBoundarySpecies(int nBoundarySpecies) {
        nBoundarySpecies_ = nBoundarySpecies;
        return *this;
    }

    int RNGOptions::getNReactions() const {
        return nReactions_;
    }

    RNGOptions &RNGOptions::setNReactions(int nReactions) {
        nReactions_ = nReactions;
        return *this;
    }

    int RNGOptions::getNCompartments() const {
        return nCompartments_;
    }

    RNGOptions &RNGOptions::setNCompartments(int nCompartments) {
        nCompartments_ = nCompartments;
        return *this;
    }

    double RNGOptions::getFloatingSpeciesLowerBound() const {
        return floatingSpeciesLowerBound_;
    }

    RNGOptions &RNGOptions::setFloatingSpeciesLowerBound(double speciesLowerBound) {
        floatingSpeciesLowerBound_ = speciesLowerBound;
        return *this;
    }

    double RNGOptions::getFloatingSpeciesUpperBound() const {
        return floatingSpeciesUpperBound_;
    }

    RNGOptions &RNGOptions::setFloatingSpeciesUpperBound(double speciesUpperBound) {
        floatingSpeciesUpperBound_ = speciesUpperBound;
        return *this;
    }

    double RNGOptions::getParameterLowerBound() const {
        return parameterLowerBound_;
    }

    RNGOptions &RNGOptions::setParameterLowerBound(double parameterLowerBound) {
        RNGOptions::parameterLowerBound_ = parameterLowerBound;
        return *this;
    }

    double RNGOptions::getParameterUpperBound() const {
        return parameterUpperBound_;
    }

    RNGOptions &RNGOptions::setParameterUpperBound(double parameterUpperBound) {
        RNGOptions::parameterUpperBound_ = parameterUpperBound;
        return *this;
    }

    double RNGOptions::getCompartmentLowerBound() const {
        return compartmentLowerBound_;
    }

    RNGOptions &RNGOptions::setCompartmentLowerBound(double compartmentLowerBound) {
        RNGOptions::compartmentLowerBound_ = compartmentLowerBound;
        return *this;
    }

    double RNGOptions::getCompartmentUpperBound() const {
        return compartmentUpperBound_;
    }

    RNGOptions &RNGOptions::setCompartmentUpperBound(double compartmentUpperBound) {
        RNGOptions::compartmentUpperBound_ = compartmentUpperBound;
        return *this;
    }

    const RateLaws &RNGOptions::getRateLaws() const {
        return rate_laws_;
    }

    RNGOptions &RNGOptions::setRateLaws(const RateLaws &rateLaws) {
        rate_laws_ = rateLaws;
        return *this;
    }

    void RNGOptions::validate() const {
        if (getNReactions() == 0) {
            throw std::logic_error("nReactions is 0, meaning that "
                                   "you are trying to randomize the generation of a network "
                                   "without any reactions.");
        }
    }

    int RNGOptions::getBoundarySpeciesLowerBound() const {
        return boundarySpeciesLowerBound_;
    }

    RNGOptions &RNGOptions::setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound) {
        RNGOptions::boundarySpeciesLowerBound_ = boundarySpeciesLowerBound;
        return *this;
    }

    int RNGOptions::getBoundarySpeciesUpperBound() const {
        return boundarySpeciesUpperBound_;
    }

    RNGOptions &RNGOptions::setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound) {
        RNGOptions::boundarySpeciesUpperBound_ = boundarySpeciesUpperBound;
        return *this;
    }


    unsigned long long int RNGOptions::getSeed() const {
        return seed_;
    }

    RNGOptions &RNGOptions::setSeed(unsigned long long int seed) {
        seed_ = seed;
        return *this;
    }

}













