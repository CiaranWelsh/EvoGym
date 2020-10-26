
#include "NetworkComponent.h"


namespace evo {

    NetworkComponent::NetworkComponent(int n) {
        ids.resize(n);
    }

    int NetworkComponent::size() const {
        return ids.size();
    }

    int NetworkComponent::empty() const {
        return ids.empty();
    }

    bool NetworkComponent::operator==(const NetworkComponent &rhs) const {
        return ids == rhs.ids;
    }

    bool NetworkComponent::operator!=(const NetworkComponent &rhs) const {
        return !(rhs == *this);
    }

    Reactions::Reactions(int num) {
        substrates.resize(num);
        products.resize(num);
        modifiers.resize(num);
        rate_laws.resize(num);
        ids.resize(num);
    }

    bool Reactions::operator==(const Reactions &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               rate_laws == rhs.rate_laws &&
               substrates == rhs.substrates &&
               products == rhs.products &&
               modifiers == rhs.modifiers;
    }

    bool Reactions::operator!=(const Reactions &rhs) const {
        return !(rhs == *this);
    }

    bool BoundarySpecies::operator==(const BoundarySpecies &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               compartment_index == rhs.compartment_index &&
               values == rhs.values;
    }

    bool BoundarySpecies::operator!=(const BoundarySpecies &rhs) const {
        return !(rhs == *this);
    }

    bool Compartments::operator==(const Compartments &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               values == rhs.values;
    }

    bool Compartments::operator!=(const Compartments &rhs) const {
        return !(rhs == *this);
    }

    bool FloatingSpecies::operator==(const FloatingSpecies &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               compartment_index == rhs.compartment_index &&
               values == rhs.values;
    }

    bool FloatingSpecies::operator!=(const FloatingSpecies &rhs) const {
        return !(rhs == *this);
    }
}