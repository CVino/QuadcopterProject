#include <pigpio.h>
#include "libMotor.h"
#include "Config.h"
#include <iostream>

int InitPWM(int pin, int freq)
{
	if (gpioSetMode(pin,PI_OUTPUT))
		return (-1);
	if(gpioPWM(pin,0))
		return (-1);
	if(gpioSetPWMfrequency(pin, freq) == PI_BAD_USER_GPIO)
		return (-1);
	if (gpioSetPWMrange(pin, GRANUL_PWM) == PI_BAD_DUTYRANGE)
		return (-1);
	if (gpioPWM(pin,INIT_PWM_1ms))
		return (-1);

	return(0);
}

/*Motor::Motor(int pin, int freq)
{
	this->_pin = pin;
	this->_freq = freq;
	InitPWM(_pin,_freq);
*/

Motor::Motor(int pin, int freq)	
{
	this->_pin = pin;
	this->_freq = freq;
	InitPWM(_pin,_freq);
}

int Motor::SetSpeed(double Speed)
{
	if(Speed>SAT_CTRL_MOT) Speed = SAT_CTRL_MOT;
	this->_Speed = Speed;
	#if defined(DEBUG_STABILITY_CTRL) || defined(DEBUG_HEIGHT_CTRL)
		std::cout 
		<< Speed <<"  "
		<< std::flush;
	#endif
	Speed=(int)(Speed*(INIT_PWM_1ms/100)+INIT_PWM_1ms);
	gpioPWM(_pin,(int)Speed);
	
	return 1;
}

double Motor::GetSpeed(void)
{
	return _Speed;
}

int Motor::Stop(void)
{
	gpioPWM(_pin,INIT_PWM_1ms);
	
	return 1;
}
