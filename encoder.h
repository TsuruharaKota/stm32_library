#ifndef ENCODER_H_
#define ENCODER_H_
#ifdef __cplusplus
extern "C"{
#endif

#define _ENC_GET_VELOCITY(_ENC_STRUCT_)((_ENC_STRUCT_) -> vel)

#define ENC_CNT_PERIOD 65536
#define ENC_CNT_RESET (ENC_CNT_PERIOD / 2)
#define ENC_CNT_MAX 5000

typedef enum{
	ENC_FW_CNTUP = 1,
	ENC_FW_CNTDOWN = -1
}Enc_FW;

typedef struct{
	TIM_HandleTypeDef *htim;
	float update_freq;
	Enc_FW cnt_dir;
	float value_per_pulse;
}Enc_InitTypedef;

typedef struct{
	Enc_InitTypedef Init;
	int32_t prev_cnt;
	float vel;
}Enc_HandleTypedef;
void EncoderEnable(Enc_HandleTypedef *);
void EncoderUpdateData(Enc_HandleTypedef *);

#ifdef __cplusplus
}
#endif
#endif

