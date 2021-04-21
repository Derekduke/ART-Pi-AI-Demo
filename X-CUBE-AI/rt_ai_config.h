// generate >>>> 

#ifndef __AI_CFG_H
#define __AI_CFG_H

#include <network.h>
#include <network_data.h>
#include "ai_datatypes_defines.h"

#define PLATFORM_CUBE_AI                1

#define MODEL_NAME                      AI_NETWORK_MODEL_NAME


#define PLATFORM_AI_INPUT_T             ai_buffer



#define PLATFORM_AI_OUTPUT_T            ai_buffer



#define PLAYFORM_AI_PARAMS_T            ai_network_params



#define PLATFORM_AI_DATA_WEIGHTS_GET_F  ai_network_data_weights_get



#define PLATFORM_AI_DATA_WEIGHTS        AI_NETWORK_DATA_WEIGHTS



#define PLATFORM_AI_DATA_ACTIVATIONS    AI_NETWORK_DATA_ACTIVATIONS



#define PLATFORM_AI_ERR_T               ai_error



#define PLATFORM_AI_INIT                ai_network_init  



#define PLATFORM_AI_RUN                 ai_network_run 



#define PLATFORM_AI_GET_INFO            ai_network_get_info



#define PLATFORM_AI_CREATE              ai_network_create



#define PLATFORM_AI_DESTORY             ai_network_destroy



#define PLATFORM_AI_GET_ERROR           ai_network_get_error



#define AI_INPUT_N                      AI_NETWORK_IN_NUM



#define AI_OUTPUT_N                     AI_NETWORK_OUT_NUM



#define AI_INPUT_SIZE                   AI_NETWORK_IN_1_SIZE



#define AI_OUTPUT_SIZE                  AI_NETWORK_OUT_1_SIZE



#define AI_INPUT_SIZE_BYTES             AI_NETWORK_IN_1_SIZE_BYTES 



#define AI_OUTPUT_SIZE_BYTES            AI_NETWORK_OUT_1_SIZE_BYTES 



#define AI_INPUT_INIT                   AI_NETWORK_IN



#define AI_OUTPUT_INIT                  AI_NETWORK_OUT



#define PLATFORM_AI_DATA_CONFIG         AI_NETWORK_DATA_CONFIG


#define AI_WORK_BUFFER_SIZE             AI_NETWORK_DATA_ACTIVATIONS_SIZE

#endif

  //end
//<<<<generate