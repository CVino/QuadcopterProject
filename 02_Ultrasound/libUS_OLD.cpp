#include <pigpio.h>
#include "libUS.h"


UltraSound::UltraSound (unsigned int trigger, unsigned int echo)
	: _trigger(trigger), _echo(echo), distanceCm(0)
{}

void UltraSound::Init(void)
{
    gpioSetMode(this->_trigger,PI_OUTPUT); 
    gpioSetMode(this->_echo,PI_INPUT); 
    gpioWrite(_trigger, 0);
    gpioSleep(PI_TIME_RELATIVE, 0.5, 0);
}

void UltraSound::GetDistance()
{
	endTimeUsec=0;
	gpioWrite(_trigger, 1);
	gpioDelay(10);
	gpioWrite(_trigger, 0);
    gpioSetISRFuncEx(_echo, RISING_EDGE, 0, WrapperPulseStart,this);
}


void UltraSound::RecordPulseLengthStart(uint32_t tick)
{
    startTimeUsec = tick;
    gpioSetISRFuncEx(_echo, FALLING_EDGE, 0, WrapperPulseStop, this);
    /*while ( gpioRead(_echo) == 1 )
    {
		endTimeUsec = gpioTick();
	}
	DifferenceTimeUsec = endTimeUsec - startTimeUsec;
	distanceCm = (double)DifferenceTimeUsec/58.7734;*/
}

void UltraSound::RecordPulseLengthStop(uint32_t tick)
{
	endTimeUsec = tick;
	if (endTimeUsec!= 0)
	{
		DifferenceTimeUsec = endTimeUsec - startTimeUsec;
		distanceCm = (double)DifferenceTimeUsec/58.7734;
	}
}
	
void WrapperPulseStart(int gpio, int level, uint32_t tick,void* Pointer)
{
	UltraSound* Ptr = (UltraSound*) Pointer;
	Ptr->RecordPulseLengthStart(tick);
}

void WrapperPulseStop(int gpio, int level, uint32_t tick,void* Pointer)
{
	UltraSound* Ptr = (UltraSound*) Pointer;
	Ptr->RecordPulseLengthStop(tick);
}
