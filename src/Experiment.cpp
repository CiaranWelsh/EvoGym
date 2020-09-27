//
// Created by Ciaran Welsh on 24/09/2020.
//

#include "evo/Experiment.h"
#include "evo/CSV.h"
#include "evo/evo_error.h"
#include "evo/EvoString.h"

#include <ostream>

namespace evo {

/*******************************************************************************************
 *      Constructors
 */

    Experiment::Experiment(const std::string &filepath) {
        CSV csv(filepath);
        datasets_.push_back(csv.getData());
        colNames_ = csv.colNames();
        rowNames_ = csv.rowNames();
        nRows = rowNames_.size();
        nCols = colNames_.size();
    }

    Experiment::Experiment(const NdArray<double> &ndArray, StringVector rownames, StringVector colnames)
            : datasets_(VectorOfNdArrays<double>()), rowNames_(std::move(rownames)), colNames_(std::move(colnames)) {
        datasets_.push_back(ndArray);
        recalculate();
    }

    Experiment::Experiment(VectorOfNdArrays<double> vectorOfNdArrays, StringVector rownames, StringVector colnames)
            : datasets_(std::move(vectorOfNdArrays)), rowNames_(std::move(rownames)), colNames_(std::move(colnames)) {
        recalculate();
    }


    Experiment::Experiment(const StringVector &filepaths) {
        for (int i = 0; i < filepaths.size(); i++) {
            const std::string &fname = filepaths[i];
            if (i == 0) {
                // we do the first one manually, (instead of using addExperiment
                // so we can collect the required information from CSV
                CSV csv(fname);
                rowNames_ = csv.rowNames();
                colNames_ = csv.colNames();
                nRows = csv.getNRows();
                nCols = csv.getNCols();
            } else {
                // now we just use addExperiment for the rest
                addExperiment(fname);
            }
        }
        recalculate();
    }

/*****************************************************************
 *  public methods
 */

    Experiment &Experiment::addExperiment(const std::string &filename) {
        if (!std::filesystem::exists(filename))
            FILE_NOT_FOUND_ERROR << filename;

        CSV csv(filename);

        if (csv.getNCols() != nCols)
            INVALID_ARGUMENT_ERROR << "The number of columns in file \""
                                   << filename
                                   << "\" is not equal to the number of columns in this Experiment object";
        if (csv.getNRows() != nRows)
            INVALID_ARGUMENT_ERROR << "The number of rows in file \""
                                   << filename
                                   << "\" is not equal to the number of rows in this Experiment object";
        if (csv.rowNames() != rowNames_)
            INVALID_ARGUMENT_ERROR << "The rows in \"" << filename
                                   << "\" are not the same as the rows in this experiment";
        if (csv.colNames() != colNames_)
            INVALID_ARGUMENT_ERROR <<
                                   "The columns in \"" << filename
                                   << "\" are not the same as the columns in this experiment";

        addExperiment(csv.getData());
        recalculate();
        return *this;
    }


    Experiment &Experiment::addExperiment(const NdArray<double> &data, bool recalculate_) {
        if (datasets_.empty())
            setNRows(data.shape().rows).setNCols(data.shape().cols);
        if (data.shape().rows != nRows)
            INVALID_ARGUMENT_ERROR << "The number of rows in input data != number rows in your experiment";
        if (data.shape().cols != nCols)
            INVALID_ARGUMENT_ERROR << "The number of columns in input data != number columns in your experiment";

        datasets_.push_back(data);
        if (recalculate_)
            recalculate();
        return *this;
    }

    bool Experiment::isSimilar(const Experiment &rhs) {
        return rowNames_ == rhs.rowNames_ && colNames_ == rhs.colNames_;
    }

    Experiment &Experiment::operator+=(Experiment &rhs) {
        if (!isSimilar(rhs))
            INVALID_ARGUMENT_ERROR << "rhs Experiment cannot be concatonated "
                                      "with the current experiment object because "
                                      "they are not similar Experiment objects "
                                      "(same rows and columns)";
        for (auto &data: rhs.getDatasets())
            datasets_.push_back(data);
        return *this;
    }

    int Experiment::size() {
        return datasets_.size();
    }

    void Experiment::recalculate() {
        calculateCounts();
        calculateAverages();
        calculateStdev();
    }


/*****************************************************************
 *  private methods
 */

    void Experiment::calculateCounts() {
        NdArray<int> counts = nc::zeros<int>(nc::Shape(nRows, nCols));

        for (auto dataset : datasets_) {
            for (int i = 0; i < nRows; i++) {
                for (int j = 0; j < nCols; j++) {
                    if (nc::isnan(dataset(i, j)))
                        continue;
                    else
                        counts(i, j) += 1;
                }
            }
        }
        // accounting for missing data
        // any value that is still 0 should be nan.
        for (auto dataset : datasets_) {
            for (int i = 0; i < nRows; i++) {
                for (int j = 0; j < nCols; j++) {
                    if (dataset(i, j) == 0)
                        counts(i, j) = nc::constants::nan;
                }
            }
        }
        counts_ = counts;
    }

