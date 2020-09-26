//
// Created by Ciaran Welsh on 25/09/2020.
//

#ifndef EVOGEN_CSV_H
#define EVOGEN_CSV_H

#include "evo/TypeDefs.h"
#include "NumCpp.hpp"

namespace evo {

    /**
     * @brief Read and write to csv, accounting for column and rownames
     */
    class CSV {
        bool use_index = false;
        bool use_headers = false;

        StringVector rownames_;
        StringVector colnames_;

        int nRows_;
        int nCols_;

        NdArray<double> data_;

        void parseFromString(const std::string& csv_string);

        /**
         * @brief Read all content from a file
         * @param fname the file to read from
         */
        static std::ostringstream readFromFile(const std::string& fname);

    public:
        /**
         * @brief Create a CSV parser object from a csv file on disk
         * @param filename location of csv file on disk
         */
        explicit CSV(const std::string& filename);

        /**
         * @brief Create a CSV parser object from a csv file on disk
         * @param filename location of csv file on disk
         */
        explicit CSV(const std::filesystem::path& filename);

        /**
         * @brief create a CSVParser directly from data in memory. Both header and index required.
         * @param data a NdArray<double> containing data to parse
         * @param headers a vector of strings containing headers for data
         * @param index a vector of strings containing index for data
         */
        CSV(NdArray<double> data, const StringVector& headers, const StringVector& index);


        /**
         * @brief create a CSVParser directly from data in memory. Neither index or header required
         * @param data a NdArray<double> containing data to parse
         * @param index a vector of strings containing index for data
         */
        explicit CSV(NdArray<double> data);

        /**
         * @brief write csv to a stream
         * @param use_headers write csv with header row as row 0
         * @param use_index write csv with index column as col 0
         */
        [[nodiscard]] std::ostringstream toCSV() const;


        /**
         * @brief return the rownames for this csv file
         */
        [[nodiscard]] const StringVector &rowNames() const;

        /**
         * @brief return the column names for this csv file
         */
        [[nodiscard]] const StringVector &colNames() const;

        /**
         * @brief return the number of rows in csv file
         */
        [[nodiscard]] int getNRows() const;

        /**
         * @brief return the number of cols in csv file
         */
        [[nodiscard]] int getNCols() const;

        /**
         * @brief return the data in csv file
         */
        [[nodiscard]] const NdArray<double> &getData() const;
    };


}

#endif//EVOGEN_CSV_H
