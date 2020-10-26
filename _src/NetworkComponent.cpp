
#include "evo/NetworkComponent.h"


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

    Reactions::Reactions(int num) {
        substrates.resize(num);
        products.resize(num);
        modifiers.resize(num);
        rate_laws.resize(num);
        ids.resize(num);
    }

}