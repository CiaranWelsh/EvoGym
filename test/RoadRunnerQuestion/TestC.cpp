//
// Created by Ciaran Welsh on 26/10/2020.
//

#include "CreateRRModelCAPI.cpp"
#include "rr/rrRoadrunner.h"

using namespace rr;

int main(){
    RoadRunner* rr_ptr = CreateRRModel_createRRModel();

    rr_ptr->setConservedMoietyAnalysis(true);

    auto m = rr_ptr->getConservationMatrix();

    std::cout << m << std::endl;

    CreateRRModel_deleteRRModel(rr_ptr);

}