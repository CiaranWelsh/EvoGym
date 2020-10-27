
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

        // we first sort s, p and m sub vectors (Not the outer vector as that would be a bug)
        for (auto &i: substrates) {
            std::sort(i.begin(), i.end());
        }

        for (auto &i: products) {
            std::sort(i.begin(), i.end());
        }

        for (auto &i: modifiers) {
            std::sort(i.begin(), i.end());
        }

        int idx = indexOfElementInVector<std::vector<int>>(reaction.substrates_, substrates);
        std::cout << "idx: " << idx << std::endl;
        // when idx == -1 we know this reaction is not in this Reactions object
        if (idx < 0)
            return false;
        // otherwise we now have the index of the Reaction we are looking at
        // and we can check the other elements
        std::cout << "Substrates[idx]: ";
        for (auto &i: substrates[idx]){
            std::cout << i << ", ";
        }
        std::cout << std::endl;

        std::cout << "reaction.substrates: ";
        for (auto &i: reaction.substrates_){
            std::cout << i << ", ";
        }
        std::cout << std::endl;

        std::cout << "products[idx]: ";
        for (auto &i: products[idx]){
            std::cout << i << ", ";
        }

        std::cout << "reaction.prodicts: ";
        for (auto &i: reaction.products_){
            std::cout << i << ", ";
        }
        std::cout << std::endl;

        std::cout << "modifiers[idx]: ";
        for (auto &i: modifiers[idx]){
            std::cout << i << ", ";
        }
        std::cout << std::endl;


        std::cout << "reaction.modifiers: ";
        for (auto &i: reaction.modifiers_){
            std::cout << i << ", ";
        }
        std::cout << std::endl;

//        std::cout << "substrates[idx] == p: " << (substrates[idx] == reaction.substrates_) << std::endl;
//        std::cout << "products[idx] == p: " <<   (products[idx] == reaction.products_) << std::endl;
//        std::cout << "modifiers[idx] == p: " <<  (modifiers[idx] == reaction.modifiers_) << std::endl;
//        std::cout << "rate_laws[idx] == p: " <<  (rate_laws[idx] == reaction.rate_law_) << std::endl;
//        std::cout << "all: " << (substrates[idx] == reaction.substrates_ && products[idx] == reaction.products_
//                                 && modifiers[idx] == reaction.modifiers_
//                                 && rate_laws[idx] == reaction.rate_law_
//        ) << std::endl;

        return substrates[idx] == reaction.substrates_
               && products[idx] == reaction.products_
               && modifiers[idx] == reaction.modifiers_
               && rate_laws[idx] == reaction.rate_law_;
    }

    void Reactions::addReaction(const Reaction& reaction, int index) {
        ids[index] = reaction.name_;
        rate_laws[index] = reaction.rate_law_;
        substrates[index] = reaction.substrates_;
        products[index] = reaction.products_;
        modifiers[index] = reaction.modifiers_;
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
}