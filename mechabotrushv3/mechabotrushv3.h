

// ensure this library description is only included once

#ifndef __mechabotrushv3_H__
#define __mechabotrushv3_H__

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//#include "QTRSensors.h"

#define SENSOR_CNT 5
#define ADDR_BASE 10
#define CENTER_VAL 2000



//MOTOR1-LEFT
const int PWM1 = 6;
const int dir1 = 2;
//MOTOR2-RIGHT
const int PWM2 = 5;
const int dir2 = 3;


enum EN_JUNCTION {
    BLACK_T,
    BLACK_RIGHT,
    BLACK_LEFT,
    WHITE_T,
    WHITE_RIGHT,
    WHITE_LEFT,
    BLACK_LEFT_ONLY,
    BLACK_RIGHT_ONLY,
    BLACK_T_WHITE_CENTER,
    WHITE_T_BLACK_CENTER
};

enum EN_LINE_FORMAT {
    BLACK_LINE,
    WHITE_LINE
};

enum EN_ACTION {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    TURN_RIGHT,
    TURN_LEFT,
    RIGHT_AT_C,
    LEFT_AT_C,
	RIGHT_AT_45,
    LEFT_AT_45,
    STOP
};

void initialize(bool debug);

void calibrate();

void readButton();
int getButtonEvt(int idx);

void pid_lineB(EN_LINE_FORMAT lineFormat, int speedBase, float Kp, float Kd);
void moveDelay(EN_LINE_FORMAT lineFormat, int speedBase, float Kp, float Kd, int delay);
void movePlan(EN_JUNCTION junction, EN_LINE_FORMAT lineFormat, int speedBase, float Kp, float Kd, int timerForward,
              int forwardSpeed, EN_ACTION action, int timerAction, int actionSpeed);
              
void actionPlanCenter(EN_LINE_FORMAT lineFormat, int timerForward, int forwardSpeed, EN_ACTION action, int actionSpeed);

void stop();
void forward(int speed, int timer);
void reverse(int speed, int timer);
void forwardCustom(int speedL, int speedR, int timer);


//function prototype step by step updated

void init_output();
void init_input();
void init_motor();
void init_serial();

void LEDs(int l, char *stat);
void Buzz(int l, char *stat);


void motordrive(char *directionL, int powerL, char *directionR, int powerR);
void motorsteer(char *robotdirection, int power);

void read_button();


#endif
