#include <pigpio.h>
#include "libUS.h"
#include <iostream>

UltraSound::UltraSound (unsigned int trigger, unsigned int echo)
	: _trigger(trigger), _echo(echo), Distancem(0)
{}

void UltraSound::Init(void)
{
    gpioSetMode(this->_trigger,PI_OUTPUT); 
    gpioSetMode(this->_echo,PI_INPUT); 
    gpioWrite(_trigger, 0);
    gpioSleep(PI_TIME_RELATIVE, 0.5, 0);
    gpioSetAlertFuncEx(_echo, WrapperRecordPulse,this);
    //gpioSetISRFuncEx(_echo, EITHER_EDGE, 0, WrapperRecordPulse,this);
}

void UltraSound::GetDistance()
{
	endTimeUsec=0;
	gpioWrite(_trigger, 1);
	gpioDelay(10);
	gpioWrite(_trigger, 0);
}

	
void WrapperRecordPulse(int gpio, int level, uint32_t tick,void* Pointer)
{
	UltraSound* Ptr = (UltraSound*) Pointer;
	if (level == PI_ON) 
	{
		Ptr->startTimeUsec = tick;
	}
	else if (level == PI_OFF)
	{
		Ptr->endTimeUsec = tick;
		Ptr->DifferenceTimeUsec = Ptr->endTimeUsec - Ptr->startTimeUsec;
		Ptr->Distancem = (float)Ptr->DifferenceTimeUsec/5877.34;
	}
	
}

