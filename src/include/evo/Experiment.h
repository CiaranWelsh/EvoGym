//
// Created by Ciaran Welsh on 24/09/2020.
//

#ifndef EVOGYM_EXPERIMENT_H
#define EVOGYM_EXPERIMENT_H

#include "evo/TypeDefs.h"
#include "evo/evogym_export.h"
#include "evo/RoleTypes.h"
#include <iostream>

namespace evo {

    enum ExperimentType {
        EVO_TIMESERIES_EXPERIMENT,
        EVO_PERTURBATION_EXPERIMENT,
        EVO_PERTURBATION_UNKNOWN,
    };

    /**
     * plan
     * ----
     * - Need a convenient place to store experimental
     *   data
     * - Store repeats as matrices
     * - calculate average and std dev from repeats
     * - or pass in averages
     * - and std dev
     * - Read from csv file
     * - support for time series measurements
     * - how does this work with time series and multiple conditions?
     * - or use a heirachy of datasets
     *
     * @brief Parent DataSet object defining the structure of
     * datasets in EvoGym.
     * @details Both PerturbationDataSet and
     * TimeseriesDataSet implement this virtual class. Data can be read in
     * from a csv file where row and column names are defined by subtypes.
     * Generally the input is a matrix or set of matrices separated by
     * a single blank line in a csv file. Alternatively you can pass
     * in a VectorOfNdArrays as argument or even just an NdArray.
     * When multiple matrices are supplied they are averaged and standard
     * deviations are automatically calculated. When a single matrix is supplied
     * the error matrix is assumed to be 1, but can be set using
     * setErrorMatrix.
     *
     */
    class EVOGYM_EXPORT Experiment {
        VectorOfNdArrays<double> datasets_; /* dataset repeats*/
        NdArray<int> counts_;
        NdArray<double> average_;
        NdArray<double> error_;
        StringVector rowNames_;
        StringVector colNames_;
        RoleMap roles_;

    private:
        /**
         * @brief returns EVO_TIMESERIES_DATASET
         * if the data in `datasets_` looks like a timeseries
         * or EVO_PERTURBATION_DATASET otherwise.
         * @details This variable is used to indicate which
         * type of data is held by the dataset. This is needed because
         * timeseries data needs to be handled differently to
         * perturbation data.
         */
        virtual ExperimentType experimentType() const = 0;

        /**
         * @brief calculate the average of datasets_ and populates
         * the average_ field.
         */
        virtual void calculateAverages();

        /**
         * @brief calculate the stdev of datasets_ and populates
         * the error_ field.
         */
        virtual void calculateStdev();

        /**
         * @brief count the number of repeats for each data point
         */
        virtual void calculateCounts();

        /**
         * @brief ensure user input makes sense
         * @details Make sure
         */
        void validateUserInput();

    public:
        // public attributes
        int nRows = 0;
        int nCols = 0;

        /**
         * @brief default constructor for Experiment.
         * @details user must add the data and set row and column names.
         */
        Experiment() = default;

        /**
         * @brief construct a DataSet by reading in a properly formatted csv file
         */
        explicit Experiment(const std::string& filepath);

        /**
         * @brief construct a DataSet by reading in a properly vector of formatted csv file
         */
        explicit Experiment(const StringVector& filepaths);

        /**
         * @brief read data from file into Experiment object
         * @details This method is a convenience method only
         * designed so that users use Experiment::fromFile(fname)
         * which is more explicit than Experiment(fname), but equivalent
         */
         Experiment fromFile(const std::string& fname);

        /**
         * @brief construct a DataSet directly from a NdArray<double> object
         * @param ndArray a single dataset in the form of an nc::NdArray
         * @param rownames a vector of strings to use for rownames
         * @param colnames a vector of strings to use for colnames
         */
        Experiment(const NdArray<double>& ndArray, StringVector  rownames, StringVector  colnames);

        /**
          * @brief construct a DataSet from a vector of NdArray objects
          * @param ndArray a single dataset in the form of an nc::NdArray
          * @param rownames a vector of strings to use for rownames
          * @param colnames a vector of strings to use for colnames
          */
        Experiment(VectorOfNdArrays<double> vectorOfNdArrays, StringVector  rownames, StringVector  colnames);

        virtual ~Experiment() = default;

