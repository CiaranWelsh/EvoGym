//
// Created by Ciaran Welsh on 24/09/2020.
//

#ifndef EVOGYM_TYPEDEFS_H
#define EVOGYM_TYPEDEFS_H

#include <vector>
#include <set>
#include <unordered_map>
#include "evo/evogym_export.h"
#include "NumCpp.hpp"

#include "rr/rrRoadRunner.h"

namespace evo {
/*******************************************************************
 *  NumCpp typedefs
 */
    template <class T>
    using SetOfNdArrays = std::set<nc::NdArray<T>>;

    template <class T>
    using NdArray = nc::NdArray<T>;

    template <class T>
    using VectorOfNdArrays = std::vector<nc::NdArray<T>>;

/**************************************************************
 *  ptr types
 */

    using RoadRunnerPtr = std::unique_ptr<rr::RoadRunner>;
    using RoadRunnerSharedPtr = std::shared_ptr<rr::RoadRunner>;

/**************************************************************
 *  vector types
 */

    template<typename T>
    using Vector2D = std::vector<std::vector<T>>;
    using StringVector = std::vector<std::string>;
    using IntVector = std::vector<int>;
    using DoubleVector = std::vector<double>;

    /**
     * @brief A vector of unique pointers to RoadRunner models
     */
    using RoadRunnerPtrVector = std::vector<RoadRunnerPtr>;



    /**
     * @brief a vector of vectors containing unique pointers to RoadRunner models
     */
    using NestedRoadRunnerPtrVector = std::vector<RoadRunnerPtrVector>;


    /**
     * @brief a triple nested set of type T.
     * @details this is deprecated in favour of SetOfNdArrays
     */
    template<typename T>
    using VectorOfMatrices = std::vector<std::vector<std::vector<T>>>;

/**************************************************************
 *  set types
 */
    /**
     * @brief a triple nested vector of type T.
     * @details this is deprecated in favour of VectorOfNdArrays
     */
    template<typename T>
    using SetOfMatrices = std::set<std::vector<std::vector<T>>>;


/**************************************************************
 *  map types
 */
    using StringMap = std::unordered_map<std::string, std::string>;

}

#endif//EVOGYM_TYPEDEFS_H
