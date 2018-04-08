#include <pigpio.h>
#include <iostream>
#include <cstdlib>
#include "RPi_Sensor.h"
#include "RPi_BNO055.h"

using namespace std;

int main (void)
{

	int i =0;
	Adafruit_BNO055 bno;
	adafruit_bno055_offsets_t* Sensor_Offsets = (adafruit_bno055_offsets_t*)malloc(sizeof(*Sensor_Offsets));
	adafruit_bno055_offsets_t OFFSET;
	
    if (gpioInitialise() <0)
	{
		std::cout <<"Initialisation error of the GPIO \n Closing program..."<< std::endl;
		return (-1);
	}
	int Hand=i2cOpen(1,0x28,0);
	cout << (int) Hand << endl;
	if (Hand < 0)
	cout <<"Error"<<endl;
		uint16_t read;
	//bno.begin();
	//bno.setExtCrystalUse(true);
    gpioSleep(PI_TIME_RELATIVE, 0, 1000*30);
	i2cWriteByteData(Hand,0x3D, 0x00);
	gpioSleep(PI_TIME_RELATIVE, 0, 1000*30);
	read = i2cReadByteData(Hand,0x3D);
	GetOffsetConf(Sensor_Offsets);
	cout << "MUST: " << (int) ((Sensor_Offsets->mag_offset_x) & 0x0FF) << endl;

	for (i=1;i<2;i++)
	{
		i2cWriteByteData(Hand,0x3D, i);
		cout << (int) (i2cReadByteData(Hand,0x3D) & 0x0F) << endl;
		i2cWriteByteData(Hand,0x3D, 0);
		cout << (int) (i2cReadByteData(Hand,0x3D) & 0x0F) << endl;
		//i2cWriteByteData(Hand,bno.MAG_OFFSET_X_LSB_ADDR, (Sensor_Offsets->mag_offset_x) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.MAG_OFFSET_X_LSB_ADDR) & 0x0FF) << endl;
		
		cout << "MUST: " << (int) ((Sensor_Offsets->mag_offset_x >> 8) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.MAG_OFFSET_X_MSB_ADDR, (Sensor_Offsets->mag_offset_x >> 8) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.MAG_OFFSET_X_MSB_ADDR) & 0x0FF) << endl;
		
		read = (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_X_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_X_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
		
		cout << "MUST: " << (int) ((Sensor_Offsets->mag_offset_y) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.MAG_OFFSET_Y_LSB_ADDR, (Sensor_Offsets->mag_offset_y) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.MAG_OFFSET_Y_LSB_ADDR) & 0x0FF) << endl;
		
	    cout << "MUST: " << (int) ((Sensor_Offsets->mag_offset_y >> 8) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.MAG_OFFSET_Y_MSB_ADDR, (Sensor_Offsets->mag_offset_y >> 8) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.MAG_OFFSET_Y_MSB_ADDR) & 0x0FF) << endl;
		
		read = (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_Y_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_Y_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
				
		cout << "MUST: " << (int) ((Sensor_Offsets->mag_offset_z) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.MAG_OFFSET_Z_LSB_ADDR, (Sensor_Offsets->mag_offset_z) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.MAG_OFFSET_Z_LSB_ADDR) & 0x0FF) << endl;
		
		cout << "MUST: " << (int) ((Sensor_Offsets->mag_offset_z >> 8) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.MAG_OFFSET_Z_MSB_ADDR, (Sensor_Offsets->mag_offset_z >> 8) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.MAG_OFFSET_Z_MSB_ADDR) & 0x0FF) << endl;
		
	    read = (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_Z_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_Z_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
				
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_x) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR, (Sensor_Offsets->accel_offset_x) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR) & 0x0FF) << endl;
		
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_x >> 8) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR, (Sensor_Offsets->accel_offset_x >> 8) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR) & 0x0FF) << endl;
		
read = (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
				
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_y) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Y_LSB_ADDR, (Sensor_Offsets->accel_offset_y) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_Y_LSB_ADDR) & 0x0FF) << endl;
		
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_y >> 8) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Y_MSB_ADDR, (Sensor_Offsets->accel_offset_y >> 8) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_Y_MSB_ADDR) & 0x0FF) << endl;
		
