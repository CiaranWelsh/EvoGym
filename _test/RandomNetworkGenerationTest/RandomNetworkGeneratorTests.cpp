//
// Created by Ciaran on 09/09/2020.
//

#include "gtest/gtest.h"

#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/logger.h"
#include "evo/EvoRateLaw.h"
#include "rr/rrRoadRunner.h"
#include <random>
#include "NumCpp.hpp"

#include "rr/ExecutableModelFactory.h"

using namespace evo;
using namespace rr;



class RandomNetworkGenerator2Tests : public ::testing::Test {
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

    RandomNetworkGenerator2Tests() {
        rateLaws["uni-uni"] = EvoRateLaw("uni-uni", "k*A",
                                         RoleMap({
                                                         {"k", EVO_PARAMETER},
                                                         {"A", EVO_SUBSTRATE},
                                                         {"B", EVO_PRODUCT}}
                                         )
        );
        rateLaws["uni-bi"] = EvoRateLaw("uni-bi", "k*A",
                                        RoleMap({
                                                        {"k", EVO_PARAMETER},
                                                        {"A", EVO_SUBSTRATE},
                                                        {"B", EVO_PRODUCT},
                                                        {"C", EVO_PRODUCT}}
                                        )
        );
    };
};


TEST_F(RandomNetworkGenerator2Tests, TestNumberOfCompartments){
    // todo you haven't accounted for volume differences in multi compartment reactions.
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(4);
    options.setSeed(4);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    ASSERT_EQ(4, ind_ptr->getRRPtr()->getModel()->getNumCompartments());
}

TEST_F(RandomNetworkGenerator2Tests, TestNumberOfBoundarySpecies){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNBoundarySpecies(4);
    options.setSeed(4);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    ASSERT_EQ(4, ind_ptr->getRRPtr()->getModel()->getNumBoundarySpecies());
}

TEST_F(RandomNetworkGenerator2Tests, TestNumberOfFloatingSpecies){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNFloatingSpecies(4);
    options.setSeed(4);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    ASSERT_EQ(4, ind_ptr->getRRPtr()->getModel()->getNumFloatingSpecies());
}

TEST_F(RandomNetworkGenerator2Tests, TestNumberOfReactions){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNFloatingSpecies(4);
    options.setNReactions(5);
    options.setSeed(4);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    ASSERT_EQ(5, ind_ptr->getRRPtr()->getModel()->getNumReactions());
}

TEST_F(RandomNetworkGenerator2Tests, TestCompartmentValue){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(2);
    options.setCompartmentLowerBound(1.0);
    options.setCompartmentUpperBound(10.0);
    options.setSeed(46);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    ASSERT_DOUBLE_EQ(7.59733895439041, ind_ptr->getRRPtr()->getCompartmentByIndex(0));
    ASSERT_DOUBLE_EQ(3.2564907819767202, ind_ptr->getRRPtr()->getCompartmentByIndex(1));
}

TEST_F(RandomNetworkGenerator2Tests, TestBoundarySpeciesValue){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setBoundarySpeciesLowerBound(1);
    options.setBoundarySpeciesUpperBound(10);
    options.setNBoundarySpecies(2);
    options.setSeed(2);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    ASSERT_DOUBLE_EQ(9, ind_ptr->getRRPtr()->getBoundarySpeciesByIndex(0));
    ASSERT_DOUBLE_EQ(8, ind_ptr->getRRPtr()->getBoundarySpeciesByIndex(1));
}


TEST_F(RandomNetworkGenerator2Tests, TestFloatingSpeciesValue){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setFloatingSpeciesLowerBound(1.0);
    options.setFloatingSpeciesUpperBound(10.0);
    options.setNFloatingSpecies(2);

    options.setSeed(8);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    auto x = ind_ptr->getRRPtr()->getFloatingSpeciesConcentrationsNamedArray().getValues();
    ASSERT_DOUBLE_EQ(9.2584571916380796, x[0][0]);
    ASSERT_DOUBLE_EQ(8.7608727625994405, x[0][1]);
}

TEST_F(RandomNetworkGenerator2Tests, TestReactionStoichiometryMatrix){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNFloatingSpecies(2);
    options.setNBoundarySpecies(0);
    options.setNReactions(1);
    options.setSeed(4);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate();
    std::ostringstream actual;
    actual << ind_ptr->getRRPtr()->getFullStoichiometryMatrix();
    std::string expected = "R0\n"
                           "1\n"
                           "-1\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}


TEST_F(RandomNetworkGenerator2Tests, TestGenerateMoreThan1Model){
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNFloatingSpecies(2);
    options.setNBoundarySpecies(0);
    options.setNReactions(1);
    options.setSeed(4);
    NaiveRandomNetworkGenerator generator(options);
    auto ind_ptr = generator.generate(4);
    ASSERT_EQ(4, ind_ptr[0].size());
}




















