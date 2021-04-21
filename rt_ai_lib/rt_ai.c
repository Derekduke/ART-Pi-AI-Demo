/*
 * Copyright (c) 2006-2018, 
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
 
#include <rt_ai.h>
#ifdef RT_USING_AI_OPS
#define ai_init        (aihandle->ops->init)
#define ai_load        (aihandle->ops->load)
#define ai_run         (aihandle->ops->run)
#define ai_get_output  (aihandle->ops->get_output)
#define ai_get_info    (aihandle->ops->get_info)
#define ai_control     (aihandle->ops->control)
#else
#define ai_init         (aihandle->init)
#define ai_load         (aihandle->load)
#define ai_run          (aihandle->run)
#define ai_get_output   (aihandle->get_output)
#define ai_get_info     (aihandle->get_info)
#define ai_control      (aihandle->control)
#endif

static rt_ai_t ai_model;
/**
 * This function registers a ai driver with specified name.
 *
 * @param aihandle the pointer of ai driver structure
 * @param name the ai driver's name
 * @param flags the capabilities flag of ai
 *
 * @return the error code, RT_EOK on initialization successfully.
 */
rt_err_t rt_ai_register(rt_ai_t aihandle, const char *name, rt_uint16_t flags)
{
    if (aihandle == RT_NULL)
        return -RT_ERROR;

//    rt_object_init(&(aihandle->parent), RT_Object_Class_ai, name);
    ai_model = aihandle;
    rt_strncpy(ai_model->name, name, RT_NAME_MAX);
    return RT_EOK;
}
//RTM_EXPORT(rt_ai_register);

/**
 * This function removes a previously registered ai driver
 *
 * @param aihandle the pointer of ai driver structure
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_ai_unregister(rt_ai_t aihandle)
{

    return RT_EOK;
}
//RTM_EXPORT(rt_ai_unregister);
/**
 * This function finds a device driver by specified name.
 *
 * @param name the device driver's name
 *
 * @return the registered device driver on successful, or RT_NULL on failure.
 */
rt_ai_t rt_ai_find(const char *name)
{
    if(rt_strncmp(ai_model->name, name, RT_AI_NAME_MAX) == 0){
        return ai_model;
    }
    else{
        return RT_NULL;    
    } 

}
/**
 * This function will initialize the specified ai
 *
 * @param aihandle the pointer of ai driver structure
 *
 * @return the result
 */
rt_err_t rt_ai_init(rt_ai_t aihandle, rt_aibuffer_t* work_buf)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(aihandle != RT_NULL);

    /* get ai_init handler */
    
    if (ai_init != RT_NULL)
    {      
        result = ai_init(aihandle, work_buf);
        if (result != RT_EOK)
        {
            rt_kprintf("To initialize ai failed. The error code is %d\n", result);
            return -RT_ERROR;
        }
    }
    else{
        return  RT_EEMPTY;
    }
    aihandle->workbuffer = work_buf;
    aihandle->flag |= RT_AI_FLAG_INITED;

    return result;
}

/**
 * This function will open a ai
 *
 * @param aihandle the pointer of ai driver structure
 * @param oflag the flags for ai open
 *
 * @return the result
 */
rt_err_t rt_ai_load(rt_ai_t aihandle, rt_aibuffer_t *addr, rt_aibuffer_t *buf)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(aihandle != RT_NULL);

    /* call ai_open interface */
    if (ai_load != RT_NULL)
    {
        result = ai_load(aihandle, addr, buf);
    }
    else
    {
        /* set open flag */
        ;
    }

    /* set open flag */
    if (result == RT_EOK)
    {
        aihandle->flag |= RT_AI_FLAG_LOADED;
    }

    return result;
}

//RTM_EXPORT(rt_ai_open);

/**
 * This function will close a ai
 *
 * @param aihandle the pointer of ai driver structure
 *
 * @return the result
 */
rt_err_t rt_ai_run(rt_ai_t aihandle, rt_aibuffer_t *inputs_data, rt_aibuffer_t* outputs_data)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(aihandle != RT_NULL);

        /* if ai is not initialized, initialize it. */
    if (!(aihandle->flag & RT_AI_FLAG_INITED))
    {
        rt_kprintf("error: uninitialize!");
        return -RT_ERROR;
    }
    /* call ai_close interface */
    if (ai_run != RT_NULL)
    {
        result = ai_run(aihandle, inputs_data, outputs_data);
    }

    /* set open flag */
    if (result != RT_EOK ){
        return -RT_ERROR;
    }
    aihandle->flag |= RT_AI_FLAG_RUN;
    aihandle->flag |= RT_AI_FLAG_OUTPUT;
    aihandle->inputs = inputs_data;
    aihandle->outputs = outputs_data;
    return result;
}
//RTM_EXPORT(rt_ai_close);

/**
 * This function will read some data from a ai.
 *
 * @param aihandle the pointer of ai driver structure
 * @param pos the position of reading
 * @param buffer the data buffer to save read data
 * @param size the size of buffer
 *
 * @return the actually read size on successful, otherwise negative returned.
 *
 * @note since 0.4.0, the unit of size/pos is a block for block ai.
 */
rt_err_t rt_ai_get_output(rt_ai_t aihandle, rt_aibuffer_t **buf, rt_uint32_t index, rt_size_t *size)
{
    RT_ASSERT(aihandle != RT_NULL);

    if (!(aihandle->flag & RT_AI_FLAG_OUTPUT))
    {
        return -RT_ERROR;
    }

    /* call ai_read interface */
    if (ai_get_output != RT_NULL)
    {
        ai_get_output(aihandle, buf, index, size);
        aihandle->output_size = *size;
    }

    return RT_EOK;
}
//RTM_EXPORT(rt_ai_read);

/**
 * This function will write some data to a ai.
 *
 * @param aihandle the pointer of ai driver structure
 * @param pos the position of written
 * @param buffer the data buffer to be written to ai
 * @param size the size of buffer
 *
 * @return the actually written size on successful, otherwise negative returned.
 *
 * @note since 0.4.0, the unit of size/pos is a block for block ai.
 */
rt_err_t rt_ai_get_info(rt_ai_t aihandle)
{
    RT_ASSERT(aihandle != RT_NULL);

     if (!(aihandle->flag & RT_AI_FLAG_INITED))
    {
        rt_kprintf("error: uninitialize!");
        return -RT_ERROR;
    }

    rt_kprintf("model info:\n");
    rt_kprintf("%-15s:%d\n","n_input",aihandle->n_input);
    rt_kprintf("%-15s:%d\n","input_size",aihandle->input_size);
    rt_kprintf("%-15s:%d\n","n_output",aihandle->n_output);
    rt_kprintf("%-15s:%d\n","output_size",aihandle->output_size);

    /* call ai_write interface */
//    if (ai_get_info != RT_NULL)
//    {
//        ai_get_info(aihandle, buf);
//    }
    return 0;
}
//RTM_EXPORT(rt_ai_write);

/**
 * This function will perform a variety of control functions on ais.
 *
 * @param aihandle the pointer of ai driver structure
 * @param cmd the command sent to ai
 * @param arg the argument of command
 *
 * @return the result
 */
rt_err_t rt_ai_control(rt_ai_t aihandle, int cmd, rt_aibuffer_t *arg)
{
    RT_ASSERT(aihandle != RT_NULL);

    /* call ai_write interface */
    if (ai_control != RT_NULL)
    {
        return ai_control(aihandle, cmd, arg);
    }
 
    return -RT_ENOSYS;
}
//RTM_EXPORT(rt_ai_control);