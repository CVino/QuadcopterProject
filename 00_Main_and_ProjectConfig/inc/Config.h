#ifndef CONFIG
#define CONFIG

/*   DEBUGGING    */
#define DEBUG_HEIGHT_CTRL
//#define DEBUG_STABILITY_CTRL

/*   UART CHANEL    */
#define SerialUART   "/dev/ttyAMA0"

/*  SENSOR CONFIG: BNO055   */
#define OFFSET_ACC_X  7 //32917
#define OFFSET_ACC_Y  21 //32897
#define OFFSET_ACC_Z  65532 //65520

#define OFFSET_GYR_X  65535 //32897
#define OFFSET_GYR_Y  3 //32898
#define OFFSET_GYR_Z  1 //32897

#define OFFSET_MAG_X  3 //65230
#define OFFSET_MAG_Y  65220 //65485
#define OFFSET_MAG_Z  299 //32933

#define OFFSET_ACC_RAD  1000 //33768
#define OFFSET_MAG_RAD  679 //33460

/*  MOTORS CONFIG  */
#define FREQ_PWM  200
#define GRANUL_PWM  10000
#define INIT_PWM_1ms  2000 //Set to (GANUL_PWM*0.001*FREQ_PWM)
#define PWM_1  6
#define PWM_2  13
#define PWM_3  19
#define PWM_4  26
#define SAT_CTRL_MOT 100 // Upper saturation for the motors (%)
#define SAT_CTRL_MOT_I 10 // Integral Saturation
#define SAT_CTRL_MOT_D 10 // Derivative Saturation
#define DEG_TURN_OFF_MOT  75  //Maximum pitch and roll before setting motors to 0%

/* ULTRASOUND */
#define US_TRIGGER_PIN  4
#define US_ECHO_PIN  17

/*TASK SCHEDULING*/
#define SCHED_TASK_STABIL  0.02 //0.020 //stability task executed every 100ms
#define SCHED_TASK_HEIGHT  0.08 //0.080  //height task executed every 250ms

/* PID CONTROL CONSTANTS */
#define Kp  0 //0.25 //0.35 0.5
#define Kd  0 //4  //4.6
#define Ki  0 //0.03
#define KpH  17
#define KdH  25
#define KiH  0.3
#define KpYaw  0
#define KdYaw  0
#define KiYaw  0
#define MotorGForce 57
#define PID_EUL_ERROR_SAT 181  //Saturate euler angle error

/*  HEIGHT SETTINGS  */
#define SET_INITIAL_HEIGHT  0.03  //Initial height in meters

/* LOW PASS FILTER ORIENTANTION DATA */
#define AlphaLPF 0.8
#define OneMinusAlpha 0.2
//#define LOW_PASS_FILTER_ACTIVE //undef to deactivate

/* SATURATION FILTER ORIENTATION DATA */
#define SATFILT_SATVALUE 0.1
//#define SATURATION_FILTER	//undef to deactivate

#endif
