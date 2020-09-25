#include "NumCpp.hpp"

#include "rr/rrRoadRunner.h"
#include "gtest/gtest.h"

#include "evo/Experiment.h"

#include "DataFrame/DataFrame.h"
#include <filesystem>

using namespace evo;
using namespace rr;


class ExperimentTests : public ::testing::Test {

public:
    using DataFrame = hmdf::StdDataFrame<std::string>;
    RoadRunner rr;

    double DELTA = 0.05;
    double k1 = 0.1;
    double k2 = 0.5;
    double k3 = 0.6;

    NdArray<double> true_perturbation_matrix = NdArray<double>(3, 2);

    std::filesystem::path csv_file = std::filesystem::current_path() /= "perturbation_matrix.csv";

    ExperimentTests() {

        // configure a model
        rr.addCompartment("C1", 1.0, false);
        rr.addSpecies("S1", "C1", 10.0, false, false, "", false);
        rr.addSpecies("S2", "C1", 10.0, false, false, "", false);
        rr.addParameter("k1", k1, false);
        rr.addParameter("k2", k2, false);
        rr.addParameter("k3", k3, false);
        rr.addReaction("r1", {"S1"}, {"S2"}, "(k1+k3)*S1", false);
        rr.addReaction("r2", {"S2"}, {"S1"}, "k2*S2", true);

        // must be done before moiety conservation analysis
        StringVector parameters = rr.getGlobalParameterIds();

        // simulate to steady state
        rr.setConservedMoietyAnalysis(true);
        rr.steadyState();
        NdArray<double> ss(rr.getFloatingSpeciesConcentrationsNamedArray().getValues());

        for (auto i = 0; i < parameters.size(); i++) {
            rr.reset();
            double val = rr.getGlobalParameterByName(parameters[i]);
            rr.setGlobalParameterByName(parameters[i], val + (DELTA * val));
            rr.steadyState();
            NdArray<double> ssi_plus(rr.getFloatingSpeciesConcentrationsNamedArray().getValues());
            ssi_plus = ssi_plus / ss;

            rr.reset();
            rr.setGlobalParameterByName(parameters[i], val - (DELTA * val));
            rr.steadyState();
            NdArray<double> ssi_minus(rr.getFloatingSpeciesConcentrationsNamedArray().getValues());
            ssi_minus = ssi_minus / ss;

            NdArray<double> ssi = (ssi_plus + ssi_minus) / 2.0;
            for (int j = 0; j < ssi.size(); j++) {
                true_perturbation_matrix(i, j) = ssi(0, j);
            }
        }
        const std::vector<std::string> &selections = rr.getSteadyStateSelectionStrings();
        std::cout << true_perturbation_matrix << std::endl;



    }

};


TEST_F(ExperimentTests, t) {
    int x;
}