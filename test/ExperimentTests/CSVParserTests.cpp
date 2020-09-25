#include "evo/CSVParser.h"
#include "gtest/gtest.h"
#include <filesystem>


using namespace evo;

class CSVParserTests : public ::testing::Test {
public:
    NdArray<double> dataset1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    StringVector column_names = {"C1", "C2", "C3"};
    StringVector index_names = {"R1", "R2"};

    std::string data_both = "idx, C1, C2, C3\n"
                            "R1, 1.0, 2.0, 3.0\n"
                            "R2, 4.0, 5.0, 6.0\n";

    std::string data_headers = "C1, C2, C3\n"
                               "1.0, 2.0, 3.0\n"
                               "4.0, 5.0, 6.0\n";

    std::string data_neither = "1.0, 2.0, 3.0\n"
                               "4.0, 5.0, 6.0\n";


    std::filesystem::path fname_both = std::filesystem::current_path() /= "data_headers_and_index.csv";
    std::filesystem::path fname_headers_only = std::filesystem::current_path() /= "data_headers_only.csv";
    std::filesystem::path fname_neither = std::filesystem::current_path() /= "data_no_headers_or_index.csv";

    CSVParserTests() {
        std::cout << "writing to " << fname_both.string() << std::endl;
        std::ofstream fstream_both;
        fstream_both.open(fname_both.string());
        if( !fstream_both ) { // file couldn't be opened
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }
        fstream_both << data_both << std::endl;
        fstream_both.close();

        std::ofstream fstream_headers;
        fstream_headers.open(fname_headers_only.string());
        if( !fstream_headers ) { // file couldn't be opened
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }
        fstream_headers << data_headers << std::endl;
        fstream_headers.close();

        std::ofstream fstream_neither;
        fstream_neither.open(fname_neither.string());
        if( !fstream_neither ) { // file couldn't be opened
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }
        fstream_neither << data_neither << std::endl;
        fstream_neither.close();
    };

    ~CSVParserTests() override {
//        if (std::filesystem::exists(fname_both))
//            remove(fname_both.string().c_str());
//
//        if (std::filesystem::exists(fname_headers_only))
//            remove(fname_headers_only.string().c_str());
//
//        if (std::filesystem::exists(fname_neither))
//            remove(fname_neither.string().c_str());
    }
};


TEST_F(CSVParserTests, d) {
    CSVParser parser(fname_both);
}
