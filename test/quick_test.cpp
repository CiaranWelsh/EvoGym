//
// Created by Ciaran Welsh on 28/09/2020.
//

#include "rr/rrRoadRunner.h"
#include "evo/RandomNetworkGenerator.h"
#include "evo/RandomNetworkGeneratorOptions.h"
#include "evo/EvoRateLaw.h"
#include "evo/logger.h"
#include "sbml/SBMLTypes.h"
using namespace evo;
using namespace rr;

int main(){
//    RateLaws rateLaws;
//    rateLaws["uni-bi"] = RateLaw("uni-bi", "k*A", RoleMap({{"k", EVO_PARAMETER}, {"A", EVO_SUBSTRATE}, {"B", EVO_PRODUCT}}));
//    rateLaws["uni-uni"] = RateLaw("uni-uni", "k*A",
//                                  RoleMap({{"k", EVO_PARAMETER},
//                                           {"A", EVO_SUBSTRATE}}));
//    EvoRateLaw t( "uni-uni", "k*A",
//            RoleMap({{"k", EVO_PARAMETER},
//                     {"A", EVO_SUBSTRATE}}));
//
    LOG("here");
//    libsbml::ASTNode* n = libsbml::SBML_parseFormula("k*A");
    RoadRunner roadRunner(3, 2);
    LOG("here");
}