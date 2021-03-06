//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGEN_RATELAW_H
#define EVOGEN_RATELAW_H

#include <unordered_map>
#include <set>

#include "../TypeDefs.h"
#include "RoleTypes.h"
#include "random_network_generator_export.h"
#include "sbml/SBMLTypes.h"

namespace evo {



    class RANDOM_NETWORK_GENERATOR_EXPORT evoRateLaw {
        std::string name_;
        libsbml::ASTNode *rate_law_ = nullptr;
        std::string rate_law_string_;
        RoleMap roles_;
        std::set<std::string> rate_law_elements_;

        /**
         * @brief Recursively bore into the rate law using libsbml and extract
         * the variable names.
         * @param rate_law_terms: Not a "true" parameter in the sense that users do not need to manually provide an
         * argument to this function. The default is an empty vector of libsbml::ASTNode* objects, which is the starting
         * point for the recursive algorithm.
         * @details This algorithm is called from the EvoRateLaw constructor and is private.
         */
        void unpackRateLaw(std::vector<libsbml::ASTNode *> rate_law_terms = std::vector<libsbml::ASTNode *>());

        /**
         * @brief helper function to count instances of @param role in this RateLaw
         */
        [[nodiscard]] int countRoles(eRoleType role) const;


    public:

        /**
         * @brief construct a EvoRateLaw object
         * @param name" A string representing the name of the rate law
         * @param rate_law_string: A string representing the mathematical formula for the rate law
         * @param roles: an evo::RoleMap where keys are strings of variables in your rate law and values
         * are of type evo::RoleType
         */
        evoRateLaw(std::string name, const std::string &rate_law_string, RoleMap roles);

        /**
         * @brief default constructor for EvoRateLaw
         */
        evoRateLaw() = default;

        /**
         * @brief getter for the EvoRateLaw::rate_law_elements_ attibute.
         */
        [[nodiscard]] const std::set<std::string> &getRateLawElements() const;

        [[nodiscard]] const std::string &getName() const;

        [[nodiscard]] libsbml::ASTNode *getRateLaw() const;

        [[nodiscard]] const RoleMap &getRoles() const;

        void setName(const std::string &name);

        void setRateLaw(libsbml::ASTNode *rateLaw);

        [[nodiscard]] const std::string &getRateLawString() const;

        void setRateLawString(const std::string &rateLawString);

        void setRoles(const RoleMap &roles);

        void setRateLawElements(const std::set<std::string> &rateLawElements);

        /**
         * @brief count the number of parameters in this RateLaw
         */
        [[nodiscard]] int numParameters() const;

        /**
         * @brief count the number of substrates in this RateLaw
         */
        [[nodiscard]] int numSubstrates() const;

        /**
         * @brief count the number of products in this RateLaw
         */
        [[nodiscard]] int numProducts() const;

        /**
         * @brief count the number of modifiers in this RateLaw
         */
        [[nodiscard]] int numModifiers() const;

        bool operator==(const evoRateLaw &rhs) const;

        bool operator!=(const evoRateLaw &rhs) const;
    };
    typedef std::unordered_map<std::string, evoRateLaw> RateLaws;

    /**
     * @brief returns a RateLaws object containing mass action rate laws
     * @details convenience function that returns uni-uni, uni-bi, bi-uni and
     * bi-bi rate laws
     */
    RateLaws massActionRateLaws();

}


#endif //EVOGEN_RATELAW_H
