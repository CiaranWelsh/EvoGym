//
// Created by Ciaran Welsh on 21/09/2020.
//

#ifndef EVOGYM_STOICCOUNTER_H
#define EVOGYM_STOICCOUNTER_H

#include "rr/rrRoadRunner.h"

namespace evo {

    template<typename T>
    using SetOfMatrices = std::set<std::vector<std::vector<T>>>;

    template<typename T>
    using VectorOfMatrices = std::vector<std::vector<std::vector<T>>>;


    template<typename T>
    using Vector2D = std::vector<std::vector<T>>;


    template<class T>
    class StoicCounter {
        VectorOfMatrices<T> vector_of_matrices_;
        SetOfMatrices<T> set_of_matrices_;
        std::vector<int> counts_ = count();

    public:
        explicit StoicCounter(VectorOfMatrices<T> vec)
            : vector_of_matrices_(vec) {
            set_of_matrices_ = convertToSet();
        }
        const SetOfMatrices<T> &getSetOfMatrices() const {
            return set_of_matrices_;
        }

        SetOfMatrices<T> convertToSet() {
            return std::set(vector_of_matrices_.begin(), vector_of_matrices_.end());
        };

        [[nodiscard]] const VectorOfMatrices<T> &getVectorOfMatrices() const {
            return vector_of_matrices_;
        }

        [[nodiscard]] std::vector<int> count() const {
            std::vector<int> counts(set_of_matrices_.size());
            auto setIt = set_of_matrices_.begin();
            for (int i = 0; i < set_of_matrices_.size(); i++) {
                counts[i] = std::count(vector_of_matrices_.begin(), vector_of_matrices_.end(), *setIt);
                std::advance(setIt, 1);
            }
            return counts;
        };
        friend std::ostream &operator<<(std::ostream &os, const StoicCounter<T> &stoicCounter);

    };

    std::ostream &operator<<(std::ostream &os, const StoicCounter<double> &stoicCounter) {
        const std::vector<int> &count = stoicCounter.count();
        os << "{" << std::endl;
        for (int i = 0; i < count.size() - 1; i++) {
            os <<"\t" << i << ": " << count[i] << ",\n";
        }
        os << "\t"<< count.size() - 1 << ": " << count[count.size() - 1] << std::endl;
        os << "}" << std::endl;

        os << std::endl;
        auto stoic_matrix = stoicCounter.getSetOfMatrices().begin();
        for (int i = 0; i < stoicCounter.getSetOfMatrices().size(); i++){
            os << "Stoiciometry matrix "<< i << std::endl;
            os << "{" << std::endl;
            Vector2D<double> v = *stoic_matrix;
            ls::Matrix<double> m(v);
            os << m;
            os << "}\n" << std::endl;
            std::advance(stoic_matrix, 1);
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const StoicCounter<int> &stoicCounter) {
        const std::vector<int> &count = stoicCounter.count();
        os << "{" << std::endl;
        for (int i = 0; i < count.size() - 1; i++) {
            os <<"\t" << i << ": " << count[i] << ",\n";
        }
        os << "\t"<< count.size() - 1 << ": " << count[count.size() - 1] << std::endl;
        os << "}" << std::endl;

        os << std::endl;
//        auto stoic_matrix = stoicCounter.getSetOfMatrices().begin();
//        for (int i = 0; i < stoicCounter.getSetOfMatrices().size(); i++){
//            os << "Stoiciometry matrix "<< i << std::endl;
////            os << "{" << std::endl;
////            for (int j=0; j< stoic_matrix->size(); j++){
////                for (int k=0; k<(*stoic_matrix)[j].size(); j++){
////                    os << "\t" << (*stoic_matrix)[j][k] << ", ";
////                }
////                os << std::endl;
////            }
////            os << "}" << std::endl;
//            std::advance(stoic_matrix, 1);
//        }
        return os;
    }
}// namespace evo


#endif//EVOGYM_STOICCOUNTER_H
