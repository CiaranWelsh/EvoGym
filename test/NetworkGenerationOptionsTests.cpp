
#include "evo/RandomNetworkGeneratorOptions.h"
#include "gtest/gtest.h"

using namespace evo;

class NetworkGenerationOptionsTests: public ::testing::Test {
public:
    NetworkGenerationOptionsTests() = default;
};

TEST_F(NetworkGenerationOptionsTests, nFloatingSpecies){
    RandomNetworkGeneratorOptions options;
    options.setNFloatingSpecies(4);
    int actual = options.getNFloatingSpecies();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nBoundarySpecies){
    RandomNetworkGeneratorOptions options;
    options.setNBoundarySpecies(4);
    int actual = options.getNBoundarySpecies();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nReactions){
    RandomNetworkGeneratorOptions options;
    options.setNReactions(4);
    int actual = options.getNReactions();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nCompartments){
    RandomNetworkGeneratorOptions options;
    options.setNCompartments(4);
    int actual = options.getNCompartments();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, speciesLowerBoun){
    RandomNetworkGeneratorOptions options;
    options.setSpeciesLowerBound(4);
    double actual = options.getSpeciesLowerBound();
    ASSERT_EQ(4.0, actual);
}
TEST_F(NetworkGenerationOptionsTests, speciesUpperBoun){
    RandomNetworkGeneratorOptions options;
    options.setSpeciesUpperBound(4);
    double actual = options.getSpeciesUpperBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, parameterLowerBoun){
    RandomNetworkGeneratorOptions options;
    options.setParameterLowerBound(4);
    double actual = options.getParameterLowerBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, parameterUpperBoun){
    RandomNetworkGeneratorOptions options;
    options.setParameterUpperBound(4);
    double actual = options.getParameterUpperBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, compartmentLowerBoun){
    RandomNetworkGeneratorOptions options;
    options.setCompartmentLowerBound(4);
    double actual = options.getCompartmentLowerBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, compartmentUpperBoun){
    RandomNetworkGeneratorOptions options;
    options.setCompartmentUpperBound(4);
    double actual = options.getCompartmentUpperBound();
    ASSERT_EQ(4, actual);
}

TEST_F(NetworkGenerationOptionsTests, nMotifsTests){
    RandomNetworkGeneratorOptions options;
    options.setNMotifs(4);
    double actual = options.getNMotifs();
    ASSERT_EQ(4, actual);
}

TEST_F(NetworkGenerationOptionsTests, Seed){
    RandomNetworkGeneratorOptions options;
    options.setSeed(4);
    unsigned long long int actual = options.getSeed();
    ASSERT_EQ(4, actual);
}

/*
 * Note: Save interaction with RateLaw objects for integration tests
 */























