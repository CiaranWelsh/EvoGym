//
// Created by Ciaran on 08/09/2020.
//

#include "sbml/SBMLTypes.h"

int main(){
    libsbml::ASTNode_t *x = libsbml::SBML_parseFormula ("k*A*B");
    std::cout << x << std::endl;
    std::cout << SBML_formulaToString(x) << std::endl;
    std::cout << x->getNumChildren() << std::endl;

    for (int i=0; i < x->getNumChildren(); i++){
        libsbml::ASTNode_t* child = x->getChild(i);
        std:: cout << SBML_formulaToString(child) << std::endl;
//        std::cout << child->getId() << std::endl;
//        std::cout << child->getName() << std::endl;
        std::cout << child->getNumChildren() << std::endl;

    }


}
