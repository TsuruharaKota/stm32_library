#include<stdio.h>
#include<math.h>

#ifndef BNO055_H_
#define BNO055_H_

#ifdef __cplusplus
extern "C"{
#endif

#define _BNO_GET_ANGLE(_BNO_STRUCT_)((_BNO_STRUCT_) -> deg_z)
typedef struct{
	TIM_HandleTypeDef* htim;
	}BNO_InitTypedef;

typedef struct{
	BNO_InitTypedef Init;
	float deg_z;
}BNO_HandleTypedef;

#ifdef
}
#endif

