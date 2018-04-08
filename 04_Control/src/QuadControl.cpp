#include "QuadControl.h"
#include "Config.h"
#include <iostream>


int QuadCopter::HeightControl(float MeasDistance, CtrlType Type)

{
	float ErrorH = this->_RefHeight - MeasDistance;
	float CtrlH_D;
	//std::cout << (double) ErrorH << std::endl;
	switch (Type)
	{
	
	case PID:
		this->CtrlH_I = this->CtrlH_I + (ErrorH*KiH*(1));
		if (CtrlH_I > SAT_CTRL_MOT)
			CtrlH_I = SAT_CTRL_MOT;
		if (CtrlH_I < -SAT_CTRL_MOT)
			CtrlH_I = -SAT_CTRL_MOT;
		CtrlH_D = KdH * (ErrorH - ErrorH_D) / (1);
		this->CtrlH = MotorGForce + KpH*ErrorH + CtrlH_I + CtrlH_D;
		#ifdef DEBUG_HEIGHT_CTRL
			std::cout << this->CtrlH << "  "<<std::flush;
		#endif
		if (CtrlH > SAT_CTRL_MOT)
			CtrlH = SAT_CTRL_MOT;
		if (CtrlH < 0)
			CtrlH = 0;
		ErrorH_D =  ErrorH;
		break;
		
	default:
		this->CtrlH=0;
	}

	return 1;
}

int QuadCopter::PitchControl(double MeasPitch, CtrlType Type)
{
	double ErrorP;
	if (abs(MeasPitch) < PID_EUL_ERROR_SAT)
		ErrorP = this->_RefPitch - MeasPitch;
	else
		ErrorP = ErrorP_D;
	double CtrlP_D;
	switch (Type)
	{
	
	case PID :
		this->CtrlP_I = this->CtrlP_I + (ErrorP*Ki*1);
		if (CtrlP_I > SAT_CTRL_MOT_I)
			CtrlP_I = SAT_CTRL_MOT_I;
		if (CtrlP_I < -SAT_CTRL_MOT_I)
			CtrlP_I = -SAT_CTRL_MOT_I;
		CtrlP_D = Kd * (ErrorP - ErrorP_D) / (1);
		this->CtrlP = Kp*ErrorP + CtrlP_I + CtrlP_D;
		#ifdef DEBUG_STABILITY_CTRL
			std::cout << this->CtrlP << "  "<<std::flush;
		#endif
		if (CtrlP > SAT_CTRL_MOT_D)
			CtrlP = SAT_CTRL_MOT_D;
		if (CtrlP < -SAT_CTRL_MOT_D)
			CtrlP = -SAT_CTRL_MOT_D;
		ErrorP_D =  ErrorP;
		break;
		
	default:
		this->CtrlP=0;
	}
	
	return 1;
}

int QuadCopter::RollControl(double MeasRoll, CtrlType Type)
{
	double ErrorR;
	if (abs(MeasRoll) < PID_EUL_ERROR_SAT)
		ErrorR = this->_RefRoll - MeasRoll;
	else
		ErrorR = ErrorR_D;
	double CtrlR_D;
	switch (Type)
	{
	
		case PID :
		this->CtrlR_I = this->CtrlR_I + (ErrorR*Ki*1);
		if (CtrlR_I > SAT_CTRL_MOT_I)
			CtrlR_I = SAT_CTRL_MOT_I;
		if (CtrlR_I < -SAT_CTRL_MOT_I)
			CtrlR_I = -SAT_CTRL_MOT_I;
		CtrlR_D = Kd * (ErrorR - ErrorR_D) / (1);
		this->CtrlR = Kp*ErrorR + CtrlR_I + CtrlR_D;
		#ifdef DEBUG_STABILITY_CTRL
			std::cout << this->CtrlR << "  "<<std::flush;
		#endif
		if (CtrlR > SAT_CTRL_MOT_D)
			CtrlR = SAT_CTRL_MOT_D;
		if (CtrlR < -SAT_CTRL_MOT_D)
			CtrlR = -SAT_CTRL_MOT_D;
		ErrorR_D =  ErrorR;
		break;
		
		default:
		this->CtrlR=0;
	}
	
	return 1;
}

