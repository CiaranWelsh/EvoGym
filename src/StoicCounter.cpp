//
// Created by Ciaran Welsh on 21/09/2020.
//

#include "evo/StoicCounter.h"
#include <algorithm>
#include <utility>

namespace evo {


    StoicCounter::StoicCounter(std::vector<ls::Matrix<double>> vec){
        for (auto &it: vec){
            const std::vector<std::vector<double>>& v2 = it.getValues();
            vector_of_matrices_.push_back(v2);
        }
          set_of_matrices_ = convertToSet();
    }

    // Function to convert Vector to Set
    std::set<std::vector<std::vector<double>>> StoicCounter::convertToSet(){
        return std::set(vector_of_matrices_.begin(), vector_of_matrices_.end());
    }
    std::vector<int> StoicCounter::count() {
        std::vector<int> counts_(set_of_matrices_.size());
        auto setIt = set_of_matrices_.begin();
        for (int i=0; i < set_of_matrices_.size(); i++){
            counts_[i] = std::count(vector_of_matrices_.begin(), vector_of_matrices_.end(), *setIt);
            std::advance(setIt, 1);
        }
        return counts_;
    }
    const std::vector<std::vector<std::vector<double>>> &StoicCounter::getVectorOfMatrices() const {
        return vector_of_matrices_;
    }
    const std::set<std::vector<std::vector<double>>> &StoicCounter::getSetOfMatrices() const {
        return set_of_matrices_;
    }

}// namespace evo
