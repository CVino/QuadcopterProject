#include "Config.h"
#include "RPi_BNO055.h"

int GetOffsetConf(adafruit_bno055_offsets_t* pOffsets)
{
	pOffsets->accel_offset_x = OFFSET_ACC_X;
	pOffsets->accel_offset_y = OFFSET_ACC_Y;
	pOffsets->accel_offset_z = OFFSET_ACC_Z;
	pOffsets->gyro_offset_x = OFFSET_GYR_X;
	pOffsets->gyro_offset_y = OFFSET_GYR_Y;
	pOffsets->gyro_offset_z = OFFSET_GYR_Z;
	pOffsets->mag_offset_x = OFFSET_MAG_X;
	pOffsets->mag_offset_y = OFFSET_MAG_Y;
	pOffsets->mag_offset_z = OFFSET_MAG_Z;
	pOffsets->accel_radius = OFFSET_ACC_RAD;
	pOffsets->mag_radius = OFFSET_MAG_RAD;
	
	return 1;
}
