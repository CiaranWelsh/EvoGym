//
// Created by Ciaran on 09/09/2020.
//

#include "gtest/gtest.h"

#include "RandomNetworkGenerator.h"
#include "RNGOptions.h"
#include "logger.h"
#include "evoRateLaw.h"
#include "rr/rrRoadRunner.h"
#include <random>
#include "NumCpp.hpp"

#include "rr/ExecutableModelFactory.h"

using namespace evo;
using namespace rr;



class UniqueReactionsRNGTests : public ::testing::Test {
public:
    RateLaws rateLaws;

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"simple\" id=\"simple\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment sboTerm=\"SBO:0000410\" id=\"default_compartment\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"default_compartment\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"B\" compartment=\"default_compartment\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" value=\"5\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k1 </ci>\n"
                       "              <ci> A </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>";

    UniqueReactionsRNGTests() {
        rateLaws["uni-uni"] = evoRateLaw("uni-uni", "k*A",
                                         RoleMap({
                                                         {"k", EVO_PARAMETER},
                                                         {"A", EVO_SUBSTRATE},
                                                         {"B", EVO_PRODUCT}}
                                         )
        );
        rateLaws["uni-bi"] = evoRateLaw("uni-bi", "k*A",
                                        RoleMap({
                                                        {"k", EVO_PARAMETER},
                                                        {"A", EVO_SUBSTRATE},
                                                        {"B", EVO_PRODUCT},
                                                        {"C", EVO_PRODUCT}}
                                        )
        );
    };
};


TEST_F(UniqueReactionsRNGTests, TestNumberOfCompartments){
    RNGOptions options(rateLaws);
    options.setNCompartments(1);
    options.setNBoundarySpecies(0);
    options.setNFloatingSpecies(3);
    options.setNReactions(20);
//    options.setSeed(4);
    UniqueReactionsRNG generator(options);
    auto rr_ptr = generator.generate();
    std::cout << rr_ptr->getSBML() << std::endl;

    std::cout << rr_ptr->getModel()->getNumReactions() << std::endl;
}


















