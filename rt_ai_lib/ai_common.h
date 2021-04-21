/*
*
*
*/

#ifndef AI_COMMON_H_
#define AI_COMMON_H_
#include <rt_aiconfig.h>
/********* reference tflite *********/
#ifdef AI_USE_COMPLEX64_T
// Single-precision complex data type compatible with the C99 definition.
typedef struct _rt_Complex64 {
  float re, im;  // real and imaginary parts, respectively.
} ai_Complex64_t;
#endif
#ifdef AI_USE_FLOAT16_T
// Half precision data type compatible with the C99 definition.
typedef struct _rt_Float16 {
  rt_uint16_t data;
} ai_Float16_t;
#endif
// Types supported by tensor
typedef enum {
  ai_NoType ,
  ai_Float32 ,
  ai_Int32 ,
  ai_UInt8 ,
  ai_Int64 ,
  ai_String ,
  ai_Bool ,
  ai_Int16 ,
#ifdef AI_USE_COMPLEX64_T
  ai_Complex64 ,
#endif
  ai_Int8 ,
#ifdef AI_USE_FLOAT16_T
  ai_Float16 ,
#endif
  ai_Float64 ,
} ai_type;


typedef union _rt_aiptr {
  rt_int32_t* i32;
  rt_int64_t* i64;
  float* f;
#ifdef AI_USE_FLOAT16_T
  ai_Float16_t* f16;
#endif
  char* raw;
  const char* raw_const;
  rt_uint8_t* uint8;
  bool* b;
  rt_int16_t* i16;
#ifdef AI_USE_COMPLEX64_T
  ai_Complex64_t* c64;
#endif
  rt_int8_t* int8;
  /* Only use this member. */
  void* data;
} rt_aiptr;

typedef struct _ai_tensor{
    ai_type type;
    rt_uint32_t dim; 
    rt_uint32_t shape[4]; //[b,h,w,c]
    rt_uint32_t len;
    rt_uint32_t bytes;
    rt_aiptr* data;
}rt_tensor;
    
#endif