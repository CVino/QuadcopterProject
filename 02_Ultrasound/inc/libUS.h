#ifndef DEF_SONAR
#define DEF_SONAR


class UltraSound
{
  private:
    int _trigger;
    int _echo;
  public:
    UltraSound(unsigned int trigger, unsigned int echo);
    void Init(void);
    void GetDistance(void);
    //void RecordPulseLengthStart(uint32_t tick);
	//void RecordPulseLengthStop(uint32_t tick);
    float Distancem;
    unsigned volatile long startTimeUsec;
    unsigned volatile long endTimeUsec;
    unsigned long DifferenceTimeUsec;
};

void WrapperRecordPulse(int gpio, int level, uint32_t tick,void* Pointer);
//void WrapperPulseStart(int gpio, int level, uint32_t tick,void* Pointer);
//void WrapperPulseStop(int gpio, int level, uint32_t tick,void* Pointer);

#endif
