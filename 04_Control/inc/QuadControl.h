#ifndef QUADCOPTER
#define QUADCOPTER

#include "libMotor.h"
#include "RPi_BNO055.h"
#include "RPi_Sensor.h"
#include "libUS.h"


typedef enum
{	
	P = 0,
	PI = 1,
	PID = 2

}CtrlType;

typedef enum
{	
	Filt_Pitch = 0,
	Filt_Roll = 1,
	Filt_Yaw = 2

}Filterype;


class QuadCopter
{
	public:
		QuadCopter() 
			: _RefGPSx(0), _RefGPSy(0), _RefMoveRight(0), _RefMoveLeft(0), _RefMoveForw(0), 
			_RefMoveBackw(0), _RefHeight(0), _RefPitch(0), _RefRoll(0), _RefYaw(0), CtrlH_I(0),
			 ErrorH_D(0), CtrlP_I(0), ErrorP_D(0), CtrlR_I(0), ErrorR_D(0), CtrlY_I(0), ErrorY_D(0),
			 CtrlP(0), CtrlR(0), CtrlY(0), CtrlH(0), FiltRoll_UDY(0), FiltPitch_UDY(0), FiltYaw_UDY(0) 
		{}
		int HeightControl(float MeasDistance, CtrlType Type);
		int PitchControl(double MeasPitch, CtrlType Type);
		int RollControl(double MeasRoll, CtrlType Type);
		int YawControl(double MeasYaw, CtrlType Type);
		int SetCtrlMotors(double MeasRoll, double MeasPitch, Motor* M1, Motor* M2, Motor* M3, Motor* M4);
		int SetHeight(float HeightCm);
		int SetPitch(double PitchDeg);
		int SetRoll(double RollDeg);
		int SetYaw(double YawDeg);
		float Low_Pass_Filter(float Measure, Filterype Filt_Type);
		float _RefGPSx;
		float _RefGPSy;
		float _RefMoveRight;
		float _RefMoveLeft;
		float _RefMoveForw;
		float _RefMoveBackw;

	private:
		float _RefHeight;
		float _RefPitch;
		float _RefRoll;
		float _RefYaw;
		float CtrlH_I;
		float ErrorH_D;
		float CtrlP_I;
		float ErrorP_D;
		float CtrlR_I;
		float ErrorR_D;
		float CtrlY_I;
		float ErrorY_D;
		float CtrlP;
		float CtrlR;
		float CtrlY;
		float CtrlH;
		float FiltRoll_UDY;
		float FiltPitch_UDY;
		float FiltYaw_UDY;
};

struct StructCtrlHeight
{
	UltraSound* UltraSoundPtr;
	QuadCopter* QuadPtr;
	Motor* Motor1Ptr;
	Motor* Motor2Ptr;
	Motor* Motor3Ptr;
	Motor* Motor4Ptr;
};

struct StructCtrlIMU
{
	Adafruit_BNO055* IMUPtr;
	QuadCopter* QuadPtr;
	Motor* Motor1Ptr;
	Motor* Motor2Ptr;
	Motor* Motor3Ptr;
	Motor* Motor4Ptr;
};

#endif
