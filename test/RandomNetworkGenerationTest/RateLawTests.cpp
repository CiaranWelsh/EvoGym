
#include "gtest/gtest.h"

#include "evo/EvoRateLaw.h"
#include "evo/RoleTypes.h"
#include "rr/rrRoadRunner.h"
using namespace evo;

class EvoRateLawTests : public ::testing::Test {
public:

    EvoRateLawTests() {

    }
};


TEST_F(EvoRateLawTests, TestUnpackRateLawRecursion1) {
    RoleMap roles = {
            {"k",  EVO_PARAMETER},
            {"S1", EVO_SUBSTRATE},
    };
    EvoRateLaw rateLaw("uni-uni", "k*S1", roles);
    const std::set<std::string>& actual = rateLaw.getRateLawElements();
    std::set<std::string> expected = {"k", "S1"};
    ASSERT_EQ(expected, actual);
}


TEST_F(EvoRateLawTests, TestUnpackRateLawRecursion2) {
    RoleMap roles = {
            {"k",  EVO_PARAMETER},
            {"S1", EVO_SUBSTRATE},
            {"S2", EVO_SUBSTRATE},
    };
    EvoRateLaw rateLaw("bi-uni", "k*S1*S2", roles);
    const std::set<std::string> &actual = rateLaw.getRateLawElements();
    std::set<std::string> expected = {"k", "S1", "S2"};
    ASSERT_EQ(expected, actual);
}


TEST_F(EvoRateLawTests, TestUnpackRateLawRecursion3) {
    RoleMap roles = {
            {"vmax", EVO_PARAMETER},
            {"km",   EVO_PARAMETER},
            {"S",    EVO_SUBSTRATE},
    };
    EvoRateLaw rateLaw("mm", "vmax*S / (km+S)", roles);
    const std::set<std::string> &actual = rateLaw.getRateLawElements();
    std::set<std::string> expected = {"vmax", "S", "km", "S"};
    ASSERT_EQ(expected, actual);
}


TEST_F(EvoRateLawTests, TestUnpackRateLawRecursion4) {
    RoleMap roles = {
            {"kcat", EVO_PARAMETER},
            {"km",   EVO_PARAMETER},
            {"S",    EVO_SUBSTRATE},
            {"E",    EVO_MODIFIER},
    };
    EvoRateLaw rateLaw("mm-with-kcat", "kcat*E*S / (km+S)", roles);
    const std::set<std::string> &actual = rateLaw.getRateLawElements();
    std::set<std::string> expected = {"kcat", "E", "S", "km", "S"};
    ASSERT_EQ(expected, actual);
}

TEST_F(EvoRateLawTests, TestUnpackRateLawRecursion5) {
    RoleMap roles = {
            {"kcat", EVO_PARAMETER},
            {"km",   EVO_PARAMETER},
            {"h",    EVO_PARAMETER},
            {"S",    EVO_SUBSTRATE},
            {"E",    EVO_MODIFIER},
    };
    EvoRateLaw rateLaw("hill-with-kcat", "kcat*E*S^h / (km+S^h)", roles);
    const std::set<std::string> &actual = rateLaw.getRateLawElements();
    std::set<std::string> expected = {"kcat", "E", "S", "h", "km", "S", "h"};
    ASSERT_EQ(expected, actual);
}

TEST_F(EvoRateLawTests, TestUnpackRateLawRecursion6) {
    RoleMap roles = {
            {"vfmax", EVO_PARAMETER},
            {"vbmax", EVO_PARAMETER},
            {"km1",   EVO_PARAMETER},
            {"km2",   EVO_PARAMETER},
            {"S",     EVO_SUBSTRATE},
            {"P",     EVO_PRODUCT},
    };
    EvoRateLaw rateLaw("hill-with-kcat", "((vfmax*S / km1) - (vbmax*P/km2)) / (1 + (S / km1) + (P/km1))", roles);
    const std::set<std::string> &actual = rateLaw.getRateLawElements();
    std::set<std::string> expected = {"vfmax", "vbmax", "km1", "km2", "S", "P"};
    ASSERT_EQ(expected, actual);
}

TEST_F(EvoRateLawTests, TestUnpackRateLawRecursion7) {
    RoleMap roles = {
            {"k", EVO_PARAMETER},
            {"x", EVO_SUBSTRATE},
            {"y", EVO_SUBSTRATE},
    };
    EvoRateLaw rateLaw("sine(x)", "k*sin(x)/y", roles);
    const std::set<std::string> &actual = rateLaw.getRateLawElements();
    std::set<std::string> expected = {"k", "x", "y"};
    ASSERT_EQ(expected, actual);
}



















