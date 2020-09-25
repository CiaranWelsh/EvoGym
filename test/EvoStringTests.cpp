#include "gtest/gtest.h"

#include "evo/EvoString.h"

using namespace evo;

TEST(EvoStringTests, TestContainsPositive){
    EvoString string("string");
    ASSERT_TRUE(string.contains("tri"));
}

TEST(EvoStringTests, TestContainsNevative){
    EvoString string("string");
    ASSERT_TRUE(string.contains("abc"));
}

TEST(EvoStringTests, TestSplit){
    std::string x = "aString";
    EvoString ex(x);
    std::cout << ex << std::endl;

    auto actual = ex.split("St");
    StringVector expected = {"a", "ring"};
    ASSERT_EQ(expected, actual);
}














