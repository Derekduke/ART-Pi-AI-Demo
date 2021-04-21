/*
*
*
*
*
*
*/

#include <backend_cubeai.h>
#include <rt_ai.h>
/**********CUBE.AI****************/
static PLATFORM_AI_HANDLE platform_handle = AI_HANDLE_NULL;
static rt_aibuffer_t *output_buffer;
static ai_network_report model_info;
static struct rt_aihandle model;

PLATFORM_AI_INPUT_T *platform_ai_input;
PLATFORM_AI_OUTPUT_T *platform_ai_output;

static rt_err_t cubeai_backend_init(rt_ai_t aihandle, rt_aibuffer_t *work_buf){
     PLATFORM_AI_ERR_T err;
     
    /* 1 - Create an instance of the model */
  err = PLATFORM_AI_CREATE (&platform_handle, PLATFORM_AI_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
//    ai_log_err(err, "ai_mnist_create");
    return -1;
  }

  /* 2 - Initialize the instance */
  const PLAYFORM_AI_PARAMS_T params = {
      PLATFORM_AI_DATA_WEIGHTS(PLATFORM_AI_DATA_WEIGHTS_GET_F()),
      PLATFORM_AI_DATA_ACTIVATIONS(work_buf) };

  if (!PLATFORM_AI_INIT(platform_handle, &params)) {
      err = PLATFORM_AI_GET_ERROR (platform_handle);
//      ai_log_err(err, "ai_mnist_init");
      return -1;
    }

  /* 3 - Retrieve the network info of the created instance */
  if (!PLATFORM_AI_GET_INFO(platform_handle, &model_info)) {
    err = PLATFORM_AI_GET_ERROR(platform_handle);
//    ai_log_err(err, "ai_mnist_get_error");
    PLATFORM_AI_DESTORY(platform_handle);
    platform_handle = AI_HANDLE_NULL;
    return -3;
  }
  platform_ai_input = model_info.inputs;
  platform_ai_output = model_info.outputs;
    return RT_EOK;
}

static rt_err_t cubeai_backend_run(rt_ai_t aihandle, rt_aibuffer_t *inputs_data, rt_aibuffer_t *outputs_data)
    {
    
    PLATFORM_AI_ERR_T err;
    rt_size_t addr_cnt = 0;
    ai_i32 batch;
    
    output_buffer = outputs_data;

   platform_ai_input[0].data = AI_HANDLE_PTR(&inputs_data[0]);
//  platform_ai_output[0].data = AI_HANDLE_PTR(&output_buffer[0]);
    
  for(int i = 0; i < AI_OUTPUT_N ; i++){
 
    platform_ai_output[i].data = AI_HANDLE_PTR(&output_buffer[addr_cnt]);
    ai_buffer_format _fmt = AI_BUFFER_FORMAT(&platform_ai_output[i]);
    addr_cnt += GET_SIZE_PALTFORM_TYPE(_fmt)*AI_BUFFER_SIZE(&platform_ai_output[i]);
  }
  
  batch = PLATFORM_AI_RUN(platform_handle, &platform_ai_input[0], &platform_ai_output[0]);

  if (batch != 1) {
//    ai_log_err(ai_mnist_get_error(platform_handle),
//        "ai_mnist_run");
      err = PLATFORM_AI_GET_ERROR (platform_handle);
      (void) err;
    return -1;
  }

    return RT_EOK;
}

static rt_err_t cubeai_backend_get_output(rt_ai_t aihandle, rt_aibuffer_t **buf, rt_uint32_t index, rt_size_t *size){
    if(index >= AI_OUTPUT_N){
        return -1;
    }
    ai_buffer_format _fmt = AI_BUFFER_FORMAT(&platform_ai_output[index]);
    
    *buf = platform_ai_output[index].data;
    *size = GET_SIZE_PALTFORM_TYPE(_fmt) * AI_BUFFER_SIZE(&platform_ai_output[index]);
    return RT_EOK;
}

static int cubeai_init(){
    model.init = cubeai_backend_init;
    model.run = cubeai_backend_run;
    model.get_output = cubeai_backend_get_output;
    model.n_input = AI_INPUT_N;
    model.n_output = AI_OUTPUT_N;
    model.input_size = AI_INPUT_SIZE_BYTES;
    model.output_size = AI_OUTPUT_SIZE_BYTES;
    rt_ai_register(&model,MODEL_NAME ,0);
    
    return 0;

}
INIT_APP_EXPORT(cubeai_init);
/**********CUBE.AI end****************/
