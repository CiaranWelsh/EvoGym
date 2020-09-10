//
// Created by Ciaran on 09/09/2020.
//

#include "gtest/gtest.h"

#include "evo/NetworkGenerationOptions.h"
#include "evo/RandomNetworkGenerator.h"

using namespace evo;
using namespace rr;

class RandomNetworkGeneratorTests : public ::testing::Test {
public:
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
//        rateLaws["uni-uni"] = uni_uni;
//        rateLaws["uni-bi"] = uni_bi;
    };
};


TEST_F(RandomNetworkGeneratorTests, TestRandomInt) {
    NetworkGenerationOptions options(rateLaws);
    RandomNetworkGenerator generator(options);
    int x = generator.getRandomInt(0, 5);
    std::cout << x << std::endl;
}

TEST_F(RandomNetworkGeneratorTests, test) {
    std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
    NetworkGenerationOptions options(rateLaws);
    std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
    RandomNetworkGenerator generator(options);
    std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
    generator.createReactions();
    std::cout <<__FILE__<<":"<<__LINE__<<std::endl;
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
