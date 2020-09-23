//
// Created by Ciaran on 09/09/2020.
//

#include "gtest/gtest.h"

#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/logger.h"
#include "rr/rrRoadRunner.h"
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

    RandomNetworkGeneratorTests() {
        rateLaws["uni-bi"] = RateLaw("uni-bi", "k*A", RoleMap({{"k", EVO_PARAMETER}, {"A", EVO_SUBSTRATE}, {"B", EVO_PRODUCT}}));
        rateLaws["uni-uni"] = RateLaw("uni-uni", "k*A",
                                      RoleMap({{"k", EVO_PARAMETER},
                                               {"A", EVO_SUBSTRATE}}));
    };
};


TEST_F(RandomNetworkGeneratorTests, TestCreRModelWithoutSBMLCore) {
    RoadRunner rr;
    rr.addCompartment("c1", 1);
    rr.addSpecies("s1", "c1", 1);
    rr.getSBML();
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNFloatingSpecies(6);
    RandomNetworkGenerator generator(&options);
    ASSERT_EQ(6, generator.getRR()->getModel()->getNumFloatingSpecies());
}

TEST_F(RandomNetworkGeneratorTests, TestCreateRRModelWithoutSBMLCore) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNFloatingSpecies(6);
    RandomNetworkGenerator generator(&options);
    ASSERT_EQ(6, generator.getRR()->getModel()->getNumFloatingSpecies());
}

TEST_F(RandomNetworkGeneratorTests, TestCreateRRModelWithSBMLCore) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setCoreSBML(sbml);
    options.setNFloatingSpecies(6);
    RandomNetworkGenerator generator(&options);
    ASSERT_EQ(8, generator.getRR()->getModel()->getNumFloatingSpecies());
}

TEST_F(RandomNetworkGeneratorTests, TestCompartmentsNum) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(10);
    RandomNetworkGenerator generator(&options);
    std::vector<std::string> comps = generator.rr_->getCompartmentIds();
    ASSERT_EQ(10, comps.size());
}

TEST_F(RandomNetworkGeneratorTests, TestCompartmentsValues) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(10);
    options.setCompartmentLowerBound(0);
    options.setCompartmentUpperBound(10);
    RandomNetworkGenerator generator(&options);
    const int &num_comp = generator.rr_->getModel()->getNumCompartments();
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

    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(2)
            .setNBoundarySpecies(6)
            .setBoundarySpeciesLowerBound(0)
            .setBoundarySpeciesUpperBound(1000000);
    RandomNetworkGenerator rng(&options);
    ls::Matrix<double> amounts = rng.getRR()->getBoundarySpeciesConcentrationsNamedArray();
    std::vector<std::string> expected_ids({"I0", "I1", "I2", "I3", "I4", "I5"});
    ASSERT_EQ(expected_ids, amounts.getColNames());
    const unsigned int nrow = amounts.numRows();
    const unsigned int ncol = amounts.numCols();
    auto arr = amounts.get2DMatrix((int &) nrow, (int &) ncol);
    std::vector<std::vector<double>> store(nrow, std::vector<double>(ncol));

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
    std::vector<std::vector<double>> not_expected({{265792, 212457, 960338, 919575, 741166, 741709}});
    ASSERT_NE(not_expected, store);
}

TEST_F(RandomNetworkGeneratorTests, TestCreateBoundarySpeciesSeeded) {
    //    setSeed(4);
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(2)
            .setNBoundarySpecies(6)
            .setBoundarySpeciesLowerBound(0)
            .setBoundarySpeciesUpperBound(1000000)
            .setSeed(14);
    RandomNetworkGenerator rng(&options);
    ls::Matrix<double> amounts = rng.getRR()->getBoundarySpeciesConcentrationsNamedArray();
    std::vector<std::string> expected_ids({"I0", "I1", "I2", "I3", "I4", "I5"});
    ASSERT_EQ(expected_ids, amounts.getColNames());

    std::vector<std::vector<double>> store = amounts.getValues();
    // this time we've seeded so the values are predictable
    std::vector<std::vector<double>> expected({{672099, 41611, 493558, 834295, 551567, 740876}});
    for (int i=0; i<expected.size(); i++){
        for (int j=0; j<expected[i].size(); j++) {
            EXPECT_NEAR(expected[i][j], store[i][j], 1);
        }
    }
}


TEST_F(RandomNetworkGeneratorTests, TestCreateFloatingSpeciesSeeded) {
    //    setSeed(5);
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(2)
            .setNFloatingSpecies(3)
            .setSpeciesLowerBound(0.1)
            .setSpeciesUpperBound(10.0)
            .setSeed(9);
    RandomNetworkGenerator rng(&options);
    ls::Matrix<double> amounts = rng.getRR()->getFloatingSpeciesAmountsNamedArray();

    std::vector<std::vector<double>> store = amounts.getValues();

    std::vector<std::vector<double>> expected(
            {{8.7572562648434999, 2.4358080117186298, 9.0125838738106498}});
    for (int i=0; i<expected.size(); i++){
        for (int j=0; j<expected[i].size(); j++) {
            EXPECT_NEAR(expected[i][j], store[i][j], 1);
        }
    }
}

TEST_F(RandomNetworkGeneratorTests, TestReactions) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setNCompartments(2)
            .setNFloatingSpecies(3)
            .setSpeciesLowerBound(0.1)
            .setSpeciesUpperBound(10.0);
    RandomNetworkGenerator generator(&options);
    std::cout << generator.getRR()->getSBML() << std::endl;
}


