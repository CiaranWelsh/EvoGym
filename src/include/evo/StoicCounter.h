//
// Created by Ciaran Welsh on 21/09/2020.
//

#ifndef EVOGYM_STOICCOUNTER_H
#define EVOGYM_STOICCOUNTER_H

#include "rr/rrRoadRunner.h"

namespace evo {

    class StoicCounter {
        std::vector<std::vector<std::vector<double>>> vector_of_matrices_;
        std::set<std::vector<std::vector<double>>> set_of_matrices_;

    public:
        explicit StoicCounter(std::vector<ls::Matrix<double>> vec);

        std::set<std::vector<std::vector<double>>> convertToSet();

        std::vector<int> count();
        const std::vector<std::vector<std::vector<double>>> &getVectorOfMatrices() const;
        const std::set<std::vector<std::vector<double>>> &getSetOfMatrices() const;
    };
}// namespace evo


#endif//EVOGYM_STOICCOUNTER_H
