/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "drv_spi_ili9488.h"
#include <lcd_spi_port.h>
#include <ai_app_template.h>

#define LED_PIN GET_PIN(I, 8)

struct rt_event ov2640_event;
extern rt_uint8_t model_input_data_rgb[];
extern rt_uint8_t model_input_data_gray[];

rt_uint8_t ai_flag = 0;

void ai_camera()
{
    rt_gc0328c_init();
    ai_flag = 1;
    DCMI_Start();
}
MSH_CMD_EXPORT(ai_camera, Start the AI camera to recognize person);

int main(void)
{

    /* Example Here */
    rt_uint32_t count = 0 , frame = 0;
    rt_uint8_t res_p;

    sample_network_init();
    sample_network_process(model_input_data_rgb);
    sample_deal();

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    /* init spi data notify event */
    rt_event_init(&ov2640_event, "ov2640", RT_IPC_FLAG_FIFO);
    struct drv_lcd_device *lcd;
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");
    struct rt_device_rect_info rect_info = {0, 0, LCD_WIDTH, 240};

    while(1)
    {
        rt_event_recv(&ov2640_event,
                            1,
                            RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER,
                            RT_NULL);
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);//show 320*240 RGB image
        //lcd_show_image(0, 0, 96, 96, model_input_data_rgb);//show 96*96*3 RGB image
        if(ai_flag == 1)
        {
            sample_network_init();
            sample_network_process(model_input_data_rgb);
            res_p = sample_deal();
            frame++;
            if(res_p == 1)
            {
                if(count == 0)
                    frame = 0;
                if(frame - count > 10)
                {
                    count = 0;
                }
                else {
                    count++;
                }
                if(count == 10)
                {
                    ai_flag = 0;
                    for(uint8_t i=0 ; i<3 ; i++) //notice
                    {
                        lcd_fill(0, 240, 320, 480, RED);
                        rt_thread_mdelay(500);
                        lcd_fill(0, 240, 320, 480, BLACK);
                        rt_thread_mdelay(500);
                    }
                    count = 0;
                    rt_kprintf("person detect success!\n");
                }
            }
            if(ai_flag == 1)
                DCMI_Start();
            else
                DCMI_Stop();
        }
    }
    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
   /* Vector Table Relocation in Internal QSPI_FLASH */
   SCB->VTOR = QSPI_BASE;
   return 0;
}
INIT_BOARD_EXPORT(vtor_config);


