Random Network Generation
==========================

Implementation
--------------

The current implementation of RandomNetworkGenerator requires a single argument,
and thats an instance of a RandomNetworkGeneratorOptions object, which holds
all the options. These options include

    * nCompartments: The number of compartments. Initialized from contineous uniform distribution
      between "compartmentLowerBound" and "compartmentUpperBound"
    * nFloatingSpecies.
      These are initialized with a random variable draw from continueous uniform
      distribution between "floatingSpeciesLowerBound and "floatingSpeciesUpperBound".
    * nBoundarySpecies.
      These are initialized with a random variable drawn from a discrete uniform distribution between
      "boundarySpeciesLowerBound" and "boundarySpeciesUpperBound"
    * rateLaws.
      Define the rate laws that are randomly selected during network generation.
      See below for more details.
    * motifs. Not yet implemented. The idea is a placeholder for randomly selecting entire motifs or sets of reactions with a predefined structure.
    * seed. For achieving deterministic results.

The rate laws require a bit more explaination. This code provides a way of inluding
arbitrary rate laws in the random network generator. This is handled by specifying rate laws
using placeholders (such as km or S or E) which will be replaced by actual model components
during the network generation.

.. code-block:: C++
    :linenos:

    #include "evo/RateLaw.h"

    int main(){
                        
    }












