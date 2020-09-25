//
// Created by Ciaran Welsh on 25/09/2020.
//

#ifndef EVOGEN_CSVPARSER_H
#define EVOGEN_CSVPARSER_H

#include "evo/TypeDefs.h"

namespace evo {

    /**
     * @brief Read and write to csv, accounting for column and rownames
     */
    class CSVParser {
        bool use_index = false;
        bool use_headers = false;

        StringVector index_;
        StringVector headers_;

        NdArray<double> data_;

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
        CSVParser(std::string filename, bool use_headers=true, bool use_index=true);

        /**
         * @brief Create a CSV parser object from a csv file on disk
         * @param filename location of csv file on disk
         */
        explicit CSVParser(const std::filesystem::path& filename, bool use_headers=true, bool use_index=true);

        /**
         * @brief create a CSVParser directly from data in memory. Both header and index required.
         * @param data a NdArray<double> containing data to parse
         * @param headers a vector of strings containing headers for data
         * @param index a vector of strings containing index for data
         */
        CSVParser(NdArray<double> data, StringVector headers, StringVector index);


        /**
         * @brief create a CSVParser directly from data in memory. Neither index or header required
         * @param data a NdArray<double> containing data to parse
         * @param index a vector of strings containing index for data
         */
        explicit CSVParser(NdArray<double> data);


        /**
         * @brief create a CSVParser directly from data in memory. Header only required
         * @param data a NdArray<double> containing data to parse
         * @param headers a vector of strings containing headers for data
         */
        CSVParser(NdArray<double> data, StringVector headers);

        /**
         * @brief write csv to a stream
         * @param use_headers write csv with header row as row 0
         * @param use_index write csv with index column as col 0
         */
        std::ostringstream toCSV(bool use_headers, bool use_index);


    };


}

#endif//EVOGEN_CSVPARSER_H
