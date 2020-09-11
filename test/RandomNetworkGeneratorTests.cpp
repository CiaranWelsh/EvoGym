//
// Created by Ciaran on 09/09/2020.
//

#include "gtest/gtest.h"

#include "evo/NetworkGenerationOptions.h"
#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNumberGenerator.h"
#include "evo/seed.h"

#include <random>

#include "rr/ExecutableModelFactory.h"

using namespace evo;
using namespace rr;

/**
 * Unit test for Random Network Generator. The boundaries
 * for this unit include the RandomNetworkGenerator class,
 * along with its options class and the random seem module.
 *
 * The random seed needs to be set for once for every program. Not sure why
 * this isn't always random automatically.
 *
 * Use SET_CLOCK_SEED to set the random seed based on the current time or
 * SET_SEED(x) to set seed to x.
 */

class RandomNetworkGeneratorTests : public ::testing::Test {
public:

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
    RateLaw uni_uni;
    RateLaw uni_bi;
    RateLaws rateLaws;
    RandomNetworkGeneratorTests() {
        uni_uni = RateLaw(
                "uni-uni",
                "k*A",
                RoleMap(
                        {
                                {"k", EVO_PARAMETER},
                                {"A", EVO_SUBSTRATE},
                        }));
        uni_bi = RateLaw(
                "uni-bi",
                "k*A",
                RoleMap(
                        {
                                {"k", EVO_PARAMETER},
                                {"A", EVO_SUBSTRATE},
                                {"B", EVO_PRODUCT},
                        }));
        rateLaws["uni-uni"] = uni_uni;
        rateLaws["uni-bi"] = uni_bi;

    // the default seed in NumCpp doesn't appeat to be random.
        // that means that the seed will need to be set, once per program
//    setSeed(CLOCK_SEED); // needs to be called somewhere once per program.
    };
};


TEST_F(RandomNetworkGeneratorTests, TestRandomNumberGenerator) {
    NetworkGenerationOptions options(rateLaws);
    RandomNumberGenerator rng;
    int random = rng.uniform_int(0, 1000);
    ASSERT_NE(50, random);
}

TEST_F(RandomNetworkGeneratorTests, TestSetRandomSeed) {
    NetworkGenerationOptions options(rateLaws);
    RandomNumberGenerator rng(8);
    int random = rng.uniform_int(0, 1000);
    std::cout << random << std::endl;
    ASSERT_EQ(321, random);
}

TEST_F(RandomNetworkGeneratorTests, TestCreateRRModelWithoutSBMLCore) {
    NetworkGenerationOptions options(rateLaws);
    options.setNFloatingSpecies(6);
    RandomNetworkGenerator generator(options);
    ASSERT_EQ(6, generator.getRR()->getModel()->getNumFloatingSpecies());
}

TEST_F(RandomNetworkGeneratorTests, TestCreateRRModelWithSBMLCore) {
    NetworkGenerationOptions options(rateLaws);
    options.setCoreSBML(sbml);
    options.setNFloatingSpecies(6);
    RandomNetworkGenerator generator(options);
    ASSERT_EQ(8, generator.getRR()->getModel()->getNumFloatingSpecies());
}

TEST_F(RandomNetworkGeneratorTests, TestCompartmentsNum) {
    NetworkGenerationOptions options(rateLaws);
    options.setNCompartments(10);
    RandomNetworkGenerator generator(options);
    std::vector<std::string> comps = generator.rr_->getCompartmentIds();
    ASSERT_EQ(10, comps.size());
}

TEST_F(RandomNetworkGeneratorTests, TestCompartmentsValues) {
    NetworkGenerationOptions options(rateLaws);
    options.setNCompartments(10);
    options.setCompartmentLowerBound(0);
    options.setCompartmentUpperBound(10);
    RandomNetworkGenerator generator(options);
    const int& num_comp = generator.rr_->getModel()->getNumCompartments();
    nc::NdArray<int> arr(nc::Shape(1, num_comp));
    for (int i = 0; i < num_comp; i++) {
        arr[i] = generator.rr_->getCompartmentByIndex(i);
    }
    std::cout << arr << std::endl;
    ASSERT_FALSE(nc::all(arr != arr[0])[0]);
    ASSERT_TRUE(nc::all(arr < 10)[0]);
    ASSERT_TRUE(nc::all(arr >= 0)[0]);
}

TEST_F(RandomNetworkGeneratorTests, TestCreateBoundarySpecies) {

    NetworkGenerationOptions options(rateLaws);
    options.setNCompartments(2)
            .setNBoundarySpecies(6)
            .setBoundarySpeciesLowerBound(0)
            .setBoundarySpeciesUpperBound(1000000);
    RandomNetworkGenerator rng(options);
    ls::Matrix<double> amounts = rng.getRR()->getBoundarySpeciesConcentrationsNamedArray();
    std::vector<std::string> expected_ids({"I0", "I1", "I2", "I3", "I4", "I5"});
    ASSERT_EQ(expected_ids, amounts.getColNames());
    const unsigned int nrow = amounts.numRows();
    const unsigned int ncol = amounts.numCols();
    auto arr = amounts.get2DMatrix((int &) nrow, (int &) ncol);
    std::vector<std::vector<double> > store(nrow,std::vector<double>(ncol));

    for (int i = 0; i < amounts.numRows(); i++) {
        // preallocate columns
        for (int j = 0; j < amounts.numCols(); j++) {
            store[i][j] = arr[i][j];
        }
    }
//    std::vector<std::vector<double>> actual = amounts.getValues();
//
//    // This is what I got the first time I ran this code. Since this is stochastic
//    // we expect this to be different each time. The probability of getting this
//    // set again is 1 in 6 million - I'll take my changes
    std::vector<std::vector<double>> not_expected({ { 265792, 212457, 960338, 919575, 741166, 741709 } });
    ASSERT_NE(not_expected, store);
}

