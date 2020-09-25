//
// Created by Ciaran Welsh on 23/09/2020.
//
#include "DataFrame/DataFrame.h"
#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/logger.h"
#include "rr/rrRoadRunner.h"

int main() {
    std::cout << "\nTesting load_data ..." << std::endl;

    hmdf::StdDataFrame<std::string> df;
    std::vector<int> &col0 =
            df.create_column<int>(static_cast<const char *>("col_name"));

    std::vector<int> intvec = {1, 2, 3, 4, 5};
    std::vector<double> dblvec = {1.2345, 2.2345, 3.2345, 4.2345, 5.2345};
    std::vector<double> dblvec2 = {0.998, 0.3456, 0.056, 0.15678, 0.00345, 0.923, 0.06743, 0.1};
    std::vector<std::string> strvec = {"Col_name", "Col_name", "Col_name", "Col_name", "Col_name"};
    std::vector<std::string> ulgvec = {"S1", "S2", "s3", "s4", "s5", "s6", "s7", "s8"};
    const size_t total_count = ulgvec.size() + intvec.size() + dblvec.size() + dblvec2.size() + strvec.size() + 9;// NaN inserterd

    hmdf::StdDataFrame<std::string>::size_type rc =
            df.load_data(std::move(ulgvec),
                         std::make_pair("int_col", intvec),
                         std::make_pair("dbl_col", dblvec),
                         std::make_pair("dbl_col_2", dblvec2),
                         std::make_pair("str_col", strvec)
                         );

    assert(rc == 40);

    //    hmdf::StdDataFrame<std::string> df = hmdf::StdDataFrame<std::string>::
    //    rr::RoadRunner rr;
    //    rr.addCompartment("C1", 1.0);
    //    rr.addSpecies("S1", "C1", 10.0);
    //    rr.addSpecies("S2", "C1", 10.0);
    //    rr.addSpecies("S3", "C1", 0.0);
    //    rr.addParameter("k1", 0.1);
    //    rr.addParameter("k2", 0.1);
    //    rr.addReaction("R1", {"S1", "S2"}, {"S3"}, "k1*S1*S2");
    //    rr.addReaction("R2", {"S3"}, {"S1", "S2"}, "k2*S3");
    //
    //    std::cout << rr.getSBML() << std::endl;
}