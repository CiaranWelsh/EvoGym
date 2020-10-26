//
// Created by Ciaran Welsh on 28/09/2020.
//

#ifndef EVOGEN_OPERATOR_H
#define EVOGEN_OPERATOR_H

namespace evo {
    /**
     * @plan
     * -----
     * Still only an idea
     * - Initialization, Evaluation, selection, mutation, crossover are all operators
     * of the evolutionary algorithm and probably have some common
     * aspects to their implementation. What are they?
     * - This is an abstract base class
     * - It'd be interesting to use operator overloading
     * to simplify the generation of these algorithms.
     *  - Need to support user defined everything. So need to teach people to use the base classes.
     *
     *  - user interface might look like :
     *
     *      # configure the data, population and objective functions
     *      # configure observers and callbacks.
     *
     *
     *      # 1 observer that does everything?
     *      # or several observers?
     *      # observer could be implemented as a callback?
     *      Pass in a list or vector of strings
     *
     *      Base class Callback
     *          - set of "On" methods. This is inspired by keras callbacks.
     *           OnSelection
     *           OnEvaluation
     *           OnCrossOver
     *           OnMutation
     *           OnCalibration
     *
     *      derived types:
     *          - graph theory properties?
     *          - Stdev
     *          - fitness score?
     *          - validation score
     *          - Checkpoint - save population after so many iterations. Send SBML to master.
     *          - csv_logger
     *          - EarlyStopping criteria
     *          - Calibration
     *              - algorithm
     *              - algorithm parameters
     *
     *      Observer observer(frequency, {"stdev", "fitness score", "validation set?", "state saving?"})

     *      RateLaws rateLaws = BoxedRateLaws::massAction();
     *      RandomNetworkGeneratorOptions options(rateLaws);
     *      Population population = RandomNetworkFactory(&options, "randomnetworkgeneratorname").generate(N);
     *
     *      population.setObjectiveFunction(objectiveFunction)
     *          .addExperiment(Experiment::fromCSV(fname))
     *          .addValidation(Validation::fromCSV(fname));
     *
     *      population.addCallback();     *
     *      # do I put a traditional model calibration in here as well?
     *      for i in range(N):
     *          fitness = population.fit();
     *          population = Selection::SelectionOperator(population)
     *              .Crossover::CrossoverOperator(population)
     *              .Mutation::MutationOperator(population);
     *          population.runCallbacks();
     *
     * Or is it better to have a class hierachy for each operator?
     *
     * Does the Operator base class do the stuff related to MPI???
     *
     */
    class Operator {

    };
}

#endif //EVOGEN_OPERATOR_H
