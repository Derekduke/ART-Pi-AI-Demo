# RTAK初步设计文稿

## RTAK API:

`rt_err_t rt_ai_register(rt_ai_t aihandle,const char *name, rt_uint16_t flags);`

| **Paramaters** | **Description**    |
| -------------- | ------------------ |
| aihandle       | 模型句柄           |
| name           | 模型名             |
| flags          | 标志(**暂未使用**) |
| **Return**     | --                 |
| rt_ai_t        | 已注册模型句柄     |
| NULL           | 未发现模型         |

后端模型进行注册.

`rt_ai_t  rt_ai_find(const char *name);`

| **Paramaters** | **Description** |
| -------------- | --------------- |
| name           | 注册的模型名    |
| **Return**     | --              |
| rt_ai_t        | 已注册模型句柄  |
| NULL           | 未发现模型      |



rt_err_t rt_ai_init(rt_ai_t aihandle, rt_aibuffer_t* buf);

| **Paramaters** | **Description** |
| -------------- | --------------- |
| aihandle       | rt_ai_t 句柄    |
| buf            | 计算所用内存    |
| **Return**     | --              |
| RT_EOK         | 初始化成功      |
| -RT_ERROR      | 初始化失败      |

初始化模型句柄, 挂载模型信息, 准备运行环境.

`rt_err_t rt_ai_run(rt_ai_t aihandle, rt_aibuffer_t *inputs_data, rt_aibuffer_t* outputs_data);`

| **Paramaters** | **Description**  |
| -------------- | ---------------- |
| aihandle       | rt_ai_t 模型句柄 |
| inputs_data    | 模型输入         |
| outputs_data   | 模型输出         |
| **Return**     | --               |
| RT_EOK         | 成功             |
|                |                  |

模型推理计算

`rt_err_t rt_ai_get_output(rt_ai_t aihandle, rt_aibuffer_t **buf, rt_uint32_t index, rt_size_t *size);`

| **Paramaters** | **Description**  |
| -------------- | ---------------- |
| aihandle       | rt_ai_t 模型句柄 |
| buf            | 结果地址         |
| index          | 结果索引         |
| size           | 返回结果的大小   |
| **Return**     | --               |
| RT_EOK         | 获取结果         |
| -RT_ERROR      | 获取结果失败     |

获取模型运行的结果, 结果获取后.

`rt_err_t rt_ai_get_info(rt_ai_t aihandle);`

| **Paramaters** | **Description**  |
| -------------- | ---------------- |
| aihandle       | rt_ai_t 模型句柄 |
| **Return**     | --               |
| RT_EOK         | 获取信息         |
| -RT_ERROR      | 获取信息失败     |

打印模型信息

`rt_err_t rt_ai_load(rt_ai_t aihandle, void *addr,  void *buf);`

| **Paramaters** | **Description**      |
| -------------- | -------------------- |
| aihandle       | rt_ai_t 句柄         |
| addr           | 模型地址: 地址或文件 |
| buf            | 模型加载地址         |
| **Return**     | --                   |
| RT_EOK         | 加载成功             |
| -RT_ERROR      | 加载失败             |

**暂未使用**, 加载模型, 从文件系统或地址, (创建句柄?) 

## RTAK 结构体

```

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
```

```
example:

ALIGN(4)
static const float input_data[AI_INPUT_SIZE_BYTES] = NUM_7;

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
 
 int sample_network_process(){
     
     rt_size_t size=0;
     
     rt_ai_run(model,(rt_aibuffer_t*)input_data, out_data);       // rtak api
     
    if(RT_EOK!=rt_ai_get_output(model, &out,0,&size)){     // rtak api
       rt_kprintf("get output error!\n");
       return -1;
    }
    rt_kprintf("\nget output size: %d\n",size);
    return 0;
 }
```

