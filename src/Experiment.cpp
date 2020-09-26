//
// Created by Ciaran Welsh on 24/09/2020.
//

#include "evo/Experiment.h"
#include "evo/CSV.h"
#include "evo/evo_error.h"

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
    }

    Experiment::Experiment(VectorOfNdArrays<double> vectorOfNdArrays, StringVector rownames, StringVector colnames)
            : datasets_(std::move(vectorOfNdArrays)), rowNames_(std::move(rownames)), colNames_(std::move(colnames)) {}


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
    }

/*****************************************************************
 *  public methods
 */

    void Experiment::addExperiment(const std::string &filename) {
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
            INVALID_ARGUMENT_ERROR << "The rows in \""  << filename << "\" are not the same as the rows in this experiment";
        if (csv.colNames() != colNames_)
            INVALID_ARGUMENT_ERROR <<
                    "The columns in \"" << filename << "\" are not the same as the columns in this experiment";

        addExperiment(csv.getData());
    }


    void Experiment::addExperiment(const NdArray<double> &data) {
        if (data.shape().rows != nRows)
            INVALID_ARGUMENT_ERROR << "The number of rows in input data != number rows in your experiment";
        if (data.shape().cols != nCols)
            INVALID_ARGUMENT_ERROR << "The number of columns in input data != number columns in your experiment";

        datasets_.push_back(data);

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

    void Experiment::calculateAverage() {
        NdArray<double> averages = nc::zeros<double>(nc::Shape(nRows, nCols));

        // we'll keep track of how many numbers we add up
        // so that we can account for missing data
        NdArray<double> counts = nc::zeros<double>(nc::Shape(nRows, nCols));

        // the addition
        for (auto dataset : datasets_) {
            for (int i = 0; i < nRows; i++) {
                for (int j=0; j < nCols; j++) {
                    if (dataset(i, j) == nc::constants::nan)
                        averages(i, j) = nc::constants::nan;
                    averages(i, j) += dataset(i, j);
                    counts(i, j) += 1;
                }
            }
        }

        // the division
        for (auto dataset : datasets_) {
            for (int i = 0; i < nRows; i++) {
                for (int j=0; j < nCols; j++) {
                    if (dataset(i, j) == nc::constants::nan)
                        continue; // already assigned whilst adding
                    averages(i, j) = averages(i, j) / counts(i, j);
                }
            }
        }
        average_ = averages;

    }

/*****************************************************************
 *  getters and setters
 */

    ExperimentType Experiment::getDataSetType() {
        return experimentType;
    }

    StringVector Experiment::getRowNames() const {
        return rowNames_;
    }

    StringVector Experiment::getColNames() const {
        return colNames_;
    }

    void Experiment::setRowNames(const StringVector &rowNames) {
        if (rowNames.size() != nRows)
            INVALID_ARGUMENT_ERROR << "You are trying to set this Experiment objects rownames "
                                   "with an incompatible number of rows";
        rowNames_ = rowNames;
    }

    void Experiment::setColNames(const StringVector &colNames) {
        if (colNames.size() != nCols)
            INVALID_ARGUMENT_ERROR << "You are trying to set this Experiment objects colnames "
                                   "with an incompatible number of columns";
        colNames_ = colNames;

    }

    void Experiment::setErrorMatrix(const NdArray<double> &matrix) {
        if (matrix.shape().rows != nRows)
            INVALID_ARGUMENT_ERROR << "Number of rows in error matrix != number of rows in Experiment object";
        if (matrix.shape().cols != nCols)
            INVALID_ARGUMENT_ERROR << "Number of columns in error matrix != number of columns in Experiment object";
        error_ = matrix;
    }

    void Experiment::setErrorMatrix(const std::string &filename) {
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

    }

    const VectorOfNdArrays<double> &Experiment::getDatasets() const {
        return datasets_;
    }

    const NdArray<double> &Experiment::getAverage() const {
        return average_;
    }

    const NdArray<double> &Experiment::getError() const {
        return error_;
    }

    ExperimentType Experiment::getExperimentType() const {
        return experimentType;
    }

    int Experiment::getNRows() const {
        return nRows;
    }

    int Experiment::getNCols() const {
        return nCols;
    }


}













