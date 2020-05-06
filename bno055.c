#include"bno055.h"
#include<stdio.h>
#include<math.h>

void bnoInit(BNO_HandleTypedef *bno_state){
    //Set I2C fast and bring reset line high
    bno_state -> address = BNOAddress;
    bno_state -> accel_scale = 0.001f;
    bno_state -> rate_scale = 1.0f/16.0f;
    bno_state -> angle_scale = 1.0f/16.0f;
    bno_state -> temp_scale = 1;
}
void setmode(BNO_HandleTypedef *bno_state, char omode){
    bno_state -> tx[0] = BNO055_OPR_MODE_ADDR;
    bno_state -> tx[1] = omode;
    HAL_I2C_Master_Transmit(bno_state -> Init.hi2c, bno_state -> address, (uint8_t *)(bno_state -> tx), 2, 1000);
    bno_state -> op_mode = omode;
}
void get_angles(BNO_HandleTypedef *bno_state){
	  bno_state -> tx[0] = BNO055_EULER_H_LSB_ADDR;
	  HAL_I2C_Master_Transmit(bno_state -> Init.hi2c, bno_state -> address, (uint8_t *)(bno_state -> tx), 1, 1000);
	  HAL_I2C_Master_Receive(bno_state -> Init.hi2c, bno_state -> address + 1, (uint8_t *)(bno_state -> rawdata), 6, 1000);
	  bno_state -> euler.rawyaw   = (bno_state -> rawdata[1] << 8 | bno_state -> rawdata[0]);
	  bno_state -> euler.rawroll  = (bno_state -> rawdata[3] << 8 | bno_state -> rawdata[2]);
	  bno_state -> euler.rawpitch = (bno_state -> rawdata[5] << 8 | bno_state -> rawdata[4]);
	  bno_state -> euler.yaw   = (float)((bno_state -> euler.rawyaw)  * (bno_state -> angle_scale));
	  bno_state -> euler.roll  = (float)((bno_state -> euler.rawroll) * (bno_state -> angle_scale));
	  bno_state -> euler.pitch = (float)((bno_state -> euler.rawpitch)* (bno_state -> angle_scale));
}
