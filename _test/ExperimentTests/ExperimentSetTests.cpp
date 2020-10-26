#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MockExperiment.h"
#include "evo/ExperimentSet.h"

using namespace evo;


class ExperimentSetTests : public ::testing::Test {

public:
    ExperimentSetTests() = default;
};


TEST_F(ExperimentSetTests, TestSize){
    MockExperiment experiment;
    ExperimentSet experimentSet;
    experimentSet.addExperiment(&experiment);
    ASSERT_EQ(1, experimentSet.size());
}

TEST_F(ExperimentSetTests, TestSize2){
    MockExperiment experiment;
    ExperimentSet experimentSet(&experiment);
//    ASSERT_EQ(1, experimentSet.size());
//    EXPECT_CALL(experiment, calculateAverages)
}


























