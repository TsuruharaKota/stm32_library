#include"bno055.h"
#include<stdio.h>
#include<math.h>

void bnoInit(BNO_HandleTypedef *bno_state){
	//Set I2C fast and bring reset line high
	_i2c.frequency(400000);
	address = BNOAddress;
	accel_scale = 0.001f;
	rate_scale = 1.0f/16.0f;
	angle_scale = 1.0f/16.0f;
	temp_scale = 1;
}
void setmode(BNO_HandleTypedef *bno_state, char omode){
	writechar(BNO055_OPR_MODE_ADDR,omode);
	bno_state -> tx[0] = BNO055_OPR_MODE_ADDR;
	bno_state -> tx[1] = omode;
	HAL_I2C_Master_Transmit(&hi2c1, address, bno_state -> tx, 2, 1000);
	bno_state -> op_mode = omode;
}
void get_angles(BNO_HandleTypedef *bno_state){
	bno_state -> tx[0] = BNO055_EULER_H_LSB_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, address, bno_state -> tx, 1, 1000);
	//_i2c.write(address,tx,1,true);
	HAL_I2C_Master_Receive(&hi2c1, address + 1, bno_state -> rawdata, 6, 1000);
	//_i2c.read(address+1,rawdata,6,0);
	bno_state -> euler.rawyaw   = (bno_state -> rawdata[1] << 8 | bno_state -> rawdata[0]);
	bno_state -> euler.rawroll  = (bno_state -> rawdata[3] << 8 | bno_state -> rawdata[2]);
	bno_state -> euler.rawpitch = (bno_state -> rawdata[5] << 8 | bno_state -> rawdata[4]);
	bno_state -> euler.yaw   = float(bno_state -> euler.rawyaw)  * (bno_state -> angle_scale);
	bno_state -> euler.roll  = float(bno_state -> euler.rawroll) * (bno_state -> angle_scale);
	bno_state -> euler.pitch = float(bno_state -> euler.rawpitch)* (bno_state -> angle_scale);
}