    void Experiment::calculateAverages() {
        NdArray<double> averages = nc::zeros<double>(nc::Shape(nRows, nCols));

        // the addition
        for (auto dataset : datasets_) {
            for (int i = 0; i < nRows; i++) {
                for (int j = 0; j < nCols; j++) {
                    if (nc::isnan(dataset(i, j)))
                        continue;
                    else
                        averages(i, j) += dataset(i, j);
                }
            }
        }

        // the division
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                if (nc::isnan(averages(i, j)))
                    continue; // already assigned whilst adding
                averages(i, j) = (averages(i, j) / double(counts_(i, j)));
            }
        }

        // accounting for missing data
        // any value that is still 0 should be nan.
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                if (averages(i, j) == 0.0)
                    averages(i, j) = nc::constants::nan;
            }
        }
        average_ = averages;
    }

    void Experiment::calculateStdev() {

        /*
         * root (1/N * ((X - average) ** 2)))
         */
        NdArray<double> stdev = nc::zeros<double>(nc::Shape(nRows, nCols));

        // sum of deviation from average squared
        for (auto dataset : datasets_) {
            for (int i = 0; i < nRows; i++) {
                for (int j = 0; j < nCols; j++) {
                    if (nc::isnan(dataset(i, j)))
                        continue;
                    stdev(i, j) += nc::power<double>(dataset(i, j) - average_(i, j), 2);
                }
            }
        }

        std::cout << stdev << std::endl;

        // square root of Xij divided by N
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                if (stdev(i, j) == 0)
                    stdev(i, j) = 0;
                stdev(i, j) = nc::sqrt(stdev(i, j) / counts_(i, j));
            }

        }
        error_ = stdev;
    }

/*****************************************************************
 *  getters and setters
 */

    StringVector Experiment::getRowNames() const {
        return rowNames_;
    }

    StringVector Experiment::getColNames() const {
        return colNames_;
    }

    Experiment &Experiment::setRowNames(const StringVector &rowNames) {
        if (rowNames.size() != nRows)
            INVALID_ARGUMENT_ERROR << "You are trying to set this Experiment objects rownames "
                                      "with an incompatible number of rows";
        rowNames_ = rowNames;
        return *this;
    }

    Experiment &Experiment::setColNames(const StringVector &colNames) {
        if (colNames.size() != nCols)
            INVALID_ARGUMENT_ERROR << "You are trying to set this Experiment objects colnames "
                                      "with an incompatible number of columns";
        colNames_ = colNames;
        return *this;

    }

    Experiment &Experiment::setErrorMatrix(const NdArray<double> &matrix) {
        if (matrix.shape().rows != nRows)
            INVALID_ARGUMENT_ERROR << "Number of rows in error matrix != number of rows in Experiment object";
        if (matrix.shape().cols != nCols)
            INVALID_ARGUMENT_ERROR << "Number of columns in error matrix != number of columns in Experiment object";
        error_ = matrix;
        return *this;
    }

    Experiment &Experiment::setErrorMatrix(const std::string &filename) {
        if (!std::filesystem::exists(filename))
            FILE_NOT_FOUND_ERROR << filename;
        CSV csv(filename);
        if (csv.getData().shape().rows != nRows)
            INVALID_ARGUMENT_ERROR << "Number of rows in error matrix != number of rows in Experiment objec";
        if (csv.getData().shape().cols != nCols)
            INVALID_ARGUMENT_ERROR << "Number of columns in error matrix != number of columns in Experiment objec";
        if (csv.rowNames() != rowNames_)
            INVALID_ARGUMENT_ERROR << "Rownames in error matrix != rownames in Experiment object";
        if (csv.colNames() != colNames_)
            INVALID_ARGUMENT_ERROR << "Colnames in error matrix != colnames in Experiment object";

        error_ = csv.getData();
        return *this;
    }

    const VectorOfNdArrays<double> &Experiment::getDatasets() const {
        return datasets_;
    }

    const NdArray<double> &Experiment::getAverages() const {
        return average_;
    }

    const NdArray<double> &Experiment::getErrors() const {
        return error_;
    }

    int Experiment::getNRows() const {
        return nRows;
    }

    int Experiment::getNCols() const {
        return nCols;
    }

    const NdArray<int> &Experiment::getCounts() const {
        return counts_;
    }

    Experiment &Experiment::setNRows(int nRows_) {
        Experiment::nRows = nRows_;
        return *this;
    }

    Experiment &Experiment::setNCols(int nCols_) {
        Experiment::nCols = nCols_;
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, Experiment &experiment) {
        os << "Rownames:" << std::endl;
        for (auto &it: experiment.getRowNames())
            os << "\t" << it << ", ";
        os << std::endl;

        os << "Colnames:" << std::endl;
        for (auto &it: experiment.getColNames())
            os << "\t" << it << ", ";
        os << std::endl;

        os << "Data: " << std::endl;
        for (auto &it: experiment.getDatasets()) {
            std::string data_string = it.str();
            data_string = EvoString(data_string).replace("\n", "\n\t").string();
            os << "\t" << data_string << std::endl;
        }
        os << "Averages: " << std::endl;
        std::string averages = EvoString(experiment.getAverages().str()).replace("\n", "\n\t").string();
        os << "\t" << averages << std::endl;

        os << "Errors: " << std::endl;
        std::string errors = EvoString(experiment.getErrors().str()).replace("\n", "\n\t").string();
        os << "\t" << errors << std::endl;

        os << "Counts: " << std::endl;
        std::string counts = EvoString(experiment.getCounts().str()).replace("\n", "\n\t").string();
        os << "\t" << counts << std::endl;

        return os;
    }

/************************************************************************
 * PerturbationExperiment
 */

    ExperimentType PerturbationExperiment::experimentType() const {
        return EVO_TIMESERIES_EXPERIMENT;
    }

}













