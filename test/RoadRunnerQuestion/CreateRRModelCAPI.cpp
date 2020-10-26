//
// Created by Ciaran Welsh on 26/10/2020.
//
#include "rr/rrRoadrunner.h"
#include "CreateRRModel.h"
#include "create_rr_model_c_api_export.h"

using namespace rr;

#ifdef __cplusplus
extern "C" {
#endif

CREATE_RR_MODEL_C_API_EXPORT
RoadRunner* CreateRRModel_createRRModel(){
    try{
        return CreateRRModel::createRRModel();
    } catch (std::exception &error) {
        fprintf(stderr, "Error: %s", error.what());
        exit(1);
    }
}



CREATE_RR_MODEL_C_API_EXPORT
bool CreateRRModel_deleteRRModel(RoadRunner* rr_ptr){
    try {
        CreateRRModel::deleteRRModel(rr_ptr);
        return true;
    } catch (std::exception &error) {
        fprintf(stderr, "Error: %s", error.what());
        return false;
    }
}










#ifdef __cplusplus
};
#endif