        /**
         * @brief add an experiment to the existing data contained in this
         * Experiment object
         * @param data the data to add to your experiment
         * @details data must be of the same shape as the existing data
         * @returns a referene to iteslf so calls to addExperiment can be chained.
         */
        virtual Experiment& addExperiment(const NdArray<double>& data, bool recalculate = true);

        /**
         * @brief add an experiment to the existing data contained in this
         * Experiment object
         * @param data the data to add to your experiment
         * @details data must be of the same shape as the existing data
         */
        virtual Experiment& addExperiment(const std::string& filename);

        /**
         * @brief returns the number of experiments in this Experiment object.
         */
        virtual int size();

        /**
          * @brief override the default error matrix using an
          * NdArray<double>.
          * @details This error matrix defaults to the standard deviation
          * when >1 matrices given or 1 otherwise. The error matrix is
          * used to normalize any objective function by experimental error.
          */
        virtual Experiment& setErrorMatrix(const NdArray<double>& matrix);

        /**
         * @brief override the default error matrix using an
         * from a matrix in file
         * @details This error matrix defaults to the standard deviation
         * when >1 matrices given or 1 otherwise. The error matrix is
         * used to normalize any objective function by experimental error.
         */
        Experiment& setErrorMatrix(const std::string& filename);

        /**
         * @brief getter for the rowNames attribute
         */
        [[nodiscard]] virtual StringVector getRowNames() const;

        /**
         * @brief getter for the rowNames attribute
         */
        [[nodiscard]] StringVector getColNames() const;

        /**
         * @brief setter for the rowNames attribute
         */
        Experiment& setRowNames(const StringVector& rowNames);

        /**
         * @brief getter for the rowNames attribute
         */
        Experiment& setColNames(const StringVector& colNames);

        /**
         * @brief support for += operator. This method will
         * concatenate two Experiment objects together
         * @param rhs Another Experiment object
         * @details The end result is that the two VectorOfNdArray
         * objects from the two experiments will become one.
         * If the @param rhs Experiment dimensions and data labels
         * do not conform to the current Experiment object
         * an error is thrown.
         */
        Experiment& operator+=(Experiment& rhs);

        /**
         * @brief test whether the @param rhs Experiment
         * has the same dimensions and data labels
         * as this Experiment.
         * @returns true when rownames and colnames
         * of this and rhs Experiment are equal
         */
        bool isSimilar(const Experiment& rhs);

        /**
         * @brief set the number of rows for experiment
         * @returns reference to this Experiment object
         */
        Experiment& setNRows(int nRows);

        /**
         * @brief set the number of columns for experiment
         * @returns reference to this Experiment object
         */
        Experiment& setNCols(int nCols);

        /**
         * @brief getter for the datasets in the Experiment
         * @returns a vector of NdArray<double> objects (VectorOfNdArrays<double>)
         */
        [[nodiscard]] const VectorOfNdArrays<double> &getDatasets() const;


        /**
         * @brief getter for the average matrix
         * @returns an NdArray object containing the average of datasets in this experiment
         */
        [[nodiscard]] const NdArray<double> &getAverages() const;

        /**
         * @brief getter for the error matrix
         * @returns an NdArray object containing the error of datasets in this experiment
         * @details the error matrix is used for normalizing the objective function.
         */
        [[nodiscard]] const NdArray<double> &getErrors() const;

        /**
         * @brief get the number of repeats for each data point
         */
        [[nodiscard]] const NdArray<int> &getCounts() const;

        /**
         * @brief return the number of rows in this experiment
         */
        [[nodiscard]] int getNRows() const;

        /**
         * @brief return the number of columns in this experiment
         */
        [[nodiscard]] int getNCols() const;

        /**
         * @brief recompute the average, stdev and count matrices
         */
        void recalculate();

        friend std::ostream& operator<<(std::ostream& os, Experiment& experiment);
    };


    /**
     * @brief Data structure to encase the results of a perturbation experiment
     * @details Perturbation experiments measure the system at baseline which are assumed to
     * be a steady state. Then, the amounts of system components (enzymes, signalling molecules etc)
     * are increased or decreased (perturbed) and another measurement is taken at a predefined (@param duration) time later.
     */
    class PerturbationExperiment : public Experiment {
        int duration; /*Perturbation */

        /**
         * @brief returns the EVO_PERTURBATION_EXPERIMENT enum
         */
        [[nodiscard]] ExperimentType experimentType() const override;

    public:

        using Experiment::Experiment; // forwarding constructors to superclass
    };

}// namespace evo
#endif//EVOGYM_EXPERIMENT_H
