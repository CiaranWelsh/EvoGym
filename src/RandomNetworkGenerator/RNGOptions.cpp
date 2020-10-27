//
// Created by Ciaran on 08/09/2020.
//

#include "RNGOptions.h"

#include <utility>
#include "random_network_generator_export.h"

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
//    RandomNetworkGeneratorOptions::RandomNetworkGeneratorOptions(Motifs motifs)
//        : motifs_(std::move(motifs)){}
//
//    RandomNetworkGeneratorOptions::RandomNetworkGeneratorOptions(RateLaws rateLaws, Motifs motifs)
//            : rate_laws_(std::move(rateLaws)), motifs_(std::move(motifs)) {}
//
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

    double RNGOptions::getSpeciesLowerBound() const {
        return floatingSpeciesLowerBound;
    }

    RNGOptions &RNGOptions::setFloatingSpeciesLowerBound(double speciesLowerBound) {
        floatingSpeciesLowerBound = speciesLowerBound;
        return *this;
    }

    double RNGOptions::getSpeciesUpperBound() const {
        return floatingSpeciesUpperBound;
    }

    RNGOptions &RNGOptions::setFloatingSpeciesUpperBound(double speciesUpperBound) {
        floatingSpeciesUpperBound = speciesUpperBound;
        return *this;
    }

    double RNGOptions::getParameterLowerBound() const {
        return parameterLowerBound;
    }

    RNGOptions &RNGOptions::setParameterLowerBound(double parameterLowerBound) {
        RNGOptions::parameterLowerBound = parameterLowerBound;
        return *this;
    }

    double RNGOptions::getParameterUpperBound() const {
        return parameterUpperBound;
    }

    RNGOptions &RNGOptions::setParameterUpperBound(double parameterUpperBound) {
        RNGOptions::parameterUpperBound = parameterUpperBound;
        return *this;
    }

    double RNGOptions::getCompartmentLowerBound() const {
        return compartmentLowerBound;
    }

    RNGOptions &RNGOptions::setCompartmentLowerBound(double compartmentLowerBound) {
        RNGOptions::compartmentLowerBound = compartmentLowerBound;
        return *this;
    }

    double RNGOptions::getCompartmentUpperBound() const {
        return compartmentUpperBound;
    }

    RNGOptions &RNGOptions::setCompartmentUpperBound(double compartmentUpperBound) {
        RNGOptions::compartmentUpperBound = compartmentUpperBound;
        return *this;
    }

    const RateLaws &RNGOptions::getRateLaws() const {
        return rate_laws_;
    }

    RNGOptions &RNGOptions::setRateLaws(const RateLaws &rateLaws) {
        rate_laws_ = rateLaws;
        return *this;
    }

    int RNGOptions::getNMotifs() const {
        return nMotifs;
    }

    RNGOptions &RNGOptions::setNMotifs(int nMotifs) {
        RNGOptions::nMotifs = nMotifs;
        return *this;
    }

    void RNGOptions::validate() const {
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

    int RNGOptions::getBoundarySpeciesLowerBound() const {
        return boundarySpeciesLowerBound;
    }

    RNGOptions &RNGOptions::setBoundarySpeciesLowerBound(int boundarySpeciesLowerBound) {
        RNGOptions::boundarySpeciesLowerBound = boundarySpeciesLowerBound;
        return *this;
    }

    int RNGOptions::getBoundarySpeciesUpperBound() const {
        return boundarySpeciesUpperBound;
    }

    RNGOptions &RNGOptions::setBoundarySpeciesUpperBound(int boundarySpeciesUpperBound) {
        RNGOptions::boundarySpeciesUpperBound = boundarySpeciesUpperBound;
        return *this;
    }
    const std::string &RNGOptions::getCoreSbml() const {
        return core_sbml_;
    }
    RNGOptions &RNGOptions::setCoreSbml(const std::string &coreSbml) {
        core_sbml_ = coreSbml;
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













