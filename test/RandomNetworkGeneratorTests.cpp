//
// Created by Ciaran on 09/09/2020.
//

#include "gtest/gtest.h"

#include "evo/NetworkGenerationOptions.h"
#include "evo/RandomNetworkGenerator.h"
#include "evo/seed.h"

#include "rr/ExecutableModelFactory.h"

using namespace evo;
using namespace rr;

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
    };
};


TEST_F(RandomNetworkGeneratorTests, TestRandomSeedClock) {
    NetworkGenerationOptions options(rateLaws);
    SET_CLOCK_SEED;
    int random = nc::random::randInt(10000000);
    std::cout << random << std::endl;
    ASSERT_NE(6492525, random);
    // 6492525 was what I got the first time I ran this.
    // highly unlikey to happen again.
}

TEST_F(RandomNetworkGeneratorTests, TestSetRandomSeed) {
        NetworkGenerationOptions options(rateLaws);
// create new seed
#ifdef SEED
#undef SEED
#endif
#define SEED 14
    SET_CLOCK_SEED(SEED);
    int random = nc::random::randInt(10000000);
    std::cout << random << std::endl;
    ASSERT_EQ(6720983, random);

// replace the SEED for other tests
#undef SEED
#define SEED std::chrono::system_clock::now().time_since_epoch().count()
    SET_CLOCK_SEED;
}


TEST_F(RandomNetworkGeneratorTests, TestCreateRRModelWithoutSBMLCore) {
    NetworkGenerationOptions options(rateLaws);
    RandomNetworkGenerator generator(options);
    ASSERT_EQ(0, generator.getRR()->getNumberOfFloatingSpecies());
}

TEST_F(RandomNetworkGeneratorTests, TestCreateRRModelWithSBMLCore) {
    NetworkGenerationOptions options(rateLaws);
    options.setCoreSBML(sbml);
    RandomNetworkGenerator generator(options);
    ASSERT_EQ(2, generator.getRR()->getNumberOfFloatingSpecies());
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
    nc::NdArray<int> arr(nc::Shape(1, generator.rr_->getNumberOfCompartments()));
    for (int i = 0; i < generator.rr_->getNumberOfCompartments(); i++) {
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
            .setNBoundarySpecies(2)
            .setBoundarySpeciesLowerBound(0)
            .setBoundarySpeciesUpperBound(4);
    RandomNetworkGenerator rng(options);
    std::vector<std::string> ids = rng.getRR()->getBoundarySpeciesIds();
    std::vector<std::string> expected_ids({"I0", "I1"});
    ASSERT_EQ(expected_ids, ids);

    nc::random::seed(4);
    std::vector<double> amounts = rng.getRR()->getBoundarySpeciesConcentrations();
    std::vector<double> expected = {0.0, 1.0};
    ASSERT_EQ(expected, amounts);
    ExecutableModel m = rng.getRR()->getModel()

}

TEST_F(RandomNetworkGeneratorTests, TestCreateFloatingSpecies) {
    NetworkGenerationOptions options(rateLaws);
    options.setNCompartments(2)
            .setNFloatingSpecies(10)
            .setSpeciesLowerBound(0.1)
            .setSpeciesUpperBound(10.0);
}


TEST_F(RandomNetworkGeneratorTests, test2) {
    RoadRunner rr;
    rr.addCompartment("C1", 1.0, false);
    rr.addCompartment("C2", 1.0, true);

    // deprecated!
    auto x = rr.getCompartmentIds();
    for (auto &it : x) {
        std::cout << it << ",";
    }// outputs: "C1,C2,"

    // deprecated
    int n = rr.getNumberOfCompartments();// 2
}
