//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGYM_RATELAW_H
#define EVOGYM_RATELAW_H

#include <unordered_map>
#include <set>

#include "TypeDefs.h"
#include "evo/RoleTypes.h"
#include "evo/evogym_export.h"
#include "sbml/SBMLTypes.h"

namespace evo {



    class EVOGYM_EXPORT RateLaw {
        std::string name_;
        libsbml::ASTNode *rate_law_;
        std::string rate_law_string_;
        RoleMap roles_;
        std::set<std::string> rate_law_elements_;

        /**
         * @brief Recursively bore into the rate law using libsbml and extract
         * the variable names.
         * @param rate_law_terms: Not a "true" parameter in the sense that users do not need to manually provide an
         * argument to this function. The default is an empty vector of libsbml::ASTNode* objects, which is the starting
         * point for the recursive algorithm.
         * @details This algorithm is called from the RateLaw constructor and is private.
         */
        void unpackRateLaw(std::vector<libsbml::ASTNode *> rate_law_terms = std::vector<libsbml::ASTNode *>());

        void validateRoleMap();
    public:

        /**
         * @brief construct a RateLaw object
         * @param name" A string representing the name of the rate law
         * @param rate_law_string: A string representing the mathematical formula for the rate law
         * @param roles: an evo::RoleMap where keys are strings of variables in your rate law and values
         * are of type evo::RoleType
         */
        RateLaw(std::string name, const std::string& rate_law_string, RoleMap roles);

        /**
         * @brief default constructor for RateLaw
         */
        RateLaw() = default;

        /**
         * @brief getter for the RateLaw::rate_law_elements_ attibute.
         */
        const std::set<std::string> &getRateLawElements() const;

        const std::string &getName() const;

        libsbml::ASTNode *getRateLaw() const;

        [[nodiscard]] const RoleMap &getRoles() const;
        void setName(const std::string &name);
        void setRateLaw(libsbml::ASTNode *rateLaw);
        [[nodiscard]] const std::string &getRateLawString() const;
        void setRateLawString(const std::string &rateLawString);
        void setRoles(const RoleMap &roles);
        void setRateLawElements(const std::set<std::string> &rateLawElements);
    };

    typedef std::unordered_map<std::string, RateLaw> RateLaws;

    /**
     * @brief returns a RateLaws object containing mass action rate laws
     * @details convenience function that returns uni-uni, uni-bi, bi-uni and
     * bi-bi rate laws
     */
    RateLaws massActionRateLaws();

}


#endif //EVOGYM_RATELAW_H
