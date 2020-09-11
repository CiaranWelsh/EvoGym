//
// Created by Ciaran on 11/09/2020.
//
#include "gtest/gtest.h"

#include "evo/RandomNumberGenerator.h"

#include <random>


using namespace evo;


class RandomNumberGeneratorTests : public ::testing::Test {
public:

    RandomNumberGeneratorTests() = default;
};


TEST_F(RandomNumberGeneratorTests, TestGenerateRandomNumbersUniformContineous){
    RandomNumberGenerator rng;
    double first = rng.uniform_real(0, 1);
    double second = rng.uniform_real(0, 1);
    ASSERT_NE(0.785548, first);
    ASSERT_NE(0.45383, second);
}

TEST_F(RandomNumberGeneratorTests, TestGeneratePredictableNumbersUniformContineous){
    RandomNumberGenerator rng(4);
    double first = rng.uniform_real(0, 10);
    double second = rng.uniform_real(0, 10);
    std::cout << first << std::endl;
    std::cout << second << std::endl;
    ASSERT_NEAR(7.8554828992887309, first, 0.0001);
    ASSERT_NEAR(4.5382974451971672, second, 0.0001);
}

TEST_F(RandomNumberGeneratorTests, TestGenerateRandomNumbersUnifomDiscrete){
    RandomNumberGenerator rng;
    int first = rng.uniform_int(0, 100000);
    int second = rng.uniform_int(0, 100000);
    ASSERT_NE(4, first);
    ASSERT_NE(40, second);
}

TEST_F(RandomNumberGeneratorTests, TestGeneratePredictableNumbersUniformDiscrete){
    RandomNumberGenerator rng(4);
    int first = rng.uniform_int(0, 10);
    int second = rng.uniform_int(0, 10);
    ASSERT_EQ(4, first);
    ASSERT_EQ(2, second);
}













