//
// Created by Ciaran on 4/14/2020.
//

#ifndef EVOGYM_IDGEN_H
#define EVOGYM_IDGEN_H

#include <string>
#include <sstream>
#include <utility>
#include <iostream>

namespace evo {
    /*
     * @brief an ID generator
     */
    class IdGen {
    private:
        std::string base_;
        long start_number_;
        int num_digits_;


    public:

        /**
         */
        IdGen(std::string base, long start_number, int num_digits = 4);

        bool operator==(const IdGen &rhs) const;

        bool operator!=(const IdGen &rhs) const;

        /**
         */
        [[nodiscard]] std::string generate() const;

        /**
         */
        [[nodiscard]] std::string generate(long n) const;

        /**
         * @brief figure out the max number possible with user parameters
         * @return the maximum possible number with user parameters
         */
        [[nodiscard]] int maxNumber() const;

        /**
         * @brief count the digits in a number
         * @param n the number to count digits in
         * @return the number of digits in n
         */
        static int countDigits(long long int n);
    };
}

#endif //EVOGYM_IDGEN_H
