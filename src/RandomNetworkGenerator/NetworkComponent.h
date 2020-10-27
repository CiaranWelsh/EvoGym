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
         * @brief make NetworkComponent polymorphic with a virtual
         * destructor
         */
        virtual ~NetworkComponent() = default;;

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

        /**
         * @brief return true when element
         */
        template<class T>
        static bool elementInVector(T element, std::vector<T> vec) {
            return std::find(vec.begin(), vec.end(), element) != vec.end();
        }

        /**
         * @brief return index of element in vector or -1 if not found
         */
        template<class T>
        static bool indexOfElementInVector(T element, std::vector<T> vec) {
            auto it = std::find(vec.begin(), vec.end(), element);

            if (it == vec.end()){
                return -1;
            } else{
                return distance(vec.begin(), it);
            }
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

        bool contains(const std::string &compartment);

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

        bool contains(const std::string &id, const int index);

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

        bool contains(const std::string &id, int index);

    };

//    using Reaction = std::tuple<std::string, evoRateLaw, std::vector<int>, std::vector<int>, std::vector<int>>;

    struct Reaction {
        std::string name_;
        evoRateLaw rate_law_;
        std::vector<int> substrates_;
        std::vector<int> products_;
        std::vector<int> modifiers_;

        bool operator==(const Reaction &rhs) const;

        bool operator!=(const Reaction &rhs) const;

        Reaction(std::string name, evoRateLaw rateLaw,
                 std::vector<int> substrates,
                 std::vector<int> products,
                 std::vector<int> modifiers);

        Reaction() = default;

        [[nodiscard]] const std::string &getName() const;

        void setName(const string &name);

        [[nodiscard]] const evoRateLaw &getRateLaw() const;

        void setRateLaw(const evoRateLaw &rateLaw);

        [[nodiscard]] const std::vector<int> &getSubstrates() const;

        void setSubstrates(const std::vector<int> &substrates);

        [[nodiscard]] const std::vector<int> &getProducts() const;

        void setProducts(const std::vector<int> &products);

        [[nodiscard]] const std::vector<int> &getModifiers() const;

        void setModifiers(const std::vector<int> &modifiers);
    };


    /**
     * @brief Container to hold reaction information
     */
    struct Reactions : public NetworkComponent {
        using NetworkComponent::NetworkComponent;

        std::vector<Reaction> reactions;

    public:
        bool operator==(const Reactions &rhs) const;

        bool operator!=(const Reactions &rhs) const;

        Reaction& operator[](int i);

        /**
         * @brief Alternative constructor for Reactions
         * That enables preallocation of @param num Reactions.
         */
        explicit Reactions(int num);

        void addReaction(const Reaction& reaction, int index);

        /**
         * @brief overload of contains method that takes a
         * @param reaction Reaction tuple as input argument
         * @details unpack the tuple and then feed into other overload.
         *
         */
        bool contains(const Reaction& reaction);

        std::vector<Reaction>::iterator begin(){
            return reactions.begin();
        }

        std::vector<Reaction>::iterator end(){
            return reactions.end();
        }
    };
}


#endif //EVOGEN_NETWORKCOMPONENT_H
