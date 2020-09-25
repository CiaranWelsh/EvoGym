//
// Created by Ciaran Welsh on 24/09/2020.
//

#ifndef EVOGYM_EXPERIMENT_H
#define EVOGYM_EXPERIMENT_H

#include "evo/TypeDefs.h"
#include "evo/evogym_export.h"
#include <iostream>

namespace evo {

    enum DataSetType {
        EVO_TIMESERIES_DATASET,
        EVO_PERTURBATION_DATASET,
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
        NdArray<double> average_;
        NdArray<double> error_;
        DataSetType dataSetType;
        StringVector rowNames_;
        StringVector colNames_;
        RoleMap roles_;



        /**
         * @brief returns EVO_TIMESERIES_DATASET
         * if the data in `datasets_` looks like a timeseries
         * or EVO_PERTURBATION_DATASET otherwise.
         * @details This variable is used to indicate which
         * type of data is held by the dataset. This is needed because
         * timeseries data needs to be handled differently to
         * perturbation data.
         */
        virtual DataSetType getDataSetType() = 0;

        /**
         * @brief calculate the average of datasets_ and populates
         * the average_ field.
         */
        void calculateAverage();

        /**
         * @brief calculate the stdev of datasets_ and populates
         * the error_ field.
         */
        void calculateStdev();

        /**
         * @brief ensure user input makes sense
         * @details Make sure
         */
        void validateUserInput();

    public:
        /**
         * @brief construct a DataSet by reading in a properly formatted csv file
         */
        Experiment(std::string filepath);

        /**
         * @brief construct a DataSet directly from a NdArray<double> object
         */
        Experiment(NdArray<double> ndArray);

        /**
          * @brief construct a DataSet from a vector of NdArray objects
          */
        Experiment(VectorOfNdArrays<double> vectorOfNdArrays);

        /**
          * @brief override the default error matrix using an
          * NdArray<double>.
          * @details This error matrix defaults to the standard deviation
          * when >1 matrices given or 1 otherwise. The error matrix is
          * used to normalize any objective function by experimental error.
          */
        void setErrorMatrix(NdArray<double> matrix);

        /**
         * @brief override the default error matrix using an
         * from a matrix in file
         * @details This error matrix defaults to the standard deviation
         * when >1 matrices given or 1 otherwise. The error matrix is
         * used to normalize any objective function by experimental error.
         */
        void setErrorMatrix(std::string filename);

        /**
         * @brief getter for the rowNames attribute
         */
        StringVector getRowNames() const;

        /**
         * @brief getter for the rowNames attribute
         */
        StringVector getColNames() const;

        /**
         * @brief setter for the rowNames attribute
         */
        void setRowNames(StringVector rowNames) const;

        /**
         * @brief getter for the rowNames attribute
         */
        void setColNames(StringVector colNames) const;
    };

}// namespace evo
#endif//EVOGYM_EXPERIMENT_H
