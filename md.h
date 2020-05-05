#ifndef MD_H_
#define MD_H_

#ifdef __cplusplus
extern "C"{
#endif

#define MD_DIR_FR 0
#define MD_DIR_BC 1

typedef struct{
	TIM_HandleTypeDef* timer;
	uint32_t channel;
	uint8_t direction;
	GPIO_TypeDef* inA_port;
	uint16_t inA_pin;
	GPIO_TypeDef* inB_port;
	uint16_t inB_pin;
}MD_HandleTypedef;

void MD_motor_init(MD_HandleTypedef *md_struct);
void MD_Run(MD_HandleTypedef *md_struct, float speed);

#ifdef __cplusplus
}
#endif
#endif

