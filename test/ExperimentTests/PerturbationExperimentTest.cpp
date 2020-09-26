#include "NumCpp.hpp"

#include "rr/rrRoadRunner.h"
#include "gtest/gtest.h"

#include "evo/Experiment.h"
#include "evo/evo_error.h"
#include "DataFrame/DataFrame.h"
#include <filesystem>

using namespace evo;
using namespace rr;


class PerturbationExperimentTests : public ::testing::Test {

public:


    RoadRunner rr;

    double DELTA = 0.05; // perturbation amount
    double T = 30; // time of measurement

    double k1 = 0.1;
    double k2 = 0.5;
    double k3 = 0.6;

    NdArray<double> data1 = {
            {1.8, 2.9, 3.2},
            {3.4, 3, 3.4},
            {12.6, 1.95, 3.8},
    };

    NdArray<double> data2 = {
            {2.0, 3.4, 2.5},
            {3.5, 7.3, 2.5},
            {12.8, 1.9, 3.8},
    };

    NdArray<double> data3 = {
            {1.6, 2.6, 3.6},
            {3.6, 3.7, 3.9},
            {1.4, 2.59, 3.9},
    };

    std::filesystem::path csv_file = std::filesystem::current_path() /= "perturbation_matrix.csv";

};


TEST_F(PerturbationExperimentTests, t) {
//    PerturbationExperiment experiment
    INVALID_ARGUMENT_ERROR << "invalid" ;
}




/*
 *     PerturbationExperimentTests() {

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
 */