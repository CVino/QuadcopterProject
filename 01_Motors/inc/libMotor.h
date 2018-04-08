#ifndef DEF_MOTORS
#define DEF_MOTORS

class Motor
{
	public:
	  Motor(int, int);
	  int SetSpeed(double);
	  double GetSpeed(void);
	  int Stop(void);
	
	private:
	  int _pin;
	  int _freq;
	  double _Speed;
	
};

int InitPWM(int pin, int freq);

#endif
