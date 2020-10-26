//
// Created by Ciaran Welsh on 25/09/2020.
//

#ifndef EVOGEN_EVOSTRING_H
#define EVOGEN_EVOSTRING_H

#include "TypeDefs.h"
#include <string>


namespace evo {
    /**
     * @brief wrapper around std::string which includes some more comprehensive functionality
     */
    class EvoString {
        std::string string_;


    public:

        /**
         * @brief construct a EvoString from a regular std::string @param string
         */
        explicit EvoString(std::string string);

        /**
         * @brief support for "put to" operator
         * @details just a wrapper around std::string operator<<
         */
        friend std::ostream &operator<<(std::ostream &os, EvoString &string);

        /**
         * @brief returns the string_ begin iterator;
         */
        std::string::iterator begin();

        /**
         * @brief returns the string_ end iterator;
         */
        std::string::iterator end();

        /**
         * @brief split the string represented by EvoString by string contained in @param by
         */
        StringVector split(const std::string &by);

        /**
         * @brief returns the underlying string object
         */
        [[nodiscard]] std::string string() const;

        /**
         * @brief check whether this EvoString contains @param other std::string
         */
        bool contains(const std::string &other);

        /**
         * @brief check whether this EvoString contains @param other std::string
         */
        bool contains(const EvoString &other);

        EvoString replace(const std::string& what, const std::string& with);
    };


}// namespace evo

#endif//EVOGEN_EVOSTRING_H
