#include "evo/EvoRateLaw.h"
#include "evo/StoicCounter.h"

#include "rr/rrRoadRunner.h"

#include "gtest/gtest.h"

using namespace evo;
using namespace rr;


TEST(StoicCounterTests, TestConvertVectorToSet) {
    Vector2D<int> matrix1({{1, 2, 3},
                                {4, 5, 6}});
    Vector2D<int> matrix2({{1, 2, 3},
                                {4, 5, 6}});

    Vector2D<int> matrix3({{7, 8, 9},
                                {10, 11, 12}});

    Vector2D<int> matrix4({{13, 14, 15},
                                {15, 17, 18}});

    VectorOfMatrices<int> v({matrix1, matrix2, matrix3, matrix4});

    StoicCounter counter(v);
    ASSERT_EQ(3, counter.getSetOfMatrices().size());

}

TEST(StoicCounterTests, TestCount) {
    Vector2D<int> matrix1({{1, 2, 3},
                           {4, 5, 6}});
    Vector2D<int> matrix2({{1, 2, 3},
                           {4, 5, 6}});

    Vector2D<int> matrix3({{7, 8, 9},
                           {10, 11, 12}});

    Vector2D<int> matrix4({{13, 14, 15},
                           {15, 17, 18}});
    VectorOfMatrices<int> v({matrix1, matrix2, matrix3, matrix4});

    StoicCounter counter(v);
    std::vector<int> counts = counter.count();
    std::vector<int> expected({2, 1, 1});
    ASSERT_EQ(expected, counts);
}




