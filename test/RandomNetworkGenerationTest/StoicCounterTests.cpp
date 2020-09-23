#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/RateLaw.h"
#include "evo/StoicCounter.h"

#include "rr/rrRoadRunner.h"

#include "gtest/gtest.h"

using namespace evo;
using namespace rr;


//TEST(StoicCounterTests, TestConvertVectorToSet) {
//    ls::Matrix<double> matrix1({{1, 2, 3},
//                                {4, 5, 6}});
//    ls::Matrix<double> matrix2({{1, 2, 3},
//                                {4, 5, 6}});
//
//    ls::Matrix<double> matrix3({{7, 8, 9},
//                                {10, 11, 12}});
//
//    ls::Matrix<double> matrix4({{13, 14, 15},
//                                {15, 17, 18}});
//
//    std::vector<ls::Matrix<double>> v({matrix1, matrix2, matrix3, matrix4});
//
//    StoicCounter counter(v);
//    ASSERT_EQ(3, counter.getSetOfMatrices().size());
//}
//
//TEST(StoicCounterTests, TestCount) {
//    ls::Matrix<double> matrix1({{1, 2, 3},
//                                {4, 5, 6}});
//    ls::Matrix<double> matrix2({{1, 2, 3},
//                                {4, 5, 6}});
//
//    ls::Matrix<double> matrix3({{7, 8, 9},
//                                {10, 11, 12}});
//
//    ls::Matrix<double> matrix4({{13, 14, 15},
//                                {15, 17, 18}});
//
//    std::vector<ls::Matrix<double>> v({matrix1, matrix2, matrix3, matrix4});
//
//    StoicCounter counter(v);
//    std::vector<int> counts = counter.count();
//    std::vector<int> expected({2, 1, 1});
//    ASSERT_EQ(expected, counts);
//}

TEST(StoicCounterTests, TestCountOnNetwork){
    RoadRunner rr;
//    RandomNetworkGeneratorOptions options(massActionRateLaws());
//    int N = 10;
//    std::vector<std::vector<std::vector<double>>> v;
//    for (int i=0; i< N ; i ++){
//        RandomNetworkGenerator generator(&options);
////        v.push_back(generator.getRR()->getFullStoichiometryMatrix().getValues());
//    }

}




