//
// Created by Ciaran Welsh on 26/10/2020.
//

#ifndef CREATERRMODEL_H
#define CREATERRMODEL_H

#include "rr/rrRoadRunner.h"

using namespace rr;

class CreateRRModel {
public:

    CreateRRModel() = default;

    static RoadRunner* createRRModel(){
        auto* rr = new RoadRunner();
        rr->addCompartment("C1", 1.0, false);
        rr->addSpecies("S1", "C1", 10.0, false, false, "", false);
        rr->addSpecies("S2", "C1", 10.0, false, false, "", false);
        rr->addParameter("k1", 0.1, false);
        rr->addParameter("k2", 0.2, false);
        rr->addReaction("r1", {"S1"}, {"S2"}, "k1*S1", false);
        rr->addReaction("r2", {"S2"}, {"S1"}, "k2*S2", false);
        std::cout << __FILE__ <<":"<<__LINE__ << std::endl;
        rr->regenerate(); // causes crash in Python when roadrunner 2.0.1 from pip is imported.
        std::cout << __FILE__ <<":"<<__LINE__ << std::endl;
        return rr;
    }

    static void deleteRRModel(RoadRunner* rr_ptr){
        delete rr_ptr;
    }

};


#endif //CREATERRMODEL_H
