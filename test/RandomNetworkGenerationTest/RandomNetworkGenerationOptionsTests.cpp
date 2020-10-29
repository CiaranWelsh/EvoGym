
#include "RNGOptions.h"
#include "gtest/gtest.h"

using namespace evo;

class NetworkGenerationOptionsTests: public ::testing::Test {
public:
    NetworkGenerationOptionsTests() = default;
};

TEST_F(NetworkGenerationOptionsTests, nFloatingSpecies){
    RNGOptions options;
    options.setNFloatingSpecies(4);
    int actual = options.getNFloatingSpecies();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nBoundarySpecies){
    RNGOptions options;
    options.setNBoundarySpecies(4);
    int actual = options.getNBoundarySpecies();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nReactions){
    RNGOptions options;
    options.setNReactions(4);
    int actual = options.getNReactions();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nCompartments){
    RNGOptions options;
    options.setNCompartments(4);
    int actual = options.getNCompartments();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, speciesLowerBoun){
    RNGOptions options;
    options.setFloatingSpeciesLowerBound(4.5);
    double actual = options.getFloatingSpeciesLowerBound();
    ASSERT_EQ(4.5, actual);
}
TEST_F(NetworkGenerationOptionsTests, speciesUpperBoun){
    RNGOptions options;
    options.setFloatingSpeciesUpperBound(9.4);
    double actual = options.getFloatingSpeciesUpperBound();
    ASSERT_EQ(9.4, actual);
}
TEST_F(NetworkGenerationOptionsTests, parameterLowerBoun){
    RNGOptions options;
    options.setParameterLowerBound(4);
    double actual = options.getParameterLowerBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, parameterUpperBoun){
    RNGOptions options;
    options.setParameterUpperBound(4);
    double actual = options.getParameterUpperBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, compartmentLowerBoun){
    RNGOptions options;
    options.setCompartmentLowerBound(4);
    double actual = options.getCompartmentLowerBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, compartmentUpperBoun){
    RNGOptions options;
    options.setCompartmentUpperBound(4);
    double actual = options.getCompartmentUpperBound();
    ASSERT_EQ(4, actual);
}

TEST_F(NetworkGenerationOptionsTests, Seed){
    RNGOptions options;
    options.setSeed(4);
    unsigned long long int actual = options.getSeed();
    ASSERT_EQ(4, actual);
}

/*
 * Note: Save interaction with RateLaw objects for integration tests
 */























