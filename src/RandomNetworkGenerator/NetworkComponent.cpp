
#include "NetworkComponent.h"

#include <utility>


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
        reactions.resize(num);
    }

    Reaction::Reaction(
            std::string name, evoRateLaw rateLaw,
            std::vector<int> substrates,
            std::vector<int> products,
            std::vector<int> modifiers)
            : name_(std::move(name)), rate_law_(std::move(rateLaw)), substrates_(std::move(substrates)),
            products_(std::move(products)), modifiers_(std::move(modifiers)){
        std::sort(substrates_.begin(), substrates_.end());
        std::sort(products_.begin(), products_.end());
        std::sort(modifiers_.begin(), modifiers_.end());
    }

    bool Reactions::contains(const Reaction& reaction) {
        return std::find(reactions.begin(), reactions.end(), reaction) != reactions.end();
    }

    bool Reactions::operator==(const Reactions &rhs) const {
        return static_cast<const evo::NetworkComponent &>(*this) == static_cast<const evo::NetworkComponent &>(rhs) &&
               reactions == rhs.reactions;
    }

    bool Reactions::operator!=(const Reactions &rhs) const {
        return !(rhs == *this);
    }

    Reaction& Reactions::operator[](int i){
        return reactions[i];
    }

    void Reactions::addReaction(const Reaction& reaction, int index) {
        reactions[index] = reaction;
    }

    const string &Reaction::getName() const {
        return name_;
    }

    void Reaction::setName(const string &name) {
        Reaction::name_ = name;
    }

    const evoRateLaw &Reaction::getRateLaw() const {
        return rate_law_;
    }

    void Reaction::setRateLaw(const evoRateLaw &rateLaw) {
        rate_law_ = rateLaw;
    }

    const std::vector<int> &Reaction::getSubstrates() const {
        return substrates_;
    }

    void Reaction::setSubstrates(const std::vector<int> &substrates) {
        Reaction::substrates_ = substrates;
    }

    const std::vector<int> &Reaction::getProducts() const {
        return products_;
    }

    void Reaction::setProducts(const std::vector<int> &products) {
        Reaction::products_ = products;
    }

    const std::vector<int> &Reaction::getModifiers() const {
        return modifiers_;
    }

    void Reaction::setModifiers(const std::vector<int> &modifiers) {
        Reaction::modifiers_ = modifiers;
    }

    bool Reaction::operator==(const Reaction &rhs) const {
        return rate_law_ == rhs.rate_law_ &&
               substrates_ == rhs.substrates_ &&
               products_ == rhs.products_ &&
               modifiers_ == rhs.modifiers_;
    }

    bool Reaction::operator!=(const Reaction &rhs) const {
        return !(rhs == *this);
    }
}