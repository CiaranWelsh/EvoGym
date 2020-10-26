//
// Created by Ciaran Welsh on 25/09/2020.
//

#include "include/evo/CSV.h"
#include "evo/EvoString.h"
#include "evo/evo_error.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

#include "../third_party/NumCpp/include/NumCpp/NdArray.hpp"
#include "NumCpp.hpp"
#include "evo/TypeDefs.h"
#include "evo/logger.h"

namespace evo {

    CSV::CSV(const std::filesystem::path &filename) : CSV(filename.string()){}

    CSV::CSV(const std::string &filename) : nRows_(0), nCols_(0){
        EvoString content(readFromFile(filename).str());

        parseFromString(content.string());

        if (colnames_.size() != nCols_)
            LOGIC_ERROR << "Columns size != nCols --> ";
        if (rownames_.size() != nRows_)
            LOGIC_ERROR << "Rows size != nRols --> ";
    }

    std::ostringstream CSV::readFromFile(const std::string &fname) {
        if (!std::filesystem::exists(fname)) {
            INVALID_ARGUMENT_ERROR << "The file \"" + fname + "\" does not exist.";
        }
        std::ifstream f(fname);
        if (!f)
            LOGIC_ERROR << "File stream could not be opened";

        std::string csv_content;
        std::ostringstream os;
        while (getline(f, csv_content)) {
            os << csv_content << std::endl;
        }
        f.close();
        return os;
    }

    void CSV::parseFromString(const std::string &csv_string) {
        // split string by newlines
        StringVector row_vectors = EvoString(csv_string).split("\n");
        assert(row_vectors.size() > 1);

        // get the header column, including superflous first coordinate
        colnames_ = EvoString(row_vectors[0]).split(",");

        // collect metrics about required size of NdArray and resize the previously empty data_
        nRows_ = (int) row_vectors.size() - 1;// accounting for header and index
        nCols_ = (int) colnames_.size() - 1;
        data_.resizeFast(nRows_, nCols_);

        // iterate over rows vectors
        for (int i = 0; i < row_vectors.size(); i++) {
            // convert the string row into a vector of strings
            StringVector row = EvoString(row_vectors[i]).split(",");

            // collect the item in slot 0 of string vector. This contains our index
            std::string idx = row[0];
            rownames_.push_back(idx);

            // and now remove the index from this row
            row.erase(row.begin());

            // avoiding row 0 which only contains headers
            // iterate over the string vector and build up our data_ array.
            if (i != 0) {// row 0 contains column names
                // we need index i-1 because of ignoring 0 row
                for (int j = 0; j < row.size(); j++)
                    data_(i - 1, j) = std::stod(row[j]);
            }
        }
        // now remove the (0, 0) coordinates from both columns and index
        // since it should only contain the idx label
        colnames_.erase(colnames_.begin());
        rownames_.erase(rownames_.begin());
    }

    const StringVector &CSV::rowNames() const {
        return rownames_;
    }

    const StringVector &CSV::colNames() const {
        return colnames_;
    }

    int CSV::getNRows() const {
        return nRows_;
    }

    int CSV::getNCols() const {
        return nCols_;
    }

    const nc::NdArray<double> &CSV::getData() const {
        return data_;
    }

    CSV::CSV(NdArray<double> data, const StringVector &rownames, const StringVector &colnames)
            :
            data_(std::move(data)), rownames_(rownames), colnames_(colnames),
            nRows_(rownames.size()), nCols_(colnames.size()) {}

    CSV::CSV(NdArray<double> data)
            : data_(std::move(data)), nRows_(data.shape().rows), nCols_(data.shape().cols) {
    }

    std::ostringstream CSV::toCSV() const {
        // first construct the rows.
        std::ostringstream os;
        os << "idx, ";
        for (int i = 0; i < nCols_; i++) {
            if (i == nCols_ - 1)
                os << colNames()[i] << "\n";
            else
                os << colNames()[i] << ", ";
        }
        for (int i = 0; i < nRows_; i++) {
            os << rownames_[i] << ", ";
            for (int j = 0; j < nCols_; j++) {
                if (j == nCols_-1)
                    os << data_(i, j) << "\n";
                else
                    os << data_(i, j) << ", ";
            }
        }
        return os;
    }
}// namespace evo
