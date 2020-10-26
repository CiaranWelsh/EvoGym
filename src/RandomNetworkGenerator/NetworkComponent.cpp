
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


    bool Compartments::operator==(const Compartments &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               values == rhs.values;
    }

    bool Compartments::operator!=(const Compartments &rhs) const {
        return !(rhs == *this);
    }

    bool Compartments::contains(const std::string &compartment) {
        return elementInVector<std::string>(compartment, ids);
    }


    bool BoundarySpecies::operator==(const BoundarySpecies &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               compartment_index == rhs.compartment_index &&
               values == rhs.values;
    }

    bool BoundarySpecies::operator!=(const BoundarySpecies &rhs) const {
        return !(rhs == *this);
    }

    bool BoundarySpecies::contains(const std::string &id, const int index) {
        int idx = indexOfElementInVector<std::string>(id, ids);
        if (idx < 0)
            return false;
        return index == compartment_index[idx];
    }

    bool FloatingSpecies::operator==(const FloatingSpecies &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               compartment_index == rhs.compartment_index &&
               values == rhs.values;
    }

    bool FloatingSpecies::operator!=(const FloatingSpecies &rhs) const {
        return !(rhs == *this);
    }

    bool FloatingSpecies::contains(const std::string &id, const int index) {
        int idx = indexOfElementInVector<std::string>(id, ids);
        if (idx < 0)
            return false;
        return index == compartment_index[idx];
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

    bool Reactions::contains(
            std::vector<int> s,
            std::vector<int> p,
            std::vector<int> m,
            evoRateLaw rateLaw) {
        // we first sort s, p and m sub vectors (Not the outer vector as that would be a bug)
        for (auto &i: substrates){
            std::sort(i.begin(), i.end());
        }

        for (auto &i: products){
            std::sort(i.begin(), i.end());
        }

        for (auto &i: modifiers){
            std::sort(i.begin(), i.end());
        }

        // and sort our input vectors
        std::sort(s.begin(), s.end());
        std::sort(p.begin(), p.end());
        std::sort(m.begin(), m.end());

        int idx = indexOfElementInVector<std::vector<int>>(s, substrates);
        // when idx == -1 we know this reaction is not in this Reactions object
        if (idx < 0)
            return false;
        // otherwise we now have the index of the Reaction we are looking at
        // and we can check the other elements
        return substrates[idx] == s
            && products[idx] == p
            && modifiers[idx] == m
            && rate_laws[idx] == rateLaw;
    }

}