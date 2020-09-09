//
// Created by Ciaran on 07/09/2020.
//

#include "SBMLFactory.h"
#include "rr/rrRoadRunner.h"

using namespace rr;

int main(){
    std::string sbml = SBMLFactory(SIMPLE_MASS_ACTION_MODEL);
//    RoadRunner rr(sbml);
//
//    const ls::Matrix<double>* s = rr.simulate();
//    std::cout << s->Element(1, 1) << std::endl;

    RoadRunner rr;
    rr.addCompartment("comp", 1.0, true);
    rr.addSpecies("s1", "comp", 10.0, false, false, "mol", true);
    rr.addSpecies("s2", "comp", 0.0, false, false, "mol", true);
    rr.addParameter("k", 1, true);
    rr.addReaction("r1", {"s1", "s2"}, {}, "comp*k*s1*s2", true);

    SimulateOptions o;
	o.start = 0;
	o.duration = 10;
	o.steps = 101;

    const ls::Matrix<double>* result = rr.simulate(&o);

    std::ostringstream os;
    for (int i=0; i< result->numRows(); i++){
        for (int j=0; j < result->numCols(); j++){
            os << result->Element(i, j) << ", ";
        }
        os << std::endl;
    }
    std::cout << os.str() << std::endl;

}