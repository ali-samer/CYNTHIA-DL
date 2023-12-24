#pragma once

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define CYDL_TENSOR_MAX_DIMS 4
#define CYDL_TENSOR_MAX_NODES 4096
#define CYDL_TENSOR_MAX_PARAMS 16
#define CYDL_TENSOR_MAX_CONTEXTS 16

#ifdef __ARM_NEON
// we use the built-in 16-bit float type
typedef __fp16 ggml_fp16_t;
#else
typedef uint16_t ggml_fp16_t;
#endif

enum tensor_type
{
	TENSOR_TYPE_I8,
	TENSOR_TYPE_I18,
	TENSOR_TYPE_I32,
	TENSOR_TYPE_F16,
	TENSOR_TYPE_F32,
	TENSOR_TYPE_COUNT
};

struct tensor
{

};

//#ifdef __cplusplus
//}
//#endif