int QuadCopter::YawControl(double MeasYaw, CtrlType Type)
{	
	double ErrorY;
	if (abs(MeasYaw) < PID_EUL_ERROR_SAT)
		ErrorY = this->_RefYaw - MeasYaw;
	else
		ErrorY = ErrorY_D;
	double CtrlY_D;
	switch (Type)
	{
	
		case PID :
		CtrlY_I = CtrlY_I + (ErrorY*KiYaw*1);
		if (CtrlY_I > SAT_CTRL_MOT_I)
			CtrlY_I = SAT_CTRL_MOT_I;
		if (CtrlY_I < -SAT_CTRL_MOT_I)
			CtrlY_I = -SAT_CTRL_MOT_I;
		CtrlY_D = KdYaw * (ErrorY - ErrorY_D) / (1);
		this->CtrlY = KpYaw*ErrorY + CtrlY_I + CtrlY_D;
		#ifdef DEBUG_STABILITY_CTRL
			std::cout << this->CtrlY << "  "<<std::flush;
		#endif
		if (CtrlY > SAT_CTRL_MOT_D)
			CtrlY = SAT_CTRL_MOT_D;
		if (CtrlY < -SAT_CTRL_MOT_D)
			CtrlY = -SAT_CTRL_MOT_D;
		ErrorY_D =  ErrorY;
		break;
		
		default:
		this->CtrlY=0;
	}
	
	return 1;
}

int QuadCopter::SetCtrlMotors (double MeasRoll, double MeasPitch, Motor* M1, Motor* M2, Motor* M3, Motor* M4)
{
	if ((abs(MeasRoll) > DEG_TURN_OFF_MOT) || (abs(MeasPitch) > DEG_TURN_OFF_MOT))
	{
		M1->SetSpeed(0);
		M2->SetSpeed(0);
		M3->SetSpeed(0);
		M4->SetSpeed(0);
		this->CtrlH_I=0;
		this->CtrlP_I=0;
		this->CtrlR_I=0;
		return -1;
	}
	else
	{
		//SetSpeed Motor1
		double SetCtrl = this->CtrlH - this->CtrlP + this->CtrlR + this->CtrlY;
		if (SetCtrl < 0)
			SetCtrl =0;
		M1->SetSpeed(SetCtrl);
		//SetSpeed Motor3
		SetCtrl = this->CtrlH + this->CtrlP - this->CtrlR + this->CtrlY;
		if (SetCtrl < 0)
			SetCtrl =0;
		M3->SetSpeed(SetCtrl);
		//SetSpeed 2
		SetCtrl = this->CtrlH - this->CtrlP - this->CtrlR - this->CtrlY;
		if (SetCtrl < 0)
			SetCtrl =0;
		M2->SetSpeed(SetCtrl);
		//SetSpeed Motor4
		SetCtrl = this->CtrlH + this->CtrlP + this->CtrlR - this->CtrlY;
		if (SetCtrl < 0)
			SetCtrl =0;
		M4->SetSpeed(SetCtrl);
		
		return 1;
	}
}

float QuadCopter::Low_Pass_Filter(float Measure, Filterype Filt_Type)
{
	float Output;
	switch (Filt_Type)
	{
		case Filt_Pitch:
			Output = Measure*AlphaLPF + FiltPitch_UDY*OneMinusAlpha;
			FiltPitch_UDY = Output;
		break;
		
		case Filt_Roll:
			Output = Measure*AlphaLPF + FiltRoll_UDY*OneMinusAlpha;
			FiltRoll_UDY = Output;
		break;
		
		case Filt_Yaw:
			Output = Measure*AlphaLPF + FiltYaw_UDY*OneMinusAlpha;
			FiltYaw_UDY = Output;
		break;
		
		default:
		FiltPitch_UDY = 0;
		FiltRoll_UDY = 0;
		FiltYaw_UDY = 0;
		break;
	}
	
	return Output;
		
}

int QuadCopter::SetHeight(float Heightm)
{
	this->_RefHeight = Heightm;
	return 1;
}

int QuadCopter::SetPitch(double PitchDeg)
{
	this->_RefPitch = PitchDeg;
	return 1;
}

int QuadCopter::SetRoll(double RollDeg)
{
	this->_RefRoll = RollDeg;
	return 1;
}

int QuadCopter::SetYaw(double YawDeg)
{
	this->_RefYaw = YawDeg;
	return 1;
}

