//
// Created by Ciaran on 08/09/2020.
//

#include "sbml/SBMLTypes.h"
#include <regex>

#include "evo/RateLaw.h"
#include "evo/evo_error.h"

namespace evo {

    RateLaw::RateLaw(std::string name, const std::string &rate_law_string, RoleMap roles)
        : name_(std::move(name)),
          rate_law_string_(rate_law_string),
          rate_law_(libsbml::SBML_parseFormula(rate_law_string.c_str())),
          roles_(std::move(roles)) {
        unpackRateLaw();
        validateRoleMap();
    }
    void RateLaw::setName(const std::string &name) {
        name_ = name;
    }
    void RateLaw::setRateLaw(libsbml::ASTNode *rateLaw) {
        rate_law_ = rateLaw;
    }
    const std::string &RateLaw::getRateLawString() const {
        return rate_law_string_;
    }
    void RateLaw::setRateLawString(const std::string &rateLawString) {
        rate_law_string_ = rateLawString;
    }
    void RateLaw::setRoles(const RoleMap &roles) {
        roles_ = roles;
    }
    void RateLaw::setRateLawElements(const std::set<std::string> &rateLawElements) {
        rate_law_elements_ = rateLawElements;
    }
    void RateLaw::unpackRateLaw(std::vector<libsbml::ASTNode *> rate_law_terms) {
        /*
         * When rate_law_terms is empty, the recursive function is being called for the first time
         * so we need to populate the rate_law_terms with the parent equation that we
         * want to get variables from.
         */
        if (rate_law_terms.empty()) {
            rate_law_terms.push_back(rate_law_);
        }

        /*
         * We iterate over the vector of libsbml::ASTNode* pointers; if we encounter
         * a leaf node (aka no children) we add the string representation of the node to
         * the rate_law_elements_ vector. When we encounter a branch node (i.e. 1 or more children)
         * we construct a new rate_law_terms vector from the children of each element
         * of the current rate_law_terms vector.
         */
        for (auto &rate_law_term : rate_law_terms) {

            if (rate_law_term->getNumChildren() == 0) {
                std::string elementary_term_string = libsbml::SBML_formulaToString(rate_law_term);

                // throw an error when user has given a variable name like S1 or K2. The parameters will
                // be enumarated automatically.
                if (std::regex_match(elementary_term_string, std::regex("\\d$"))) {
                    INVALID_ARGUMENT_ERROR("The elementary term of the rate law called \"" + getName() + "\" ends with a digit. Please rename this term "
                                                                                                         "so that it does not.");
                }
                rate_law_elements_.insert(libsbml::SBML_formulaToString(rate_law_term));
            } else {
                std::vector<libsbml::ASTNode *> new_rate_law_terms;
                for (int i = 0; i < rate_law_term->getNumChildren(); i++) {
                    auto node_type = rate_law_term->getChild(i)->getType();
                    // exclude integers or doubles. These are parameters, like K
                    if (node_type == libsbml::AST_INTEGER ||
                        node_type == libsbml::AST_REAL ||
                        node_type == libsbml::AST_REAL_E) {
                        continue;
                    }
                    new_rate_law_terms.push_back(rate_law_term->getChild(i));
                }
                unpackRateLaw(new_rate_law_terms);
            }
        }
    }

    const std::set<std::string> &RateLaw::getRateLawElements() const {
        return rate_law_elements_;
    }

    void RateLaw::validateRoleMap() {
        // this was an inaccurate error to throw
        //        for (auto &role: roles_){
        //            if(getRateLawElements().find(role.first) == getRateLawElements().end()){
        //                // role not found in rate law. This is an input error
        //                throw std::invalid_argument("Invalid role map: element name \"" + role.first +
        //                                            "\" is not in your role map. Please check your input "
        //                                            "to RateLaw.");
        //
        //            }
        //        }
    }

    const std::string &RateLaw::getName() const {
        return name_;
    }

    libsbml::ASTNode *RateLaw::getRateLaw() const {
        return rate_law_;
    }

    const RoleMap &RateLaw::getRoles() const {
        return roles_;
    }

    RateLaws massActionRateLaws() {
        RateLaws rateLaws;
        rateLaws["uni-uni"] = RateLaw("uni-uni", "k*A",
                                      RoleMap({
                                              {"k", EVO_PARAMETER},
                                              {"A", EVO_SUBSTRATE},
                                              {"B", EVO_PRODUCT},
                                      }));

        rateLaws["uni-bi"] = RateLaw("uni-bi", "k*A",
                                     RoleMap({
                                             {"k", EVO_PARAMETER},
                                             {"A", EVO_SUBSTRATE},
                                             {"B", EVO_PRODUCT},
                                             {"C", EVO_PRODUCT},
                                     }));

        rateLaws["bi-uni"] = RateLaw("bi-uni", "k*A*B",
                                     RoleMap({
                                             {"k", EVO_PARAMETER},
                                             {"A", EVO_SUBSTRATE},
                                             {"B", EVO_SUBSTRATE},
                                             {"C", EVO_PRODUCT},
                                     }));
        rateLaws["bi-bi"] = RateLaw("bi-bi", "k*A*B",
                                    RoleMap({
                                            {"k", EVO_PARAMETER},
                                            {"A", EVO_SUBSTRATE},
                                            {"B", EVO_SUBSTRATE},
                                            {"C", EVO_PRODUCT},
                                            {"D", EVO_PRODUCT},
                                    }));
        return rateLaws;
    }

}// namespace evo