TEST_F(RandomNetworkGeneratorTests, TestSampleWithReplacement) {
    RandomNetworkGeneratorOptions options(rateLaws);
    RandomNetworkGenerator generator(&options);
    std::vector<int> x = RandomNetworkGenerator::sample_with_replacement(3, 100);
    std::vector<int> y({7, 32, 17});
    ASSERT_NE(x, y);
}

TEST_F(RandomNetworkGeneratorTests, TestSampleWithReplacementSeeded2) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setSeed(9);
    RandomNetworkGenerator generator(&options);
    std::vector<int> actual = RandomNetworkGenerator::sample_with_replacement(4, 100);
    std::vector<int> expected({45, 43, 39, 55});
    ASSERT_EQ(actual, expected);
}

TEST_F(RandomNetworkGeneratorTests, TestGenerateUniqueParameterId) {
    RandomNetworkGeneratorOptions options(rateLaws);
    RandomNetworkGenerator generator(&options);
    std::vector<std::string> x = generator.rr_->getGlobalParameterIds();
    std::string actual = generator.generateUniqueParameterID(0, "TheBase", x);
    std::string expected = "TheBase0";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RandomNetworkGeneratorTests, TestGenerateUniqueParameterId2) {
    RandomNetworkGeneratorOptions options(rateLaws);
    RandomNetworkGenerator generator(&options);
    generator.getRR()->addCompartment("Comp", 1.0, false);
    generator.getRR()->addParameter("TheBase0", 1.0, true);
    std::vector<std::string> x = generator.rr_->getGlobalParameterIds();
    std::string actual = generator.generateUniqueParameterID(0, "TheBase", x);
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

TEST_F(RandomNetworkGeneratorTests, TestGlobalParametersBeingSetCorrectly) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setSeed(2);
    RandomNetworkGenerator generator(&options);
    double k1 = generator.getRR()->getGlobalParameterByIndex(0);
    double k2 = generator.getRR()->getGlobalParameterByIndex(1);
    ASSERT_NEAR(1.08653831902689, k1, 0.0001);
    ASSERT_NEAR(9.6871122082640806, k2, 0.0001);
}

TEST_F(RandomNetworkGeneratorTests, TestStoiciometryMatrix) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setSeed(5);
    RandomNetworkGenerator generator(&options);
    std::string x = generator.getRR()->getSBML();
    std::cout << x << std::endl;

    ls::Matrix<double> stoic = generator.getRR()->getFullStoichiometryMatrix();
    //    auto actual = stoic.getValues();
    //    std::vector<std::vector<double>> expected = {
    //            { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, -1, 0 }
    //    };
    //    ASSERT_EQ(expected, actual);
}

TEST_F(RandomNetworkGeneratorTests, TestTimeSeries) {
    RandomNetworkGeneratorOptions options(rateLaws);
    options.setSeed(5);
    RandomNetworkGenerator generator(&options);

    SimulateOptions simulateOptions;
    simulateOptions.start = 0;
    simulateOptions.duration = 100;
    simulateOptions.steps = 101;

    //    auto rr = generator.getRR();
    //
    ////    ls::Matrix<double> sim = generator.getRR()->simulate(&simulateOptions);
    //
    //    ASSERT_EQ(expected, actual);
}


TEST_F(RandomNetworkGeneratorTests, TimeNetworkGeneration) {
    auto t1 = std::chrono::high_resolution_clock::now();
    RandomNetworkGeneratorOptions options(rateLaws);

    int n = 100;

    for (int i = 0; i < n; i++) {
        RandomNetworkGenerator generator(&options);
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "It took : " << duration << " milliseconds to build " << n << " models.";
}

TEST_F(RandomNetworkGeneratorTests, x) {
    RateLaws rl;
    rl["uni-uni"] = RateLaw("uni-uni", "k*A", RoleMap({
                                                      {"k", EVO_PARAMETER},
                                                      {"A", EVO_SUBSTRATE},
                                                      {"B", EVO_PRODUCT},
                                              }));
    RandomNetworkGeneratorOptions options(rl);
    options.setNCompartments(1);
    options.setNReactions(3);
    options.setNBoundarySpecies(1);
    options.setNFloatingSpecies(3);

    int N = 10;

    //    std::vector<std::vector<std::vector<double>>> vector_of_matrices;
    std::vector<ls::Matrix<double>> vector_of_matrices;
    LOG("here");
    std::vector<int> counts;
    LOG("here");
    for (int i = 0; i < N; i++) {
        LOG("here");
        RandomNetworkGenerator generator(&options);
        LOG("here");
        vector_of_matrices.push_back(generator.getRR()->getFullStoichiometryMatrix());
    }

//        std::cout << (m == )
//        for (auto j = 0; j < i; j++) {
//            if (m != vector_of_matrices[j]) {// not yet seen already
//                LOG("no equal");
//                vector_of_matrices.push_back(vector_of_matrices[j]);
//                counts.push_back(1);
//            } else {
//                counts[j] += 1;
//            }
//            LOG("here");
//            if (j < i){ // protect against accessing null elements of vector
//                if(m != vector_of_matrices[j]){
//                    LOG("no equal");
//                }
//            }

//                LOG("here");
//                vector_of_matrices.push_back(m);
//                LOG("here");
//                counts[j] = 1;
//                LOG("here");
//            } else {
//                LOG("here");
//                counts[j] += 1;
//                LOG("here");
//            }
//        }
//    }

//    for (int i = 0; i < 10; i++) {
//        std::cout << "counts: " << counts[i] << std::endl;
//    }


    // how to count instances of stoiciometry matrices?
    //    std::cout << (vector_of_matrices[0] == vector_of_matrices[0]) << std::endl;
}
