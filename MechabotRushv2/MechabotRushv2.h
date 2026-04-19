/*
  tuahmini.h - Library for Tuah Mini
  Copyright (c) 2018 Fauzan Khairi Che Harun.  All right reserved.
*/

/*

This library has been merged with QTRSensors and Tuah motor Library.
Other QTR function for call name remain the same.


*/

// ensure this library description is only included once
#ifndef MechabotRushv2_h
#define MechabotRushv2_h

#define QTR_EMITTERS_OFF 0
#define QTR_EMITTERS_ON 1
#define QTR_EMITTERS_ON_AND_OFF 2

#define QTR_NO_EMITTER_PIN  255

#define QTR_MAX_SENSORS 16





// include types & constants of Wiring core API
//MOTOR1
const int PWM1 = 6;
const int dir1 = 2;
//MOTOR2
const int PWM2 = 5;
const int dir2 = 3;

//Infrared LineFollow


#include "Arduino.h"


// This class cannot be instantiated directly (it has no constructor).
// Instead, you should instantiate one of its two derived classes (either the
// QTR-A or QTR-RC version, depending on the type of your sensor).
class QTRSensors
{
  public:

    // Reads the sensor values into an array. There *MUST* be space
    // for as many values as there were sensors specified in the constructor.
    // Example usage:
    // unsigned int sensor_values[8];
    // sensors.read(sensor_values);
    // The values returned are a measure of the reflectance in abstract units,
    // with higher values corresponding to lower reflectance (e.g. a black
    // surface or a void).
    // If measureOffAndOn is true, measures the values with the
    // emitters on AND off and returns on - (timeout - off).  If this
    // value is less than zero, it returns zero.
    // This method will call the appropriate derived class's readPrivate(),
    // which is defined as a virtual function in the base class and
    // overridden by each derived class's own implementation.
    void read(unsigned int *sensor_values, unsigned char readMode = QTR_EMITTERS_ON);
    void pid_line(int right_base, int left_base, int speedturn, int maxSpeed, float Kp, float Kd, int line_format, int senspeed);
    void mechabotrushv2FinderW(int inByte, int inNext, int lajur, int lajul, float turn, int speedturn, float kp, float kd, int sensorc, int lajak, int dturn);
    void mechabotrushv2FinderB(int inByte, int inNext, int lajur, int lajul, float turn, int speedturn, float kp, float kd, int sensorc, int lajak, int dturn);
	void mechabotrushv2Dtracer(int lajur, int lajul, int speedturn, float kp, float kd, int sensorc, int linef, int dtracer); 
	void mechabotrushv2flineB(int lajur, int lajul, int sensorc, int linef); 
	void mechabotrushv2flineW(int lajur, int lajul, int sensorc, int linef); 
	void mechabotrushv2tillJunction(int lajul, int lajur, int speedturn, int sensorc, int inByte, float kp, float kd,int linef,int basespeed,int forwarddelay);
    void mechabotrushv2tillJunctionSimple(int laju,  int inByte, float kp, float kd, int linef);
    void mechabotrushv2FinderBlack(int inByte, int inNext, int laju, int turnspeed,float kp, float kd , int lajak,int turndelay); // (type of junction, next robot action, robot speed, turn speed percentage)
	void mechabotrushv2FinderWhite(int inByte, int inNext, int laju, int turnspeed,float kp, float kd, int terus,int turndelay); // (type of junction, next robot action, robot speed, turn speed percentage)
    void turn_R(char a, char b);
    void turn_L(char a, char b);
    void turn_L_center(char a);
    void turn_R_center(char a);
    void turn_at_center(int direction, int speed,int sensorc, int linef);
    void reverse(char a, char b);
    void advance(char a, char b);
    void LEDsense(int positionx);
    void stop();
    void Motor(int M1, int M2, int MD1, int MD2);

    // Turn the IR LEDs off and on.  This is mainly for use by the
    // read method, and calling these functions before or
    // after the reading the sensors will have no effect on the
    // readings, but you may wish to use these for testing purposes.
    void emittersOff();
    void emittersOn();

