//
// Created by Ciaran on 08/09/2020.
//

#include "evo/RandomNetworkGeneratorOptions.h"

#include <utility>
#include "evo/EVOGEN_export.h"

namespace evo {

    RandomNetworkGeneratorOptions::RandomNetworkGeneratorOptions(RateLaws rateLaws) :
            rate_laws_(std::move(rateLaws)) {
        validate();
    }

    const std::string &RandomNetworkGeneratorOptions::getCoreSBML() const {
        return core_sbml_;
    }
    void RandomNetworkGeneratorOptions::setCoreSBML(const std::string &coreSbml) {
        core_sbml_ = coreSbml;
    }
//    RandomNetworkGeneratorOptions::RandomNetworkGeneratorOptions(Motifs motifs)
//        : motifs_(std::move(motifs)){}
//
//    RandomNetworkGeneratorOptions::RandomNetworkGeneratorOptions(RateLaws rateLaws, Motifs motifs)
//            : rate_laws_(std::move(rateLaws)), motifs_(std::move(motifs)) {}
//
    int RandomNetworkGeneratorOptions::getNFloatingSpecies() const {
        return nFloatingSpecies_;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setNFloatingSpecies(int nFloatingSpecies) {
        nFloatingSpecies_ = nFloatingSpecies;
        return *this;
    }

    int RandomNetworkGeneratorOptions::getNBoundarySpecies() const {
        return nBoundarySpecies_;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setNBoundarySpecies(int nBoundarySpecies) {
        nBoundarySpecies_ = nBoundarySpecies;
        return *this;
    }

    int RandomNetworkGeneratorOptions::getNReactions() const {
        return nReactions_;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setNReactions(int nReactions) {
        nReactions_ = nReactions;
        return *this;
    }

    int RandomNetworkGeneratorOptions::getNCompartments() const {
        return nCompartments_;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setNCompartments(int nCompartments) {
        nCompartments_ = nCompartments;
        return *this;
    }

    double RandomNetworkGeneratorOptions::getSpeciesLowerBound() const {
        return floatingSpeciesLowerBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setFloatingSpeciesLowerBound(double speciesLowerBound) {
        floatingSpeciesLowerBound = speciesLowerBound;
        return *this;
    }

    double RandomNetworkGeneratorOptions::getSpeciesUpperBound() const {
        return floatingSpeciesUpperBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setFloatingSpeciesUpperBound(double speciesUpperBound) {
        floatingSpeciesUpperBound = speciesUpperBound;
        return *this;
    }

    double RandomNetworkGeneratorOptions::getParameterLowerBound() const {
        return parameterLowerBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setParameterLowerBound(double parameterLowerBound) {
        RandomNetworkGeneratorOptions::parameterLowerBound = parameterLowerBound;
        return *this;
    }

    double RandomNetworkGeneratorOptions::getParameterUpperBound() const {
        return parameterUpperBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setParameterUpperBound(double parameterUpperBound) {
        RandomNetworkGeneratorOptions::parameterUpperBound = parameterUpperBound;
        return *this;
    }

    double RandomNetworkGeneratorOptions::getCompartmentLowerBound() const {
        return compartmentLowerBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setCompartmentLowerBound(double compartmentLowerBound) {
        RandomNetworkGeneratorOptions::compartmentLowerBound = compartmentLowerBound;
        return *this;
    }

    double RandomNetworkGeneratorOptions::getCompartmentUpperBound() const {
        return compartmentUpperBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setCompartmentUpperBound(double compartmentUpperBound) {
        RandomNetworkGeneratorOptions::compartmentUpperBound = compartmentUpperBound;
        return *this;
    }

    const RateLaws &RandomNetworkGeneratorOptions::getRateLaws() const {
        return rate_laws_;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setRateLaws(const RateLaws &rateLaws) {
        rate_laws_ = rateLaws;
        return *this;
    }

    int RandomNetworkGeneratorOptions::getNMotifs() const {
        return nMotifs;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setNMotifs(int nMotifs) {
        RandomNetworkGeneratorOptions::nMotifs = nMotifs;
        return *this;
    }

    void RandomNetworkGeneratorOptions::validate() const {
        if (getNMotifs() == 0 && getNReactions() == 0) {
            throw std::logic_error("Both nReactions and nMotifs are 0, meaning that "
                                   "you are trying to randomize the generation of a network "
                                   "without any reactions.");
        }
    }

//    const Motifs &RandomNetworkGeneratorOptions::getMotifs() const {
//        return motifs_;
//    }
//
//    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setMotifs(const Motifs &motifs) {
//        motifs_ = motifs;
//        return *this;
//    }

    int RandomNetworkGeneratorOptions::getBoundarySpeciesLowerBound() const {
        return boundarySpeciesLowerBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound) {
        RandomNetworkGeneratorOptions::boundarySpeciesLowerBound = boundarySpeciesLowerBound;
        return *this;
    }

    int RandomNetworkGeneratorOptions::getBoundarySpeciesUpperBound() const {
        return boundarySpeciesUpperBound;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound) {
        RandomNetworkGeneratorOptions::boundarySpeciesUpperBound = boundarySpeciesUpperBound;
        return *this;
    }
    const std::string &RandomNetworkGeneratorOptions::getCoreSbml() const {
        return core_sbml_;
    }
    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setCoreSbml(const std::string &coreSbml) {
        core_sbml_ = coreSbml;
        return *this;
    }

    unsigned long long int RandomNetworkGeneratorOptions::getSeed() const {
        return seed_;
    }

    RandomNetworkGeneratorOptions &RandomNetworkGeneratorOptions::setSeed(unsigned long long int seed) {
        seed_ = seed;
        return *this;
    }

}













