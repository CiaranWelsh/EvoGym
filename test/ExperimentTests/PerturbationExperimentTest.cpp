#include "NumCpp.hpp"

#include "gtest/gtest.h"

#include "evo/Experiment.h"
#include "evo/evo_error.h"
#include "evo/logger.h"

#include <filesystem>

using namespace evo;


class PerturbationExperimentTests : public ::testing::Test {

public:

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
    NdArray<double> data4 = {
            {1.8, 2.36, 3.56},
            {4.6, nc::constants::nan, 3.69},
            {1.74, 5.59, 3.79},
    };

    std::filesystem::path csv_file = std::filesystem::current_path() /= "perturbation_matrix.csv";

};

TEST_F(PerturbationExperimentTests, TestCountsMatrix) {
    PerturbationExperiment experiment;
    experiment.addExperiment(data1, false)
            .addExperiment(data2, false)
            .addExperiment(data3)
            .setRowNames({"A", "B", "C"})
            .setColNames({"A", "B", "C"});

    // the whole counts matrix should be 3
    ASSERT_TRUE(nc::all(experiment.getCounts() == 3)(0, 0));
}

TEST_F(PerturbationExperimentTests, TestCountsMatrixMissingData) {
    PerturbationExperiment experiment;
    experiment.addExperiment(data1, false)
            .addExperiment(data2, false)
            .addExperiment(data3, false)
            .addExperiment(data4)
            .setRowNames({"A", "B", "C"})
            .setColNames({"A", "B", "C"});

    // the whole counts matrix should be 3, as t
    std::cout << experiment << std::endl;
    ASSERT_FALSE(nc::all(experiment.getCounts() == 4)(0, 0));
    ASSERT_EQ(3 , experiment.getCounts()(1, 1));

}

TEST_F(PerturbationExperimentTests, TestThatAveragesAreCalculateCorrectly) {
    PerturbationExperiment experiment;
    experiment.addExperiment(data1, false)
        .addExperiment(data2, false)
        .addExperiment(data3)
        .setRowNames({"A", "B", "C"})
        .setColNames({"A", "B", "C"});
    std::cout << experiment << std::endl;
    double expected = (data1(0, 0) + data2(0, 0) + data3(0, 0) ) / 3;
    ASSERT_DOUBLE_EQ(expected, experiment.getAverages()(0, 0));
}

TEST_F(PerturbationExperimentTests, TestThatAveragesAreCalculateCorrectlyWithMissingData) {
    PerturbationExperiment experiment;
    experiment.addExperiment(data1, false)
        .addExperiment(data2, false)
        .addExperiment(data3, false)
        .addExperiment(data4)
        .setRowNames({"A", "B", "C"})
        .setColNames({"A", "B", "C"});

    double expected = (3.7 + 7.3 + 3) / 3;
    ASSERT_DOUBLE_EQ(expected, experiment.getAverages()(1, 1));
}

TEST_F(PerturbationExperimentTests, TestThatStdevAreCalculateCorrectly) {
    PerturbationExperiment experiment;
    experiment.addExperiment(data1, false)
        .addExperiment(data2, false)
        .addExperiment(data3, true)
        .setRowNames({"A", "B", "C"})
        .setColNames({"A", "B", "C"});
    std::cout << experiment << std::endl;
    NdArray<double> a = {1.8, 2, 1.6};
    double expected = nc::stdev(a)(0, 0);
    ASSERT_DOUBLE_EQ(expected, experiment.getErrors()(0, 0));
}

TEST_F(PerturbationExperimentTests, TestThatStdevAreCalculateCorrectlyWithMissingData) {
    PerturbationExperiment experiment;
    experiment.addExperiment(data1, false)
        .addExperiment(data2, false)
        .addExperiment(data3, false)
        .addExperiment(data4)
        .setRowNames({"A", "B", "C"})
        .setColNames({"A", "B", "C"});
    NdArray<double> a = {3.7, 7.3,  3.0};
    double expected = nc::stdev(a)(0, 0);
    ASSERT_DOUBLE_EQ(expected, experiment.getErrors()(1, 1));
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