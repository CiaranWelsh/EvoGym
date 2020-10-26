//
// Created by Ciaran Welsh on 26/10/2020.
//

#include "CreateRRModel.h"
#include "rr/rrRoadrunner.h"

int main(){
    RoadRunner* rr_ptr = CreateRRModel::createRRModel();

    rr_ptr->setConservedMoietyAnalysis(true);

    auto m = rr_ptr->getConservationMatrix();

    std::cout << m << std::endl;

    CreateRRModel::deleteRRModel(rr_ptr);

}