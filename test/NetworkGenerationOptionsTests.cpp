
#include "gtest/gtest.h"
#include "evo/NetworkGenerationOptions.h"

using namespace evo;

class NetworkGenerationOptionsTests: public ::testing::Test {
public:
    NetworkGenerationOptionsTests() = default;
};

TEST_F(NetworkGenerationOptionsTests, nFloatingSpecies){
    NetworkGenerationOptions options;
    options.setNFloatingSpecies(4);
    int actual = options.getNFloatingSpecies();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nBoundarySpecies){
    NetworkGenerationOptions options;
    options.setNBoundarySpecies(4);
    int actual = options.getNBoundarySpecies();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nReactions){
    NetworkGenerationOptions options;
    options.setNReactions(4);
    int actual = options.getNReactions();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nCompartments){
    NetworkGenerationOptions options;
    options.setNCompartments(4);
    int actual = options.getNCompartments();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, speciesLowerBoun){
    NetworkGenerationOptions options;
    options.setSpeciesLowerBound(4);
    double actual = options.getSpeciesLowerBound();
    ASSERT_EQ(4.0, actual);
}
TEST_F(NetworkGenerationOptionsTests, speciesUpperBoun){
    NetworkGenerationOptions options;
    options.setSpeciesUpperBound(4);
    double actual = options.getSpeciesUpperBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, parameterLowerBoun){
    NetworkGenerationOptions options;
    options.setParameterLowerBound(4);
    double actual = options.getParameterLowerBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, parameterUpperBoun){
    NetworkGenerationOptions options;
    options.setParameterUpperBound(4);
    double actual = options.getParameterUpperBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, compartmentLowerBoun){
    NetworkGenerationOptions options;
    options.setCompartmentLowerBound(4);
    double actual = options.getCompartmentLowerBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, compartmentUpperBoun){
    NetworkGenerationOptions options;
    options.setCompartmentUpperBound(4);
    double actual = options.getCompartmentUpperBound();
    ASSERT_EQ(4, actual);
}
TEST_F(NetworkGenerationOptionsTests, nMotifsTests){
    NetworkGenerationOptions options;
    options.setNMotifs(4);
    double actual = options.getCompartmentUpperBound();
    ASSERT_EQ(4, actual);
}

/*
 * Note: Save interaction with RateLaw objects for integration tests
 */























