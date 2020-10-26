//
// Created by Ciaran Welsh on 30/09/2020.
//

#ifndef EVOGEN_NETWORKCOMPONENT_H
#define EVOGEN_NETWORKCOMPONENT_H

#include "TypeDefs.h"
#include "evoRateLaw.h"

namespace evo {
    struct NetworkComponent {
    public:
        StringVector ids;

        /**
         * @brief default constructor for NetworkComponent types.
         */
        NetworkComponent() = default;

        /**
         * @brief Constructor for NetworkComponent types.
         * @param n the number of elements NetworkComponent should contain
         * @details it is more efficient to preallocate a known
         * block of memory for NetworkComponent, rather than resizing when needed.
         */
        explicit NetworkComponent(int n);

        /**
         * @brief The size of a NetworkComponent is the number in the ids vector
         * @details it is assumed that the number of elements in ids is equal
         * to the number of elements in other vectors owned by NetworkComponent and subtypes,
         */
        [[nodiscard]] int size() const;

        /**
         * @brief true when the ids vector is empty.
         * @details the number of elements contained in
         * ids is assumed to be the same as the number of
         * ids in other vectors owned by NetworkComponent and subtypes.
         */
        [[nodiscard]] int empty() const;

        /**
         * @brief remove and return one item from the end of
         * @param vec
         * @details this method is static.
         */
        template<class T>
        static T popFromEndOfVector(std::vector<T> &vec) {
            const T &end = vec[vec.size() - 1];
            vec.resize(vec.size() - 1);
            return end;
        }

        bool operator==(const NetworkComponent &rhs) const;

        bool operator!=(const NetworkComponent &rhs) const;
    };

/**
 * @brief Data container for holding information about which compartments and their
 * sizes will be in a model
 */
    struct Compartments : public NetworkComponent {
        using NetworkComponent::NetworkComponent;
        DoubleVector values;

        bool operator==(const Compartments &rhs) const;

        bool operator!=(const Compartments &rhs) const;
    };

/**
 * @brief Container to hold information about which BoundarySpecies a model will contain
 */
    struct BoundarySpecies : public NetworkComponent {
        using NetworkComponent::NetworkComponent;
        IntVector compartment_index;
        IntVector values;

        bool operator==(const BoundarySpecies &rhs) const;

        bool operator!=(const BoundarySpecies &rhs) const;
    };

/**
 * @brief Container to hold information about which FloatingSpecies a model will contain
 */
    struct FloatingSpecies : public NetworkComponent {
        using NetworkComponent::NetworkComponent;
        IntVector compartment_index;
        DoubleVector values;

        bool operator==(const FloatingSpecies &rhs) const;

        bool operator!=(const FloatingSpecies &rhs) const;
    };

/**
 * @brief Container to hold reaction information
 */
    struct Reactions : public NetworkComponent {
        using NetworkComponent::NetworkComponent;
        std::vector<evoRateLaw> rate_laws;
        // a vector of int vectors for substrate indexes
        std::vector<IntVector> substrates;
        std::vector<IntVector> products;
        std::vector<IntVector> modifiers;

        bool operator==(const Reactions &rhs) const;

        bool operator!=(const Reactions &rhs) const;

    public:
        /**
         * @brief instantiate Reactions object with predefined number
         * of reactions
         */
        explicit Reactions(int num);
    };
}


#endif //EVOGEN_NETWORKCOMPONENT_H
