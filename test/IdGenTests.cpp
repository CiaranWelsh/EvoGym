//
// Created by Ciaran on 4/14/2020.
//

#include "gtest/gtest.h"
#include "evo/IdGen.h"

using namespace evo;

class IdGenTests : public ::testing::Test {
public:

    IdGenTests() = default;
};

TEST_F(IdGenTests, TestCountDigits1) {
    int actual = IdGen::countDigits(5032);
    int expected = 4;
    ASSERT_EQ(actual, expected);
}

TEST_F(IdGenTests, TestCountDigits2) {
    long actual = IdGen::countDigits(50365363456);
    long expected = 11;
    ASSERT_EQ(actual, expected);
}

TEST_F(IdGenTests, TestCountDigits3) {
    int actual = IdGen::countDigits(0);
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(IdGenTests, TestCountDigits4) {
    int actual = IdGen::countDigits(7);
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(IdGenTests, TestCountDigits5) {
    int actual = IdGen::countDigits(1);
    int expected = 1;
    ASSERT_EQ(actual, expected);
}


TEST_F(IdGenTests, TestMaxNumber1) {
    IdGen metaId("metaId", 4, 3);
    int actual = metaId.maxNumber();
    int expected = 999;
    ASSERT_EQ(actual, expected);
}


TEST_F(IdGenTests, TestMaxNumber2) {
    IdGen metaId("metaId", 4, 6);
    int actual = metaId.maxNumber();
    int expected = 999999;
    ASSERT_EQ(actual, expected);
}

TEST_F(IdGenTests, TestMaxNumberFail) {
    ASSERT_THROW(IdGen
                         metaId("metaId", 106, 2), std::invalid_argument);
}

TEST_F(IdGenTests, TestGenerate) {
    IdGen metaId("#metaId", 4, 3);
    std::string actual = metaId.generate();
    std::string expected = "#metaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(IdGenTests, TestGenerate5) {
    IdGen metaId("metaId", 4, 3);
    std::string actual = metaId.generate();
    std::string expected = "#metaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(IdGenTests, TestGenerate2) {
    IdGen metaId("EvoGymID", 1453, 6);
    std::string actual = metaId.generate();
    std::string expected = "#EvoGymID001453";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(IdGenTests, TestGenerate3) {
    IdGen metaId("EvoGymID", 1453, 6);
    std::string actual = metaId.generate(9);
    std::string expected = "#EvoGymID000009";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(IdGenTests, TestGenerate4) {
    IdGen metaId("EvoGymID", 0, 4);
    std::string actual = metaId.generate();
    std::string expected = "#EvoGymID0000";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(IdGenTests, TestEquality1) {
    IdGen metaId1("EvoGymID", 1453, 6);
    IdGen metaId2("EvoGymID", 1453, 6);
    ASSERT_STREQ(metaId1.generate().c_str(), metaId2.generate().c_str());
}

TEST_F(IdGenTests, TestInequality1) {
    IdGen metaId1("EvoGymID", 55, 6);
    IdGen metaId2("EvoGymID", 1453, 6);
    ASSERT_STRNE(metaId1.generate().c_str(), metaId2.generate().c_str());
}

TEST_F(IdGenTests, AnotherTest) {
    IdGen metaId1("PhysicalEntity", 0, 4);
    std::string expected = "#PhysicalEntity0000";
    std::string actual = metaId1.generate();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}













