//
// Created by Ciaran Welsh on 25/09/2020.
//

#include "include/evo/EvoString.h"

#include <iostream>
#include <algorithm>

#include <utility>
#include "evo/evo_error.h"

namespace evo {
    EvoString::EvoString(std::string  string)
        : string_(std::move(string)) {}

    StringVector EvoString::split(const std::string& by) {
        StringVector tokens;

        // first try and find by in string_
        if (!contains(by))
            INVALID_ARGUMENT_ERROR << "There are no substrings \""
                << by << "\" in \"" << string_ << "\"";

        size_t prev = 0, pos = 0;
        do
        {
            pos = string_.find(by, prev);
            if (pos == std::string::npos) pos = string_.length();
            std::string token = string_.substr(prev, pos-prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + by.length();
        }
        while (pos < string_.length() && prev < string_.length());
        return tokens;

    }

    std::ostream &operator<<(std::ostream &os, EvoString &string) {
        os << string.string_;
        return os;
    }
    std::string::iterator EvoString::begin() {
        return string_.begin();
    }
    std::string::iterator EvoString::end() {
        return string_.end();
    }

    bool EvoString::contains(const std::string& other) {
        return string_.find(other) != std::string::npos;
    }

    std::string EvoString::string() const{
        return string_;
    }

    bool EvoString::contains(const EvoString& other) {
        return string_.find(other.string()) != std::string::npos;
    }
    void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
    {
        // Get the first occurrence
        size_t pos = data.find(toSearch);
        // Repeat till end is reached
        while( pos != std::string::npos)
        {
            // Replace this occurrence of Sub String
            data.replace(pos, toSearch.size(), replaceStr);
            // Get the next occurrence from the current position
            pos =data.find(toSearch, pos + replaceStr.size());
        }
    }
    EvoString EvoString::replace(const std::string& what, const std::string& with) {
        std::string string = string_; // make copy so we don't mutate inplcae
        // Get the first occurrence
        size_t pos = string.find(what);
        // Repeat till end is reached
        while( pos != std::string::npos)
        {
            // Replace this occurrence of Sub String
            string.replace(pos, what.size(), with);
            // Get the next occurrence from the current position
            pos = string.find(what, pos + with.size());
        }
        return EvoString(string);
    }


}
