/* COMPILE & BUILD COMMANDS:
 * g++ -std=c++14  -Wall -pthread -c "%f" 
 * g++ -std=c++14  -Wall -pthread -o "%e" "%f" -lpigpio -lrt  RPi_BNO055.cpp libMotor.cpp libUS.cpp QuadControl.cpp
 * */

#include <pigpio.h>
#include <iostream>
#include <cstdlib>
#include "RPi_Sensor.h"
#include "RPi_BNO055.h"
#include "/home/pi/Documents/CVM_Projects/Quadcopter/utility/imumaths.h"
#include "libUS.h"
#include "libMotor.h"
#include "Config.h"
#include "QuadControl.h"
using namespace std;


/* GLOBAL VARIABLES */

//imu::Vector<3> Orientation;

/* OBJECT DECLARATIONS */



/*    FUNCTIONS    */
void HeightCtrl_Wrapper(void* Pointer)
{
	StructCtrlHeight* pStructHeight = (StructCtrlHeight*) Pointer;
	pStructHeight->UltraSoundPtr->GetDistance();
	#ifdef DEBUG_HEIGHT_CTRL
		std::cout << pStructHeight->UltraSoundPtr->Distancem << "  "<<std::flush;
	#endif
	//Height Control
	pStructHeight->QuadPtr->HeightControl(pStructHeight->UltraSoundPtr->Distancem,	PID);
}

void StabilityCtrl_Wrapper (void* Pointer)
{
	StructCtrlIMU* pStructIMU = (StructCtrlIMU*) Pointer;
	imu::Quaternion Quaternion = pStructIMU->IMUPtr->getQuat();
	imu::Vector<3> Orientation = Quaternion.toEuler()*(-57.2974693618);
	
	// Filtering
	#ifdef LOW_PASS_FILTER_ACTIVE
	  Orientation.x() = pStructIMU->QuadPtr->Low_Pass_Filter((float)Orientation.x(), Filt_Yaw);
	  Orientation.y() = pStructIMU->QuadPtr->Low_Pass_Filter((float)Orientation.y(), Filt_Pitch);
	  Orientation.z() = pStructIMU->QuadPtr->Low_Pass_Filter((float)Orientation.z(), Filt_Roll);
	#endif
	#ifdef SATURATION_FILTER
	if ((Orientation.z() < 0.1) && (Orientation.z() > -0.1))
		Orientation.z() = 0;
	if ((Orientation.y() < 0.1) && (Orientation.y() > -0.1))
		Orientation.y() = 0;
	#endif
	  
	// PRINT Euler Values
	#ifdef DEBUG_STABILITY_CTRL
		std::cout 
		<< Orientation.x() <<"  "
		<< Orientation.y() <<"  "
		<< Orientation.z() <<"  "
		<< std::flush;
	#endif
	
	//Roll Control
	pStructIMU->QuadPtr->RollControl(Orientation.z(),PID);
	//Pitch Control
	pStructIMU->QuadPtr->PitchControl(Orientation.y(),PID);
	//Yaw Control
	pStructIMU->QuadPtr->YawControl(Orientation.x(),PID);

	//Set Motors
	pStructIMU->QuadPtr->SetCtrlMotors(Orientation.z(), Orientation.y(), pStructIMU->Motor1Ptr, pStructIMU->Motor2Ptr, pStructIMU->Motor3Ptr, pStructIMU->Motor4Ptr);
	std::cout << std::endl;
}


/*    MAIN FUNCTION    */

int main(void)
{
	if (gpioInitialise() <0)
	{
		std::cout <<"Initialisation error of the GPIO \n Closing program..."<< std::endl;
		return (-1);
	}
	    
    /*  LOCAL OBJECTS  */
    UltraSound US(US_TRIGGER_PIN, US_ECHO_PIN);
	Adafruit_BNO055 bno = Adafruit_BNO055();
    Motor Motor1(PWM_1,FREQ_PWM);
	Motor Motor2(PWM_2,FREQ_PWM);
	Motor Motor3(PWM_3,FREQ_PWM);
	Motor Motor4(PWM_4,FREQ_PWM);
	QuadCopter Quad;
	
	/*  LOCAL VARIABLES  */	
	adafruit_bno055_offsets_t* Sensor_Offsets = (adafruit_bno055_offsets_t*)malloc(sizeof(*Sensor_Offsets));
	StructCtrlHeight PtrCtrlHeight = {&US, &Quad, &Motor1, &Motor2, &Motor3, &Motor4};
	StructCtrlIMU PtrCtrlIMU = {&bno, &Quad, &Motor1, &Motor2, &Motor3, &Motor4};
	
	
	US.Init();

	bno._HandleBNO = serOpen((char*)SerialUART, 115200, 0);
	gpioSleep(PI_TIME_RELATIVE, 0, 20000);
	
	if(!bno.begin())
	{
		serClose(bno._HandleBNO);
		gpioSleep(PI_TIME_RELATIVE, 0, 80000);
		bno._HandleBNO = serOpen((char*)SerialUART, 115200, 0);
		if(!bno.begin())
		{
			std::cout << "Ooops, no BNO055 detected ...!" << std::endl;
			return (-1);
		}
    }
	
	bno.setExtCrystalUse(true);
	GetOffsetConf(Sensor_Offsets);
	std::cout << "Set Offsets" << std::endl;
	bno.setSensorOffsets(*Sensor_Offsets);
	delete(Sensor_Offsets);
	std::cout << "Set OK" << std::endl;	
	//Motor1.SetSpeed(1);
	//Motor2.SetSpeed(1);
	//Motor3.SetSpeed(1);
	//Motor4.SetSpeed(1);
	
	gpioSetTimerFuncEx(0,SCHED_TASK_HEIGHT*1000,HeightCtrl_Wrapper,(StructCtrlHeight*) &PtrCtrlHeight);
	gpioSleep(PI_TIME_RELATIVE, 0, 1000);
	gpioSetTimerFuncEx(1,SCHED_TASK_STABIL*1000, StabilityCtrl_Wrapper,(StructCtrlIMU*) &PtrCtrlIMU);

	//uint8_t system, gyro, accel, mag = 0;
	Quad.SetHeight(SET_INITIAL_HEIGHT);
	//char in;
	//int TickIn=0, TickAct=0;
	while(1)
	{
		//std::cin >> in ;
		//if (in)k
		//return -1;
	
		//std::cout << "Height: " << (float) US.Distancem << std::endl;
		
		/*bno.getCalibration(&system, &gyro, &accel, &mag);
	    std::cout<< "CALIBRATIO: Sys=" << (int)system << " Gyro=" << (int) gyro
	    << " Accel=" << (int) accel << " Mag=" << (int)mag << std::endl;
		if(bno.isFullyCalibrated())
		{
			std::cout << "Calibration Ready" << std::endl;
		}*/
		//std::cout << "Motor1: " << (double) Motor1.GetSpeed() << "\n" <<
		//"Motor2: " << (double) Motor2.GetSpeed() << "\n" <<
		//"Motor3: " << (double) Motor3.GetSpeed() << "\n" <<
		//"Motor4: " << (double) Motor4.GetSpeed() << "\n" << std::endl;
		//gpioSleep(PI_TIME_RELATIVE, 0, 20000);

		
	}
	
}