read = (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_Y_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_Y_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
				
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_z) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Z_LSB_ADDR, (Sensor_Offsets->accel_offset_z) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_Z_LSB_ADDR) & 0x0FF) << endl;
		
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_z >> 8) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Z_MSB_ADDR, (Sensor_Offsets->accel_offset_z >> 8) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_Z_MSB_ADDR) & 0x0FF) << endl;
		
read = (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_Z_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_Z_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
		
		//i2cWriteByteData(Hand,0x3D, 0x0B);
			}
	/*bno.getSensorOffsets(OFFSET); 
	std::cout << "ACC_OFF_X  " << (uint16_t) OFFSET.accel_offset_x<< "    ACC_OFF_Y  " << (uint16_t) OFFSET.accel_offset_y
		   << "    ACC_OFF_Z  " << (uint16_t) OFFSET.accel_offset_z << "    GYRO_OFF_X  " << (uint16_t) OFFSET.gyro_offset_x
		   << "    GYRO_OFF_Y  " << (uint16_t) OFFSET.gyro_offset_y << "    GYRO_OFF_Z  " << (uint16_t) OFFSET.gyro_offset_z
		   << "    MAG_OFF_X  " << (uint16_t) OFFSET.mag_offset_x << "    MAG_OFF_Y  " << (uint16_t) OFFSET.mag_offset_y << "    MAG_OFF_Z  " << (uint16_t) OFFSET.mag_offset_z
		   << "    ACC_OFF_RAD  " << (uint16_t) OFFSET.accel_radius << "    MAG_OFF_RAD  " << (uint16_t) OFFSET.mag_radius << std::endl;
	i2cWriteByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR, (Sensor_Offsets->accel_offset_x) & 0x0FF);
    i2cWriteByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR, (Sensor_Offsets->accel_offset_x >> 8) & 0x0FF);
    i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Y_LSB_ADDR, (Sensor_Offsets->accel_offset_y) & 0x0FF);
    i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Y_MSB_ADDR, (Sensor_Offsets->accel_offset_y >> 8) & 0x0FF);
    std::cout << Sensor_Offsets->accel_offset_z << std::endl;
    i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Z_LSB_ADDR, (Sensor_Offsets->accel_offset_z) & 0x0FF);
    i2cWriteByteData(Hand,bno.ACCEL_OFFSET_Z_MSB_ADDR, (Sensor_Offsets->accel_offset_z >> 8) & 0x0FF);
    std::cout << "redad: " << (int) ((i2cReadByteData(Hand,bno.ACCEL_OFFSET_Z_MSB_ADDR) << 8) | (i2cReadByteData(Hand,bno.ACCEL_OFFSET_Z_LSB_ADDR))) << std::endl;

	std::cout << Sensor_Offsets->gyro_offset_x << std::endl;
    i2cWriteByteData(Hand,bno.GYRO_OFFSET_X_LSB_ADDR, (Sensor_Offsets->gyro_offset_x) & 0x0FF);
    i2cWriteByteData(Hand,bno.GYRO_OFFSET_X_MSB_ADDR, (Sensor_Offsets->gyro_offset_x >> 8) & 0x0FF);
    std::cout << Sensor_Offsets->gyro_offset_y << std::endl;
    i2cWriteByteData(Hand,bno.GYRO_OFFSET_Y_LSB_ADDR, (Sensor_Offsets->gyro_offset_y) & 0x0FF);
    i2cWriteByteData(Hand,bno.GYRO_OFFSET_Y_MSB_ADDR, (Sensor_Offsets->gyro_offset_y >> 8) & 0x0FF);
    std::cout << Sensor_Offsets->gyro_offset_z << std::endl;
    i2cWriteByteData(Hand,bno.GYRO_OFFSET_Z_LSB_ADDR, (Sensor_Offsets->gyro_offset_z) & 0x0FF);
    i2cWriteByteData(Hand,bno.GYRO_OFFSET_Z_MSB_ADDR, (Sensor_Offsets->gyro_offset_z >> 8) & 0x0FF);

    i2cWriteByteData(Hand,bno.MAG_OFFSET_X_LSB_ADDR, (Sensor_Offsets->mag_offset_x) & 0x0FF);
    i2cWriteByteData(Hand,bno.MAG_OFFSET_X_MSB_ADDR, (Sensor_Offsets->mag_offset_x >> 8) & 0x0FF);
    i2cWriteByteData(Hand,bno.MAG_OFFSET_Y_LSB_ADDR, (Sensor_Offsets->mag_offset_y) & 0x0FF);
    i2cWriteByteData(Hand,bno.MAG_OFFSET_Y_MSB_ADDR, (Sensor_Offsets->mag_offset_y >> 8) & 0x0FF);
    i2cWriteByteData(Hand,bno.MAG_OFFSET_Z_LSB_ADDR, (Sensor_Offsets->mag_offset_z) & 0x0FF);
    i2cWriteByteData(Hand,bno.MAG_OFFSET_Z_MSB_ADDR, (Sensor_Offsets->mag_offset_z >> 8) & 0x0FF);

    i2cWriteByteData(Hand,bno.ACCEL_RADIUS_LSB_ADDR, (Sensor_Offsets->accel_radius) & 0x0FF);
    i2cWriteByteData(Hand,bno.ACCEL_RADIUS_MSB_ADDR, (Sensor_Offsets->accel_radius >> 8) & 0x0FF);

    i2cWriteByteData(Hand,bno.MAG_RADIUS_LSB_ADDR, (Sensor_Offsets->mag_radius) & 0x0FF);
    i2cWriteByteData(Hand,bno.MAG_RADIUS_MSB_ADDR, (Sensor_Offsets->mag_radius >> 8) & 0x0FF);   
		   
bno.getSensorOffsets(OFFSET); 
	std::cout << "ACC_OFF_X  " << (uint16_t) OFFSET.accel_offset_x<< "    ACC_OFF_Y  " << (uint16_t) OFFSET.accel_offset_y
		   << "    ACC_OFF_Z  " << (uint16_t) OFFSET.accel_offset_z << "    GYRO_OFF_X  " << (uint16_t) OFFSET.gyro_offset_x
		   << "    GYRO_OFF_Y  " << (uint16_t) OFFSET.gyro_offset_y << "    GYRO_OFF_Z  " << (uint16_t) OFFSET.gyro_offset_z
		   << "    MAG_OFF_X  " << (uint16_t) OFFSET.mag_offset_x << "    MAG_OFF_Y  " << (uint16_t) OFFSET.mag_offset_y << "    MAG_OFF_Z  " << (uint16_t) OFFSET.mag_offset_z
		   << "    ACC_OFF_RAD  " << (uint16_t) OFFSET.accel_radius << "    MAG_OFF_RAD  " << (uint16_t) OFFSET.mag_radius << std::endl;
*/
//i2cWriteByteData(Hand,0x3D, 0x0);
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_x) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR, (Sensor_Offsets->accel_offset_x) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR) & 0x0FF) << endl;
		
		cout << "MUST: " << (int) ((Sensor_Offsets->accel_offset_x >> 8) & 0x0FF) << endl;
		//i2cWriteByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR, (Sensor_Offsets->accel_offset_x >> 8) & 0x0FF);
		cout << (int) (i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR) & 0x0FF) << endl;
		
read = (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
	gpioSleep(PI_TIME_RELATIVE, 3, 0);	
			read = (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_Y_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.MAG_OFFSET_Y_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
		read = (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_MSB_ADDR)) << 8) | (((uint8_t)i2cReadByteData(Hand,bno.ACCEL_OFFSET_X_LSB_ADDR)));
		cout << (uint16_t) read  << endl;
		
	i2cWriteByteData(Hand,0x3D, 0x0B);
	//cout << (int) (read & 0x0F) << endl;
	i2cClose(Hand);
	return 1;
	
}
