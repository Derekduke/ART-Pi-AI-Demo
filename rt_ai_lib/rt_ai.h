#ifndef _RT_AI_H
#define _RT_AI_H

#include <rtthread.h>

#define RT_AI_NAME_MAX  16

#define RT_AI_FLAG_INITED   0x01
#define RT_AI_FLAG_LOADED   0X02
#define RT_AI_FLAG_RUN      0x04  
#define RT_AI_FLAG_OUTPUT   0x08

#if defined ( __CC_ARM )
#pragma anon_unions
#endif

typedef rt_uint8_t rt_aibuffer_t;

typedef struct rt_aihandle *rt_ai_t;

/**
 * ai handle structure
 */
struct rt_aihandle
{
    rt_uint16_t               flag;                 /**< ai flag */
    char                      name[RT_AI_NAME_MAX];
    char                      **info;             /**< reference count */
    rt_uint8_t                ai_id;                /**< 0 - 255 */
    rt_uint8_t                dma;
    rt_aibuffer_t             *inputs;
    rt_aibuffer_t             *outputs;
    rt_aibuffer_t             *workbuffer;          /**< ai private data */
    rt_uint32_t               n_input;
    rt_uint32_t               n_output;
    rt_ubase_t                input_size;
    rt_ubase_t                output_size;
    union {
        void    *model_addr;
        struct{
            void    *handle;
            void    *params;
        };
    };

#ifdef RT_USING_AI_OPS
    const struct rt_ai_ops *ops;
#else
    /* common ai interface */
    rt_err_t  (*init)           (rt_ai_t aihandle, rt_aibuffer_t *buf);
    rt_err_t  (*load)           (rt_ai_t aihandle, rt_aibuffer_t *addr, rt_aibuffer_t *buf);
    rt_err_t  (*run)            (rt_ai_t aihandle, rt_aibuffer_t *inputs_data, rt_aibuffer_t* outputs_data);
    rt_err_t  (*get_output)     (rt_ai_t aihandle, rt_aibuffer_t **outputs, rt_uint32_t index, rt_size_t *size);
    rt_err_t  (*get_info)       (rt_ai_t aihandle, rt_aibuffer_t *buf);
    rt_err_t  (*control)        (rt_ai_t aihandle, int cmd, rt_aibuffer_t *args);
#endif         
};

/**
 * operations set for ai object
 */
typedef struct _rt_ai_ops
{
    /* common ai interface */
    rt_aibuffer_t *a;
} rt_ai_ops;

rt_err_t rt_ai_register(rt_ai_t aihandle,const char *name, rt_uint16_t flags);
rt_err_t rt_ai_init(rt_ai_t aihandle, rt_aibuffer_t* buf);
rt_err_t rt_ai_run(rt_ai_t aihandle, rt_aibuffer_t *inputs_data, rt_aibuffer_t* outputs_data);
rt_ai_t  rt_ai_find(const char *name);
rt_err_t rt_ai_get_output(rt_ai_t aihandle, rt_aibuffer_t **buf, rt_uint32_t index, rt_size_t *size);
rt_err_t rt_ai_get_info(rt_ai_t aihandle);
#endif
