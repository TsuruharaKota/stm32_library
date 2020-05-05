#include"md.h"
#include<math.h>

uint32_t mspeed_32;

void MD_motor_init(MD_HandleTypedef *md_struct){
	__HAL_TIM_SET_COMPARE(md_struct -> timer, md_struct -> channel, 0); //PWM設定
}

void MD_Run(MD_HandleTypedef *md_struct, float speed){
	if(fabsf(speed) <= 1.0f){
		if((speed >= 0.0f) ^ md_struct -> direction){
			HAL_GPIO_WritePin(md_struct -> inA_port, md_struct -> inA_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(md_struct -> inB_port, md_struct -> inB_pin, GPIO_PIN_RESET);
		}else{
			HAL_GPIO_WritePin(md_struct -> inA_port, md_struct -> inA_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(md_struct -> inB_port, md_struct -> inB_pin, GPIO_PIN_SET);
		}
		//変換する
	}
}

