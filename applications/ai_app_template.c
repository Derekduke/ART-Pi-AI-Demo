/*
*   RTAK Generation Demo
*/

#include <rt_ai.h>
#include <rt_ai_config.h>
#include "drv_common.h"
#include <ai_app_template.h>
#include <board.h>
//#include <mnist_test_data.h>
CRC_HandleTypeDef hcrc;

#ifdef MNIST_DATA_H_
ALIGN(4)
static const float input_data[AI_INPUT_SIZE_BYTES] = NUM_7;
#else
ALIGN(4)
static const float input_data[AI_INPUT_SIZE_BYTES] = {0.0};
#endif

rt_aibuffer_t* xxx_work_buffer;

static rt_aibuffer_t* out_data;

rt_aibuffer_t* out;

rt_ai_t model = RT_NULL;

// generate demo
 int sample_network_init(){
  
    model = rt_ai_find(MODEL_NAME);                        // rtak api
    if(model == RT_NULL){
       rt_kprintf("model not found!");
       return -1;
    }
    
    xxx_work_buffer = rt_malloc(AI_WORK_BUFFER_SIZE);
    out_data = rt_malloc(AI_OUTPUT_SIZE_BYTES);
    
    if(RT_EOK != rt_ai_init(model,  xxx_work_buffer)){    // rtak api
       return -1;
    }
    
    rt_ai_get_info(model);
    
    return 0;
 }
 
 int sample_network_process(uint8_t* input_data){
     
     rt_size_t size=0;
     
     rt_ai_run(model,(rt_aibuffer_t*)input_data, out_data);       // rtak api
     
    if(RT_EOK!=rt_ai_get_output(model, &out,0,&size)){     // rtak api
       rt_kprintf("get output error!\n");
       return -1;
    }
    rt_kprintf("\nget output size: %d\n",size);
    return 0;
 }
 
 int sample_deal(){                                         // mnist prediction
     int pred = 0;
    for(int i = 0; i < AI_OUTPUT_SIZE; i++){
        if(((int8_t*)out)[i] > ((int8_t*)out)[pred]){
            pred = i;
         }
     }
     rt_kprintf("\nprediction: %d\n",pred);
     
     rt_free(xxx_work_buffer);
     rt_free(out_data);
     return pred;
 }

// stm32 ai environment
 
/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static int MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */
  return 0;
}
INIT_APP_EXPORT(MX_CRC_Init);

/**
* @brief CRC MSP Initialization
* This function configures the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspInit 0 */

  /* USER CODE END CRC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CRC_CLK_ENABLE();
  /* USER CODE BEGIN CRC_MspInit 1 */

  /* USER CODE END CRC_MspInit 1 */
  }

}

/**
* @brief CRC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspDeInit 0 */

  /* USER CODE END CRC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRC_CLK_DISABLE();
  /* USER CODE BEGIN CRC_MspDeInit 1 */

  /* USER CODE END CRC_MspDeInit 1 */
  }
}
