#include"Encoder.h"
#include<stdio.h>
#include<math.h>

void EncoderUpdateData(Enc_HandleTypedef *enc_state){
	int32_t present_cnt = __HAL_TIM_GET_COUNTER(enc_state -> Init.htim);
	int32_t diff_cnt = enc_state -> Init.cnt_dir * (present_cnt - enc_state -> prev_cnt);
	volatile float diff;
	diff = (float)diff_cnt * enc_state -> Init.value_per_pulse / 4;
	enc_state -> vel = diff / enc_state -> Init.update_freq;
	enc_state -> prev_cnt = present_cnt;
	//オーバーフロー対策
}

void EncoderEnable(Enc_HandleTypedef *enc_state){
	HAL_TIM_Encoder_Start(enc_state -> Init.htim, TIM_CHANNEL_ALL);
	__HAL_TIM_SET_COUNTER(enc_state -> Init.htim, ENC_CNT_RESET);
	enc_state -> prev_cnt = ENC_CNT_RESET;
}