    // Reads the sensors for calibration.  The sensor values are
    // not returned; instead, the maximum and minimum values found
    // over time are stored internally and used for the
    // readCalibrated() method.
    void calibrate(unsigned char readMode = QTR_EMITTERS_ON);

    // Resets all calibration that has been done.
    void resetCalibration();

    // Returns values calibrated to a value between 0 and 1000, where
    // 0 corresponds to the minimum value read by calibrate() and 1000
    // corresponds to the maximum value.  Calibration values are
    // stored separately for each sensor, so that differences in the
    // sensors are accounted for automatically.
    void readCalibrated(unsigned int *sensor_values, unsigned char readMode = QTR_EMITTERS_ON);

    // Operates the same as read calibrated, but also returns an
    // estimated position of the robot with respect to a line. The
    // estimate is made using a weighted average of the sensor indices
    // multiplied by 1000, so that a return value of 0 indicates that
    // the line is directly below sensor 0, a return value of 1000
    // indicates that the line is directly below sensor 1, 2000
    // indicates that it's below sensor 2000, etc.  Intermediate
    // values indicate that the line is between two sensors.  The
    // formula is:
    //
    //    0*value0 + 1000*value1 + 2000*value2 + ...
    //   --------------------------------------------
    //         value0  +  value1  +  value2 + ...
    //
    // By default, this function assumes a dark line (high values)
    // surrounded by white (low values).  If your line is light on
    // black, set the optional second argument white_line to true.  In
    // this case, each sensor value will be replaced by (1000-value)
    // before the averaging.
    int readLine(unsigned int *sensor_values, unsigned char readMode = QTR_EMITTERS_ON, unsigned char white_line = 0);

    // Calibrated minumum and maximum values. These start at 1000 and
    // 0, respectively, so that the very first sensor reading will
    // update both of them.
    //
    // The pointers are unallocated until calibrate() is called, and
    // then allocated to exactly the size required.  Depending on the
    // readMode argument to calibrate, only the On or Off values may
    // be allocated, as required.
    //
    // These variables are made public so that you can use them for
    // your own calculations and do things like saving the values to
    // EEPROM, performing sanity checking, etc.
    unsigned int *calibratedMinimumOn;
    unsigned int *calibratedMaximumOn;
    unsigned int *calibratedMinimumOff;
    unsigned int *calibratedMaximumOff;
    int last_error = 0; //last error
    int right_motor_pwm = 0; //right motor pwm
    int left_motor_pwm = 0; //left motor pwm
    unsigned int sensorValues[5];
    unsigned int position = 0;
//int line=0;    //floor 0 black on white, 1 white on black

    ~QTRSensors();

  protected:

    QTRSensors()
    {

    };

    void init(unsigned char *pins, unsigned char numSensors, unsigned char emitterPin);

    unsigned char *_pins;
    unsigned char _numSensors;
    unsigned char _emitterPin;
    unsigned int _maxValue; // the maximum value returned by this function
    int _lastValue;

  private:
   int _pin1;
   int _pin2;
   int _pin3;
   int _pin4;

    virtual void readPrivate(unsigned int *sensor_values) = 0;

    // Handles the actual calibration. calibratedMinimum and
    // calibratedMaximum are pointers to the requested calibration
    // arrays, which will be allocated if necessary.
    void calibrateOnOrOff(unsigned int **calibratedMinimum,
                          unsigned int **calibratedMaximum,
                          unsigned char readMode);
};



// Object to be used for QTR-1RC and QTR-8RC sensors
class QTRSensorsRC : public QTRSensors
{
  public:

    // if this constructor is used, the user must call init() before using
    // the methods in this class
    QTRSensorsRC();

    // this constructor just calls init()
    QTRSensorsRC(unsigned char* pins, unsigned char numSensors,
          unsigned int timeout = 4000, unsigned char emitterPin = 255);


    // The array 'pins' contains the Arduino pin number for each sensor.

    // 'numSensors' specifies the length of the 'pins' array (i.e. the
    // number of QTR-RC sensors you are using).  numSensors must be
    // no greater than 16.