TEST_F(RandomNetworkGeneratorTests, TestCreateBoundarySpeciesSeeded) {
//    setSeed(4);
    NetworkGenerationOptions options(rateLaws);
    options.setNCompartments(2)
            .setNBoundarySpecies(6)
            .setBoundarySpeciesLowerBound(0)
            .setBoundarySpeciesUpperBound(1000000);
    RandomNetworkGenerator rng(options);
    ls::Matrix<double> amounts = rng.getRR()->getBoundarySpeciesConcentrationsNamedArray();
    std::vector<std::string> expected_ids({"I0", "I1", "I2", "I3", "I4", "I5"});
    ASSERT_EQ(expected_ids, amounts.getColNames());
    const unsigned int nrow = amounts.numRows();
    const unsigned int ncol = amounts.numCols();
    auto arr = amounts.get2DMatrix((int &) nrow, (int &) ncol);
    std::vector<std::vector<double>> store(nrow,std::vector<double>(ncol));

    for (int i = 0; i < amounts.numRows(); i++) {
        // preallocate columns
        for (int j = 0; j < amounts.numCols(); j++) {
            store[i][j] = arr[i][j];
        }
    }
//    std::vector<std::vector<double>> actual = amounts.getValues();
    // this time we've seeded so the values are predictable
    std::vector<std::vector<double>> expected({ { 785548, 594250, 547982, 841208, 756566, 674789 } });
    ASSERT_EQ(expected, store);
}


TEST_F(RandomNetworkGeneratorTests, TestCreateFloatingSpeciesSeeded) {
//    setSeed(5);
    NetworkGenerationOptions options(rateLaws);
    options.setNCompartments(2)
            .setNFloatingSpecies(3)
            .setSpeciesLowerBound(0.1)
            .setSpeciesUpperBound(10.0);
    RandomNetworkGenerator rng(options);
    ls::Matrix<double> amounts = rng.getRR()->getFloatingSpeciesAmountsNamedArray();
    const unsigned int nrow = amounts.numRows();
    const unsigned int ncol = amounts.numCols();
    auto arr = amounts.get2DMatrix((int &) nrow, (int &) ncol);
    std::vector<std::vector<double>> store(nrow,std::vector<double>(ncol));
    for (int i = 0; i < amounts.numRows(); i++) {
        for (int j = 0; j < amounts.numCols(); j++) {
            store[i][j] = arr[i][j];
        }
    }
//    std::vector<std::vector<double>> actual = amounts.getValues();
    // this time we've seeded so the values are predictable
    std::vector<double> expected(
            { 5.4841750682996704, 2.5797553728114799, 7.1356451668886898});
    for (int i=0; i<expected.size(); i++){
        std::cout << "i: " << std::endl;
        ASSERT_DOUBLE_EQ(expected[i], store[0][i]);
    }

}

TEST_F(RandomNetworkGeneratorTests, TestReactions) {
    NetworkGenerationOptions options(rateLaws);
    options.setNCompartments(2)
            .setNFloatingSpecies(3)
            .setSpeciesLowerBound(0.1)
            .setSpeciesUpperBound(10.0);
    RandomNetworkGenerator generator(options);
    std::cout << generator.getRR()->getSBML()<<std::endl;

}


TEST_F(RandomNetworkGeneratorTests, TestSampleWithReplacement) {
//    setSeed(CLOCK_SEED);
    std::vector<int> x = RandomNetworkGenerator::sample_with_replacement(10, 1000);
    std::vector<int> y({1,2,3, 4, 5,6, 7, 8, 9});
    ASSERT_EQ(x, y);
}

TEST_F(RandomNetworkGeneratorTests, TestGenerateUniqueParameterId) {
    NetworkGenerationOptions options(rateLaws);
    RandomNetworkGenerator generator(options);
    std::vector<std::string> x = generator.rr_->getGlobalParameterIds();
    std::string actual = generator.generateUniqueParameterID(0, "TheBase", x);
    std::string expected = "TheBase0";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RandomNetworkGeneratorTests, TestGenerateUniqueParameterId2) {
    NetworkGenerationOptions options(rateLaws);
    RandomNetworkGenerator generator(options);
    generator.getRR()->addCompartment("Comp",1.0, false );
    generator.getRR()->addParameter("TheBase0", 1.0, true);
    std::vector<std::string> x = generator.rr_->getGlobalParameterIds();
    std::string actual = generator.generateUniqueParameterID(0, "TheBase",x);
    std::string expected = "TheBase1";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RandomNetworkGeneratorTests, TestRegexStrategyInReactionRateLawReplacement) {
    /*
     * This is a placeholder so I don't forget.
     *
     * Presently we take the rate law given by user, say K*A*B and replace the components
     * k, A and B with suitable strings using regexes. Given that it is easy to get bitten here
     * do some rigerous testing with larger networks to ensure we've got it right.
     *
     */

}

TEST_F(RandomNetworkGeneratorTests, test) {
//    setSeed(CLOCK_SEED);
    nc::random::seed(CLOCK_SEED);
std::cout << CLOCK_SEED <<std::endl;
    NetworkGenerationOptions options(rateLaws);
    RandomNetworkGenerator generator(options);
    std::string sbml = generator.getRR()->getSBML();
    std::cout << sbml << std::endl;
}



//todo put check on when adding a reaction that we have enough species to implement the rate law    =
TEST_F(RandomNetworkGeneratorTests, test3) {
        auto seed = static_cast<nc::uint32>(CLOCK_SEED);
    nc::random::seed(seed);
    auto randValue = nc::random::uniform<float>(0, 1);
    std::cout << "seed = " << seed << " value = " << randValue << '\n';
}
