//
// Created by Ciaran Welsh on 25/09/2020.
//

#include "include/evo/CSVParser.h"
#include "evo/evo_error.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace evo {

    CSVParser::CSVParser(const std::filesystem::path &filename, bool use_headers, bool use_index) {
        std::string content = readFromFile(filename.string()).str();


    }

    std::ostringstream CSVParser::readFromFile(const std::string& fname) {
        if (!std::filesystem::exists(fname)) {
            INVALID_ARGUMENT_ERROR("The file \"" + fname + "\" does not exist.");
        }
        std::ifstream f(fname);
        std::string csv_content;
        std::ostringstream os;
        while (getline(f, csv_content)) {
            os << csv_content << std::endl;
        }
        f.close();
        return std::ostringstream();
    }
}// namespace evo