    // 'timeout' specifies the length of time in microseconds beyond
    // which you consider the sensor reading completely black.  That is to say,
    // if the pulse length for a pin exceeds 'timeout', pulse timing will stop
    // and the reading for that pin will be considered full black.
    // It is recommended that you set timeout to be between 1000 and
    // 3000 us, depending on things like the height of your sensors and
    // ambient lighting.  Using timeout allows you to shorten the
    // duration of a sensor-reading cycle while still maintaining
    // useful analog measurements of reflectance

    // 'emitterPin' is the Arduino pin that controls the IR LEDs on the 8RC
    // modules.  If you are using a 1RC (i.e. if there is no emitter pin),
    // or if you just want the emitters on all the time and don't want to
    // use an I/O pin to control it, use a value of 255 (QTR_NO_EMITTER_PIN).
    void init(unsigned char* pins, unsigned char numSensors,
          unsigned int timeout = 2000, unsigned char emitterPin = QTR_NO_EMITTER_PIN);



  private:

    // Reads the sensor values into an array. There *MUST* be space
    // for as many values as there were sensors specified in the constructor.
    // Example usage:
    // unsigned int sensor_values[8];
    // sensors.read(sensor_values);
    // The values returned are a measure of the reflectance in microseconds.
    void readPrivate(unsigned int *sensor_values);
};



// Object to be used for QTR-1A and QTR-8A sensors
class mechabotrushv2 : public QTRSensors
{
  public:

    // if this constructor is used, the user must call init() before using
    // the methods in this class
    
    
    void motorsteer(char*,int);
    void motortank(char*,int,char*,int);
    int ultrasonic();
    void RelaySwitch(int);
    void megablink(int);
    void knightrider(int);
    void MazeRunner(int);
  
    void followline(int,char*);
    void LED(int,char*);
    int ir_sense(int);
	int Pbutton();
	//Infrared LineFollow
	int data ;




//Init extra pin

int R, L; // IR Sensor









//char BTdata; // variable for bluetooth
long dur1;
int dis1;

	mechabotrushv2();
  // library-accessible "private" interface

    // this constructor just calls init()
    mechabotrushv2(unsigned char* pins,
        unsigned char numSensors, unsigned char numSamplesPerSensor = 4,
        unsigned char emitterPin = 255);

    // the array 'pins' contains the Arduino analog pin assignment for each
    // sensor.  For example, if pins is {0, 1, 7}, sensor 1 is on
    // Arduino analog input 0, sensor 2 is on Arduino analog input 1,
    // and sensor 3 is on Arduino analog input 7.

    // 'numSensors' specifies the length of the 'analogPins' array (i.e. the
    // number of QTR-A sensors you are using).  numSensors must be
    // no greater than 16.

    // 'numSamplesPerSensor' indicates the number of 10-bit analog samples
    // to average per channel (i.e. per sensor) for each reading.  The total
    // number of analog-to-digital conversions performed will be equal to
    // numSensors*numSamplesPerSensor.  Note that it takes about 100 us to
    // perform a single analog-to-digital conversion, so:
    // if numSamplesPerSensor is 4 and numSensors is 6, it will take
    // 4 * 6 * 100 us = ~2.5 ms to perform a full readLine().
    // Increasing this parameter increases noise suppression at the cost of
    // sample rate.  The recommended value is 4.

    // 'emitterPin' is the Arduino pin that controls the IR LEDs on the 8RC
    // modules.  If you are using a 1RC (i.e. if there is no emitter pin),
    // or if you just want the emitters on all the time and don't want to
    // use an I/O pin to control it, use a value of 255 (QTR_NO_EMITTER_PIN).
    void init(unsigned char* analogPins, unsigned char numSensors,
        unsigned char numSamplesPerSensor = 4, unsigned char emitterPin = QTR_NO_EMITTER_PIN);



  private:

    // Reads the sensor values into an array. There *MUST* be space
    // for as many values as there were sensors specified in the constructor.
    // Example usage:
    // unsigned int sensor_values[8];
    // sensors.read(sensor_values);
    // The values returned are a measure of the reflectance in terms of a
    // 10-bit ADC average with higher values corresponding to lower
    // reflectance (e.g. a black surface or a void).
    void readPrivate(unsigned int *sensor_values);

    unsigned char _numSamplesPerSensor;
};




#endif

