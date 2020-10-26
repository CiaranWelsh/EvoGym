# Note, this is not yet built, but this is what I want the end product to look like.

# classes
from evogen import Population, Individual, ExperimentSet, ExperimentSet

# modules
from evogen import selection, crossover, mutation, objective_func, callback, observer, optimization, initialization

"""
Experimental Data
==================
Prior to evolution, thought needs to be put into how to handle experimental data. 

Experiment.from_file is a static method which parses data from file and into an Experiment object.
Perturbation experimental data should be laid out like so

     S1   S2   S3 
S1   1    2     3
S2   4    5     6
S3   7    8     9
     
S1   1    2     3
S2   4    5     -
S3   7    8     9 
    
S1   1    2     3
S2   4    -     6
S3   7    8     9

Where each matrix are experimental repeats. Missing data is handled automatically. 
Steady state data should be laid out like:

S1   S2   S3    inhib
1    -     3      0
4    5     6      1

where each row is an experimental repeat and the inhib column in an independent variable. In this case
the model species "inhib" is set to 0 for the first evaluation of the objective function and 1 
for the second. The two results are added together. Unless I am mistaken, independent variables 
are not required for perturbation data. Independent variables are optional - if you only have 1 experimental 
condition, they can be ignored. 

And timeseries data 

time    S1  S2  S3  inhib
0       1   2   3    0                   
5       1   2   3    0
10      1   -   3    0
15      1   2   3    0
20      1   2   3    0    

0       1   2   -    0                   
5       1   2   3    0
10      1   2   3    0
15      1   2   3    0
20      1   2   3    0    

0       1   2   3    0                   
5       1   2   3    0
10      -   2   3    0
15      1   2   3    0
20      1   2   3    0    

0       1   2   3    1                   
5       1   2   3    1
10      1   -   3    1
15      1   2   3    1
20      1   2   3    1    

0       1   2   -    1                   
5       1   2   3    1
10      1   2   3    1
15      1   2   3    1
20      1   2   3    1    

0       1   2   3    1                   
5       1   2   3    1
10      -   2   3    1
15      1   2   3    1
20      1   2   3    1    

Averages and standard deviations are automatically calculated within the Experiment object on instantiation. 
However, if users only want to provide the averages, then providing a single matrix per experimental file
is acceptable. In this case, it is up to the user to also provide an error matrix or a matrix of 1's will be used. 
The error matrix is used to weight the objective function. 
"""

experiment_set = ExperimentSet()
experiment_set \
    .add_experiment(Experiment.from_file("path/to/pert.csv")) \
    .add_experiment(Experiment.from_file("path/to/ss.csv")) \
    .add_experiment(Experiment.from_file("path/to/ts.csv"))

"""
Internally, Experiment objects classify the experimental data they are holding into perturbation, 
steady state or time series data. This information is used during evaluation phase to 
determine which simulation experiment to perform. For now, the only objective function that is supported 
is the residual sum of squares. Later I want to experiment further with AIC(c), BIC and using the likelihood function 
directly. 
"""

"""
EvolutionaryAlgorithm
=======================
- Main user entry point which makes heavy use of the Strategy pattern for providing flexibility in algorithm operations 
- This interface is inspired by tensorflow/keras, scikit-learn, seaborn and DEAP - all of which are exceptionally well designed python packages.  
- MPI built in so end user can run this code using $ mpirun -n 6 name_of_script.py. On a laptop, n can be 
  at max the number of cores (6 or 12 hyperthreaded on mine) while on a cluster n can theoretically be anything 
  provided the resources are available. Note that when -n is just 1, so when were not using MPI, all algorithms 
  converge on just using a single core. 
"""


algorithm = EvolutionaryAlgorithm(
    population_size=100,
    number_of_generations=200,
    data=experiment_set,
    # Strategy pattern - chop and change - for all of the following
    initialization=initialization.NaiveRandomNetworkGenerator,          # not instantiated, only parameter is "population_size" which can be pulled directly from the populationsize argument
    selection=selection.KTournament(k=5),                               # Needs instantiation because users need to provide a k value.
    crossover=crossover.Blank,                                          # only a placeholder: how to do?
    mutation=[mutation.ParameterChange, mutation.TopologyChange, ...],
    parameter_optimizer=optimization.HillClimberOptimization,
    callbacks=[
        callback.CheckPoint(every=20),  # generations
        callback.Variation()            # trace the population variance
    ],
    observation=[observer.console, observer.file]
)

"""
I need to think more on the python c+ interface. I like the idea of using pybind
but I need to decide how to divvy up the workload. 

Does it make sense to have a pure python interface and expose a way of 
replacing everything with c++ code? So, it'll work in pure python and users
can easily test strategies using python only and then when they find a strategy 
they want to optimize for performance they can rewrite the modules in c++
and expose to python themselves. 

What about a pybind wrapper for roadrunner?

"""

# on Mutation
# Do we want to provide a Mutations class for storing which mutations we want to be able to occur
# and the probability of occurance, which defaults to equal weighting
# Do we want parameter optimization to be a mutation type, in which it will
#  randomly be selected from the available list of mutations with a user specified probability?
# Or do we want an additional operator "parameter_optimizer" where every model gets calibrated
#  with a regular optimization algorithm?


"""
Thinking about the parallelism, I'm wondering whether it is possible to do the compiling of new random networks
at the same as other things are happening? As far as I can tell, the JIT compilation of RoadRunner models is the 
slowest part of the algorithm. But if we already know how many random networks we'll need for each generation 
it *might be possible to generate these (i.e. compile them) *at the same time* as the other parts of the algorithm 
are running. Thus, when the algorithm catches up and needs more random networks they will already be waiting.   
"""

"""
todo look at how tensorflow have implemented their python/C++ interactions. 
They use pybind11. Looks good. 
"""



























