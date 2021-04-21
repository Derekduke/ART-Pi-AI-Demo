/*
*
*
*/

#ifndef __AI_BECKEND_H
#define __AI_BECKEND_H
#include <rt_ai.h>
#include <ai_platform.h>
#include <rt_ai_config.h>

#define GET_SIZE_PALTFORM_TYPE(_fmt) ( (AI_BUFFER_FMT_GET_FLOAT(_fmt)) ? sizeof(float) : AI_BUFFER_FMT_GET_BITS(_fmt) )

// CUBE.AI
#ifndef MODEL_NAME
#define MODEL_NAME                      AI_MNIST_MODEL_NAME
#endif

#ifndef PLATFORM_AI_HANDLE
#define PLATFORM_AI_HANDLE              ai_handle
#endif

#ifndef PLATFORM_AI_INPUT_T
#define PLATFORM_AI_INPUT_T             ai_buffer
#endif

#ifndef PLATFORM_AI_OUTPUT_T
#define PLATFORM_AI_OUTPUT_T            ai_buffer
#endif

#ifndef PLATFORM_AI_PARAMS_T
#define PLAYFORM_AI_PARAMS_T            ai_network_params
#endif

#ifndef PLATFORM_AI_DATA_WEIGHTS_GET_F
#define PLATFORM_AI_DATA_WEIGHTS_GET_F  ai_MNIST_data_weights_get
#endif

#ifndef PLATFORM_AI_DATA_WEIGHTS
#define PLATFORM_AI_DATA_WEIGHTS        AI_MNIST_DATA_WEIGHTS
#endif

#ifndef PLATFORM_AI_DATA_ACTIVATIONS  
#define PLATFORM_AI_DATA_ACTIVATIONS    AI_MNIST_DATA_ACTIVATIONS
#endif

#ifndef PLATFORM_AI_ERR_T
#define PLATFORM_AI_ERR_T               ai_error
#endif

#ifndef PLATFORM_AI_INIT
#define PLATFORM_AI_INIT                ai_mnist_init  
#endif

#ifndef PLATFORM_AI_RUN
#define PLATFORM_AI_RUN                 ai_mnist_run 
#endif

#ifndef PLATFORM_AI_GET_INFO
#define PLATFORM_AI_GET_INFO            ai_mnist_get_info
#endif

#ifndef PLATFORM_AI_CREATE
#define PLATFORM_AI_CREATE              ai_mnist_create
#endif

#ifndef PLATFORM_AI_DESTORY
#define PLATFORM_AI_DESTORY             ai_mnist_destroy
#endif

#ifndef PLATFORM_AI_GET_ERROR
#define PLATFORM_AI_GET_ERROR           ai_mnist_get_error
#endif

#ifndef AI_INPUT_N
#define AI_INPUT_N                      AI_MNIST_IN_NUM
#endif

#ifndef AI_OUTPUT_N
#define AI_OUTPUT_N                     AI_MNIST_OUT_NUM
#endif


#ifndef AI_INPUT_INIT
#define AI_INPUT_INIT                   AI_MNIST_IN
#endif

#ifndef AI_OUTPUT_INIT
#define AI_OUTPUT_INIT                  AI_MNIST_OUT
#endif

#ifndef PLATFORM_AI_DATA_CONFIG         
#define PLATFORM_AI_DATA_CONFIG         AI_MNIST_DATA_CONFIG
#endif

#ifndef PLATFORM_AI_CREATE
#define PLATFORM_AI_CREATE              ai_log_err
#endif

#ifndef AI_INPUT_1_SIZE_BYTES
#define AI_INPUT_1_SIZE_BYTES          (1)
#endif     
           
#ifndef AI_INPUT_2_SIZE_BYTES
#define AI_INPUT_2_SIZE_BYTES          (0)
#endif     
           
#ifndef AI_INPUT_3_SIZE_BYTES
#define AI_INPUT_3_SIZE_BYTES          (0)
#endif

#ifndef AI_OUTPUT_1_SIZE_BYTES
#define AI_OUTPUT_1_SIZE_BYTES          (1)
#endif

#ifndef AI_OUTPUT_2_SIZE_BYTES
#define AI_OUTPUT_2_SIZE_BYTES          (0)
#endif

#ifndef AI_OUTPUT_3_SIZE_BYTES
#define AI_OUTPUT_3_SIZE_BYTES          (0)
#endif


#ifndef AI_INPUT_SIZE_BYTES
#define AI_INPUT_SIZE_BYTES             (AI_INPUT_1_SIZE_BYTES + AI_INPUT_2_SIZE_BYTES + AI_INPUT_2_SIZE_BYTES)
#endif

#ifndef AI_OUTPUT_SIZE_BYTES
#define AI_OUTPUT_SIZE_BYTES            (AI_OUTPUT_1_SIZE_BYTES + AI_OUTPUT_2_SIZE_BYTES + AI_OUTPUT_3_SIZE_BYTES) 
#endif

#endif //end
