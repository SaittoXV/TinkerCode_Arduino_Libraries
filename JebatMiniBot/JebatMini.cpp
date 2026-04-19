/*
  jebatMini.h - Library for jebat Mini
  Copyright (c) 2018 Fauzan Khairi Che Harun.  All right reserved.
*/
/*
  QTRSensors.cpp - Arduino library for using Pololu QTR reflectance
    sensors and reflectance sensor arrays: QTR-1A, QTR-8A, QTR-1RC, and
    QTR-8RC.  The object used will determine the type of the sensor (either
    QTR-xA or QTR-xRC).  Then simply specify in the constructor which
    Arduino I/O pins are connected to a QTR sensor, and the read() method
    will obtain reflectance measurements for those sensors.  Smaller sensor
    values correspond to higher reflectance (e.g. white) while larger
    sensor values correspond to lower reflectance (e.g. black or a void).

    * QTRSensorsRC should be used for QTR-1RC and QTR-8RC sensors.
    * QTRSensorsAnalog should be used for QTR-1A and QTR-8A sensors.
*/

/*
 * Written by Ben Schmidel et al., October 4, 2010.
 * Copyright (c) 2008-2012 Pololu Corporation. For more information, see
 *
 *   http://www.pololu.com
 *   http://forum.pololu.com
 *   http://www.pololu.com/docs/0J19
 *
 * You may freely modify and share this code, as long as you keep this
 * notice intact (including the two links above).  Licensed under the
 * Creative Commons BY-SA 3.0 license:
 *
 *   http://creativecommons.org/licenses/by-sa/3.0/
 *
 * Disclaimer: To the extent permitted by law, Pololu provides this work
 * without any warranty.  It might be defective, in which case you agree
 * to be responsible for all resulting costs and damages.
 */

#include <stdlib.h>
#include "jebatMini.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(5, 16, NEO_GRB + NEO_KHZ800);


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
// Derived Analog class constructors
jebatmini::jebatmini()
{
    calibratedMinimumOn = 0;
    calibratedMaximumOn = 0;
    calibratedMinimumOff = 0;
    calibratedMaximumOff = 0;
    _pins = 0;
}


jebatmini::jebatmini(unsigned char* pins,
  unsigned char numSensors, unsigned char numSamplesPerSensor,
  unsigned char emitterPin)
{
      calibratedMinimumOn = 0;
    calibratedMaximumOn = 0;
    calibratedMinimumOff = 0;
    calibratedMaximumOff = 0;
    _pins = 0;

    init(pins, numSensors, numSamplesPerSensor, emitterPin);

  
  //initialize bluetooth




  //initialize LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  //initialize button
  pinMode(zbutton, INPUT);




  //initialize motor
  pinMode (PWM1, OUTPUT);
  pinMode (PWM2, OUTPUT);
  pinMode (dir1, OUTPUT);
  pinMode (dir2, OUTPUT);

  //TUrn off LED during start
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(PWM1, LOW);
  digitalWrite(PWM2, LOW);
  
  
  
    pixels.begin();
  
  
  

}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void jebatmini::knightrider(int delayx,int r, int g, int b)
{
for(int i=0;i<5;i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayx);
    }


}


void jebatmini::setPixyColor(int pin,int color)
{
    pixels.setPixelColor(pin, color); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
        pixels.show(); // This sends the updated pixel color to the hardware.

}

void jebatmini::clearPixyColor()
{
    pixels.clear(); 
}

void jebatmini::brightnessPixyColor(int percent)
{
	int bright=map(percent,0,100,0,255);
	
    pixels.setBrightness(bright); 
    pixels.show(); 
}


int jebatmini::ultrasonic()
{


}

void jebatmini::RelaySwitch(int delayx)
{
  digitalWrite(Relay, HIGH);   //Turn off relay
  delay(delayx);
  digitalWrite(Relay, LOW);    //Turn on relay
  //delay(2000);

}






void jebatmini::MazeRunner (int speed)
{


    R = digitalRead(irR); //RIGHT
    L = digitalRead(irL); //LEFT

    if ((R == 1) && (L == 1))
    {
      motorsteer("forward", speed);
    }

    else if ((R == 0) && (L == 1))
    {
      motortank("forward", speed, "backward",speed);
    }

    else if ((R == 1) && (L == 0))
    {
      motortank("forward", speed,"backward",speed);
    }

    else if ((R == 0) && (L == 0))
    {
      motorsteer("forward", speed);
    }

    else
    {
      motorsteer("stop", 0);
    }

  
}



void jebatmini::motortank(char *directionL,  int powerL, char *directionR,int powerR)
{

  if (directionL == "forward")
  {
    digitalWrite(dir1, HIGH);
  }

  else if (directionL == "backward")
  {
    digitalWrite(dir1, LOW);
  }

  if (directionR == "forward")
  {
    digitalWrite(dir2, HIGH);
  }

  else if (directionR == "backward")
  {
    digitalWrite(dir2, LOW);
  }

  if (PWM1 == 0 && PWM2 == 0) {



  }

  analogWrite(PWM1, powerL);
  analogWrite(PWM2, powerR);


}



void jebatmini::motorsteer(char* robotdirection, int power)
{

  if (robotdirection == "forward")
  {
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, HIGH);
    analogWrite(PWM1, power);
    analogWrite(PWM2, power);
  }

  else if (robotdirection == "right")
  {
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, HIGH);
    analogWrite(PWM1, power );
    analogWrite(PWM2, power / 2);
  }

  else if (robotdirection == "left")
  {
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, HIGH);
    analogWrite(PWM1, power/2);
    analogWrite(PWM2, power);
  }

  else if (robotdirection == "backward")
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    analogWrite(PWM1, power);
    analogWrite(PWM2, power);
  }

  else
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
  }



}

void jebatmini::megablink(int del,int r,int g, int b)
{
    for(int i=0;i<5;i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
  }
  delay(del);                       // wait for a second
  for(int i=0;i<5;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
  }
  delay(del);                       // wait for a second
}





void jebatmini::LED(int l,char *stat)
{

if (stat=="ON"){
digitalWrite(l, LOW);
}

else if (stat=="OFF")
{
digitalWrite(l, HIGH);
}

}

int jebatmini::ir_sense(int l)
{
int sensordata= analogRead(l);
return sensordata;
}

int jebatmini::Pbutton()
{
int buttondata= digitalRead(8);
return buttondata;
}



// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

// Base class data member initialization (called by derived class init())
void QTRSensors::init(unsigned char *pins, unsigned char numSensors,
  unsigned char emitterPin)
{
    calibratedMinimumOn=0;
    calibratedMaximumOn=0;
    calibratedMinimumOff=0;
    calibratedMaximumOff=0;

    _lastValue=0; // assume initially that the line is left.

    if (numSensors > QTR_MAX_SENSORS)
        _numSensors = QTR_MAX_SENSORS;
    else
        _numSensors = numSensors;

    if (_pins == 0)
    {
        _pins = (unsigned char*)malloc(sizeof(unsigned char)*_numSensors);
        if (_pins == 0)
            return;
    }

    unsigned char i;
    for (i = 0; i < _numSensors; i++)
    {
        _pins[i] = pins[i];
    }

    _emitterPin = emitterPin;
}


// Reads the sensor values into an array. There *MUST* be space
// for as many values as there were sensors specified in the constructor.
// Example usage:
// unsigned int sensor_values[8];
// sensors.read(sensor_values);
// The values returned are a measure of the reflectance in abstract units,
// with higher values corresponding to lower reflectance (e.g. a black
// surface or a void).
void QTRSensors::read(unsigned int *sensor_values, unsigned char readMode)
{
    unsigned int off_values[QTR_MAX_SENSORS];
    unsigned char i;

    if(readMode == QTR_EMITTERS_ON || readMode == QTR_EMITTERS_ON_AND_OFF)
        emittersOn();
    else
        emittersOff();

    readPrivate(sensor_values);
    emittersOff();

    if(readMode == QTR_EMITTERS_ON_AND_OFF)
    {
        readPrivate(off_values);

        for(i=0;i<_numSensors;i++)
        {
            sensor_values[i] += _maxValue - off_values[i];
        }
    }
}


// Turn the IR LEDs off and on.  This is mainly for use by the
// read method, and calling these functions before or
// after the reading the sensors will have no effect on the
// readings, but you may wish to use these for testing purposes.
void QTRSensors::emittersOff()
{
    if (_emitterPin == QTR_NO_EMITTER_PIN)
        return;
    pinMode(_emitterPin, OUTPUT);
    digitalWrite(_emitterPin, LOW);
    delayMicroseconds(200);
}

void QTRSensors::emittersOn()
{
    if (_emitterPin == QTR_NO_EMITTER_PIN)
        return;
    pinMode(_emitterPin, OUTPUT);
    digitalWrite(_emitterPin, HIGH);
    delayMicroseconds(200);
}

// Resets the calibration.
void QTRSensors::resetCalibration()
{
    unsigned char i;
    for(i=0;i<_numSensors;i++)
    {
        if(calibratedMinimumOn)
            calibratedMinimumOn[i] = _maxValue;
        if(calibratedMinimumOff)
            calibratedMinimumOff[i] = _maxValue;
        if(calibratedMaximumOn)
            calibratedMaximumOn[i] = 0;
        if(calibratedMaximumOff)
            calibratedMaximumOff[i] = 0;
    }
}

// Reads the sensors 10 times and uses the results for
// calibration.  The sensor values are not returned; instead, the
// maximum and minimum values found over time are stored internally
// and used for the readCalibrated() method.
void QTRSensors::calibrate(unsigned char readMode)
{
    if(readMode == QTR_EMITTERS_ON_AND_OFF || readMode == QTR_EMITTERS_ON)
    {
        calibrateOnOrOff(&calibratedMinimumOn,
                         &calibratedMaximumOn,
                         QTR_EMITTERS_ON);
    }


    if(readMode == QTR_EMITTERS_ON_AND_OFF || readMode == QTR_EMITTERS_OFF)
    {
        calibrateOnOrOff(&calibratedMinimumOff,
                         &calibratedMaximumOff,
                         QTR_EMITTERS_OFF);
    }
}

void QTRSensors::calibrateOnOrOff(unsigned int **calibratedMinimum,
                                        unsigned int **calibratedMaximum,
                                        unsigned char readMode)
{
    int i;
    unsigned int sensor_values[16];
    unsigned int max_sensor_values[16];
    unsigned int min_sensor_values[16];

    // Allocate the arrays if necessary.
    if(*calibratedMaximum == 0)
    {
        *calibratedMaximum = (unsigned int*)malloc(sizeof(unsigned int)*_numSensors);

        // If the malloc failed, don't continue.
        if(*calibratedMaximum == 0)
            return;

        // Initialize the max and min calibrated values to values that
        // will cause the first reading to update them.

        for(i=0;i<_numSensors;i++)
            (*calibratedMaximum)[i] = 0;
    }
    if(*calibratedMinimum == 0)
    {
        *calibratedMinimum = (unsigned int*)malloc(sizeof(unsigned int)*_numSensors);

        // If the malloc failed, don't continue.
        if(*calibratedMinimum == 0)
            return;

        for(i=0;i<_numSensors;i++)
            (*calibratedMinimum)[i] = _maxValue;
    }

    int j;
    for(j=0;j<10;j++)
    {
        read(sensor_values,readMode);
        for(i=0;i<_numSensors;i++)
        {
            // set the max we found THIS time
            if(j == 0 || max_sensor_values[i] < sensor_values[i])
                max_sensor_values[i] = sensor_values[i];

            // set the min we found THIS time
            if(j == 0 || min_sensor_values[i] > sensor_values[i])
                min_sensor_values[i] = sensor_values[i];
        }
    }

    // record the min and max calibration values
    for(i=0;i<_numSensors;i++)
    {
        if(min_sensor_values[i] > (*calibratedMaximum)[i])
            (*calibratedMaximum)[i] = min_sensor_values[i];
        if(max_sensor_values[i] < (*calibratedMinimum)[i])
            (*calibratedMinimum)[i] = max_sensor_values[i];
    }
}


// Returns values calibrated to a value between 0 and 1000, where
// 0 corresponds to the minimum value read by calibrate() and 1000
// corresponds to the maximum value.  Calibration values are
// stored separately for each sensor, so that differences in the
// sensors are accounted for automatically.
void QTRSensors::readCalibrated(unsigned int *sensor_values, unsigned char readMode)
{
    int i;

    // if not calibrated, do nothing
    if(readMode == QTR_EMITTERS_ON_AND_OFF || readMode == QTR_EMITTERS_OFF)
        if(!calibratedMinimumOff || !calibratedMaximumOff)
            return;
    if(readMode == QTR_EMITTERS_ON_AND_OFF || readMode == QTR_EMITTERS_ON)
        if(!calibratedMinimumOn || !calibratedMaximumOn)
            return;

    // read the needed values
    read(sensor_values,readMode);

    for(i=0;i<_numSensors;i++)
    {
        unsigned int calmin,calmax;
        unsigned int denominator;

        // find the correct calibration
        if(readMode == QTR_EMITTERS_ON)
        {
            calmax = calibratedMaximumOn[i];
            calmin = calibratedMinimumOn[i];
        }
        else if(readMode == QTR_EMITTERS_OFF)
        {
            calmax = calibratedMaximumOff[i];
            calmin = calibratedMinimumOff[i];
        }
        else // QTR_EMITTERS_ON_AND_OFF
        {

            if(calibratedMinimumOff[i] < calibratedMinimumOn[i]) // no meaningful signal
                calmin = _maxValue;
            else
                calmin = calibratedMinimumOn[i] + _maxValue - calibratedMinimumOff[i]; // this won't go past _maxValue

            if(calibratedMaximumOff[i] < calibratedMaximumOn[i]) // no meaningful signal
                calmax = _maxValue;
            else
                calmax = calibratedMaximumOn[i] + _maxValue - calibratedMaximumOff[i]; // this won't go past _maxValue
        }

        denominator = calmax - calmin;

        signed int x = 0;
        if(denominator != 0)
            x = (((signed long)sensor_values[i]) - calmin)
                * 1000 / denominator;
        if(x < 0)
            x = 0;
        else if(x > 1000)
            x = 1000;
        sensor_values[i] = x;
    }

}


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
int QTRSensors::readLine(unsigned int *sensor_values,
    unsigned char readMode, unsigned char white_line)
{
    unsigned char i, on_line = 0;
    unsigned long avg; // this is for the weighted total, which is long
                       // before division
    unsigned int sum; // this is for the denominator which is <= 64000

    readCalibrated(sensor_values, readMode);

    avg = 0;
    sum = 0;

    for(i=0;i<_numSensors;i++) {
        int value = sensor_values[i];
        if(white_line)
            value = 1000-value;

        // keep track of whether we see the line at all
        if(value > 200) {
            on_line = 1;
        }

        // only average in values that are above a noise threshold
        if(value > 50) {
            avg += (long)(value) * (i * 1000);
            sum += value;
        }
    }

    if(!on_line)
    {
        // If it last read to the left of center, return 0.
        if(_lastValue < (_numSensors-1)*1000/2)
            return 0;

        // If it last read to the right of center, return the max.
        else
            return (_numSensors-1)*1000;

    }

    _lastValue = avg/sum;

    return _lastValue;
}



// Derived RC class constructors
QTRSensorsRC::QTRSensorsRC()
{
    calibratedMinimumOn = 0;
    calibratedMaximumOn = 0;
    calibratedMinimumOff = 0;
    calibratedMaximumOff = 0;
    _pins = 0;
}

QTRSensorsRC::QTRSensorsRC(unsigned char* pins,
  unsigned char numSensors, unsigned int timeout, unsigned char emitterPin)
{
    calibratedMinimumOn = 0;
    calibratedMaximumOn = 0;
    calibratedMinimumOff = 0;
    calibratedMaximumOff = 0;
    _pins = 0;

    init(pins, numSensors, timeout, emitterPin);
}


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
void QTRSensorsRC::init(unsigned char* pins,
    unsigned char numSensors, unsigned int timeout, unsigned char emitterPin)
{
    QTRSensors::init(pins, numSensors, emitterPin);

    _maxValue = timeout;
}


// Reads the sensor values into an array. There *MUST* be space
// for as many values as there were sensors specified in the constructor.
// Example usage:
// unsigned int sensor_values[8];
// sensors.read(sensor_values);
// ...
// The values returned are in microseconds and range from 0 to
// timeout (as specified in the constructor).
void QTRSensorsRC::readPrivate(unsigned int *sensor_values)
{
    unsigned char i;

    if (_pins == 0)
        return;

    for(i = 0; i < _numSensors; i++)
    {
        sensor_values[i] = _maxValue;
        digitalWrite(_pins[i], HIGH);   // make sensor line an output
        pinMode(_pins[i], OUTPUT);      // drive sensor line high
    }

    delayMicroseconds(10);              // charge lines for 10 us

    for(i = 0; i < _numSensors; i++)
    {
        pinMode(_pins[i], INPUT);       // make sensor line an input
        digitalWrite(_pins[i], LOW);        // important: disable internal pull-up!
    }

    unsigned long startTime = micros();
    while (micros() - startTime < _maxValue)
    {
        unsigned int time = micros() - startTime;
        for (i = 0; i < _numSensors; i++)
        {
            if (digitalRead(_pins[i]) == LOW && time < sensor_values[i])
                sensor_values[i] = time;
        }
    }
}






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
void jebatmini::init(unsigned char* pins,
    unsigned char numSensors, unsigned char numSamplesPerSensor,
    unsigned char emitterPin)
{
    QTRSensors::init(pins, numSensors, emitterPin);

    _numSamplesPerSensor = numSamplesPerSensor;
    _maxValue = 1023; // this is the maximum returned by the A/D conversion
}


// Reads the sensor values into an array. There *MUST* be space
// for as many values as there were sensors specified in the constructor.
// Example usage:
// unsigned int sensor_values[8];
// sensors.read(sensor_values);
// The values returned are a measure of the reflectance in terms of a
// 10-bit ADC average with higher values corresponding to lower
// reflectance (e.g. a black surface or a void).
void jebatmini::readPrivate(unsigned int *sensor_values)
{
    unsigned char i, j;

    if (_pins == 0)
        return;

    // reset the values
    for(i = 0; i < _numSensors; i++)
        sensor_values[i] = 0;

    for (j = 0; j < _numSamplesPerSensor; j++)
    {
        for (i = 0; i < _numSensors; i++)
        {
	        int calibrate= analogRead(_pins[i]); 
	        int val = map(calibrate, 0, 4095, 0, 1024);
	        sensor_values[i] += val;  // sensor_values[i] += analogRead(_pins[i]);


        }
    }

    // get the rounded average of the readings for each sensor
    for (i = 0; i < _numSensors; i++)
        sensor_values[i] = (sensor_values[i] + (_numSamplesPerSensor >> 1)) /
            _numSamplesPerSensor;
}

// the destructor frees up allocated memory
QTRSensors::~QTRSensors()
{
    if (_pins)
        free(_pins);
    if(calibratedMaximumOn)
        free(calibratedMaximumOn);
    if(calibratedMaximumOff)
        free(calibratedMaximumOff);
    if(calibratedMinimumOn)
        free(calibratedMinimumOn);
    if(calibratedMinimumOff)
        free(calibratedMinimumOff);
}



void QTRSensors::jebattillJunction(int lajul, int lajur, int speedturn, int sensorc, int inByte, float kp, float kd,int linef,int maxSpeed, int forwarddelay) 

{
    
	position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black
	if (inByte==0) //0=middle
	{
	while ((position!=2000) && ( sensorValues[0]<sensorc) && ( sensorValues[4]<sensorc))
	{
	position = readLine(sensorValues,1,linef);
       pid_line(lajur, lajul, speedturn, maxSpeed, kp, kd, 1, sensorc); 
	   }
	}
	else if (inByte==1) //1=left
	{
	while (position!=3000)
	{
	position = readLine(sensorValues,1,linef);
	       pid_line(lajur, lajul, speedturn, maxSpeed, kp, kd, 1, sensorc); 
	       }

	}
	else if (inByte==2) //2=right
	{
	
	while (position!=1000)	
	{
	position = readLine(sensorValues,1,linef);
	       pid_line(lajur, lajul, speedturn, maxSpeed, kp, kd, 1, sensorc); 
	       }

	}
	advance(lajur,lajul);
	delay(forwarddelay);
}

void QTRSensors::jebattillJunctionSimple(int laju, int inByte, float kp, float kd, int linef) 

{
    int sensorc= (calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
    int sensec[4];
    sensec[0]=(calibratedMaximumOn[0]+calibratedMinimumOn[0])/2;
    sensec[4]=(calibratedMaximumOn[4]+calibratedMinimumOn[4])/2;
    int basespeed=255;
    int lajur=laju;
    int lajul=laju;
    int speedturn=10;

	position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black
	if (inByte==0) //0=middle
	{
	while ((position!=2000) && ( sensorValues[0]<sensec[0]) && ( sensorValues[4]<sensec[4]))
	{
	position = readLine(sensorValues,1,linef);
       pid_line(lajur, lajul, speedturn, basespeed, kp, kd, 1, sensorc); 
	   }
	}
	else if (inByte==1) //1=left
	{
	while (position!=3000)
	{
	position = readLine(sensorValues,1,linef);
	       pid_line(lajur, lajul, speedturn, basespeed, kp, kd, 1, sensorc); 
	       }

	}
	else if (inByte==2) //2=right
	{
	
	while (position!=1000)	
	{
	position = readLine(sensorValues,1,linef);
	       pid_line(lajur, lajul, speedturn, basespeed, kp, kd, 1, sensorc); 
	       }

	}
}


void QTRSensors::jebatFinderW(int inByte, int inNext, int lajur, int lajul, float turn, int speedturn, float kp, float kd, int sensorc, int lajak, int dturn) // (type of junction, next robot action, robot speed, turn speed percentage)
{
    
	position = readLine(sensorValues,1,1); //0 black on white, 1 white on black
    
   switch (inByte)
   {
      case 1:    
     
     while (sensorValues[0] < sensorc || sensorValues[1] < sensorc || sensorValues[2] < sensorc)  //0=right, 4=left
     {
       pid_line(lajur, lajul, speedturn, 255, kp, kd, 1, sensorc); 
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }  
     //position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black   
     advance(lajur,lajul);
     delay(lajak);	  

      switch (inNext)
      {
        case 1:
         
		    advance(lajur*(turn/100),lajul*(turn/100));
            delay(dturn);
            stop();
        break;
        
        case 2:
        
            turn_R(lajur*(turn/10),lajul*(turn/100));
            delay(dturn);
            stop();
          break;
      
        case 3:
        
            turn_L(lajur*(turn/100),lajul*(turn/10));
           delay(dturn);
           stop();
        break;
      }
      break;
    
    case 2:    
      
       while (sensorValues[4] < sensorc || sensorValues[3] < sensorc || sensorValues[2] < sensorc) // 300
     {
        pid_line(lajur, lajul, speedturn, 255, kp, kd, 1, sensorc); 
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }
     
	 //position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black   
	 advance(lajur,lajul);
	 delay(lajak);	  
      
     switch (inNext)
      {
        case 1:
       advance(lajur*(turn/100),lajul*(turn/100));
            delay(dturn);
            stop();
        break;
        
       case 2:
        
          turn_R(lajur*(turn/10),lajul*(turn/100));
          delay(dturn);
          stop();
       
        break;
      
        case 3:
        
           turn_L(lajur*(turn/100),lajul*(turn/10));
           delay(dturn);
           stop();
        break;
      }
      break;
    
    case 3:   
   
        while (sensorValues[0] < sensorc || sensorValues[4] < sensorc || sensorValues[2] < sensorc || sensorValues[3] < sensorc || sensorValues[1] < sensorc)
     {
        pid_line(lajur, lajul, speedturn, 255, kp, kd, 1, sensorc); //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black)
     }
      //position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black   
     advance(lajur,lajul);
     delay(lajak);	  
	 
     switch (inNext)
      {
        case 1:
          advance(lajur*(turn/100),lajul*(turn/100));
            delay(dturn);
            stop();
        break;
        
        case 2:
        
           turn_R(lajur*(turn/10),lajul*(turn/100));
           delay(dturn);
           stop();
       
        break;
      
        case 3:
        
           turn_L(lajur*(turn/100),lajul*(turn/10));
           delay(dturn);
           stop();
        break;
      }
     break;
   
    } 
  }


void QTRSensors::jebatFinderB(int inByte, int inNext, int lajur, int lajul, float turn, int speedturn, float kp, float kd, int sensorc, int lajak, int dturn) // (type of junction, next robot action, robot speed, turn speed percentage)
{
    
	position = readLine(sensorValues,1,0); //0 black on white, 1 white on black
    
   switch (inByte)
   {
      case 1:    
     
     while (sensorValues[0] > sensorc || sensorValues[1] > sensorc || sensorValues[2] > sensorc)  //0=right, 4=left
     {
       pid_line(lajur, lajul, speedturn, 255, kp, kd, 0, sensorc); 
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }  
     //position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black   
     advance(lajur,lajul);
     delay(lajak);	  

      switch (inNext)
      {
        case 1:
         
		    advance(lajur*(turn/100),lajul*(turn/100));
            delay(dturn);
            stop();
        break;
        
        case 2:
        
            turn_R(lajur*(turn/10),lajul*(turn/100));
            delay(dturn);
            stop();
          break;
      
        case 3:
        
            turn_L(lajur*(turn/100),lajul*(turn/10));
           delay(dturn);
           stop();
        break;
      }
      break;
    
    case 2:    
      
       while (sensorValues[4] > sensorc || sensorValues[3] > sensorc || sensorValues[2] > sensorc) // 300
     {
        pid_line(lajur, lajul, speedturn, 255, kp, kd, 0, sensorc); 
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }
     
	 advance(lajur,lajul);
	 delay(lajak);	  
      
     switch (inNext)
      {
        case 1:
       advance(lajur*(turn/100),lajul*(turn/100));
            delay(dturn);
            stop();
        break;
        
       case 2:
        
          turn_R(lajur*(turn/10),lajul*(turn/100));
          delay(dturn);
          stop();
       
        break;
      
        case 3:
        
           turn_L(lajur*(turn/100),lajul*(turn/10));
           delay(dturn);
           stop();
        break;
      }
      break;
    
    case 3:   
   
     while (sensorValues[0] > sensorc || sensorValues[4] > sensorc || sensorValues[2] > sensorc || sensorValues[3] > sensorc || sensorValues[1] > sensorc)
     {
        pid_line(lajur, lajul, speedturn, 255, kp, kd, 0, sensorc); //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black)
     }
     advance(lajur,lajul);
     delay(lajak);	  
	 
     switch (inNext)
      {
        case 1:
          advance(lajur*(turn/100),lajul*(turn/100));
            delay(dturn);
            stop();
        break;
        
        case 2:
        
           turn_R(lajur*(turn/10),lajul*(turn/100));
           delay(dturn);
           stop();
       
        break;
      
        case 3:
        
           turn_L(lajur*(turn/100),lajul*(turn/10));
           delay(dturn);
           stop();
        break;
      }
     break;
   
    } 
    
    
  }


//black background, white line
void QTRSensors::jebatFinderBlack(int inByte, int inNext, int laju,int turnspeed, float kp, float kd,  int terus,int turndelay) // (type of junction, next robot action, robot speed, turn speed percentage)
{
    
    int sensorc= (calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
    int sensec[4];
    sensec[0]=(calibratedMaximumOn[0]+calibratedMinimumOn[0])/2;
    sensec[1]=(calibratedMaximumOn[1]+calibratedMinimumOn[1])/2;
    sensec[2]=(calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
    sensec[3]=(calibratedMaximumOn[3]+calibratedMinimumOn[3])/2;
    sensec[4]=(calibratedMaximumOn[4]+calibratedMinimumOn[4])/2;


    
    //Serial.println(sensorc);
    int basespeed=255;
    int lajur=laju;
    int lajul=laju;
//  int terus=100;
    int dturn=0;
    int turn=10;
	
	position = readLine(sensorValues,1,0);
    
    
    
    
    //Junction Right
   switch (inByte)
   {
      case 1:    
     
     while (sensorValues[0] > sensec[0] || sensorValues[1] > sensec[1] || sensorValues[2] > sensec[2])  //4=left, 0=right
     {

     pid_line(lajur, lajul, 10, 255, kp, kd, 0, sensorc); 
     
     
   
      
      
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }  
     
     
     
    
     advance(lajur,lajul);

     delay(terus);	  

//Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]<sensec[2]){
//	 position = readLine(sensorValues,1,0);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
	 if (inNext==2) {
		 while ((sensorValues[4]<sensec[4]) || (sensorValues[0]<sensec[0])){
		pid_line(lajur, lajul, 100, 255, kp, kd, 0, sensorc); 

	 }
	 break;
	 }
	 
	 
		 turn_at_center(inNext, turnspeed, 0, 1);
		 break;
    
        //Junction Left

    case 2:    
      
       while (sensorValues[4] > sensec[4] || sensorValues[3] > sensec[3] || sensorValues[2] > sensec[2]) // 300
     {
        pid_line(lajur, lajul, 100, 255, kp, kd, 0, sensorc); 
        

      
           }
     //Serial.println("im out");
//Allow robot to turn a little bit first to ensure on black line during this time
     
     advance(lajur,lajul);
     delay(terus);	
     
	 //Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]<sensec[2]){
//	 position = readLine(sensorValues,1,0);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
if (inNext==2) {
		 while ((sensorValues[4]<sensec[4]) || (sensorValues[0]<sensec[0])){
		pid_line(lajur, lajul, 100, 255, kp, kd, 0, sensorc); 
	 }
	 break;
	 }     
     
      turn_at_center(inNext, turnspeed, 0, 1);
	  break;
           
               //Junction Middle
  
    case 0:   

     
        while (sensorValues[0] > sensec[0] || sensorValues[4] > sensec[4] || sensorValues[2] > sensec[2] || sensorValues[3] > sensec[3] || sensorValues[1] > sensec[1])
     {
        pid_line(lajur, lajul, 100, 255, kp, kd, 0, sensorc); 
                Serial.print("         ");
      Serial.print(sensorValues[4]);
       Serial.print(".S5.");
      Serial.print(sensec[4]);
      Serial.print("         ");
      Serial.print(sensorValues[3]);
       Serial.print(".S4.");
      Serial.print(sensec[3]);
       Serial.print("         ");
      Serial.print(sensorValues[2]);
       Serial.print(".S3.");
      Serial.print(sensec[2]);
      Serial.print("         ");
      Serial.print(sensorValues[1]);
       Serial.print(".S2.");
      Serial.print(sensec[1]); 
       Serial.print("         ");
      Serial.print(sensorValues[0]);
       Serial.print(".S1.");
      Serial.println(sensec[0]);
     }
     advance(lajur,lajul);
     delay(terus);	  
     
     
	 //Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]<sensec[2]){
//	 position = readLine(sensorValues,1,0);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
	//detect sensor getting outside of line before turning at center to find new line


	 
	 
if (inNext==2) {
		 while ((sensorValues[4]<sensec[4]) || (sensorValues[0]<sensec[0])){
		pid_line(lajur, lajul, 100, 255, kp, kd, 0, sensorc); 
	 }
	 break;
	 }   
	 turn_at_center(inNext, turnspeed, 0, 1);
	 break;
	 
	 
	 
	 case 3:   

     
        while (sensorValues[0] > sensec[0] || sensorValues[4] > sensec[4]  )
     {
        pid_line(lajur, lajul, 100, 255, kp, kd, 0, sensorc); 
     }
     advance(lajur,lajul);
     delay(terus);	  
     
     
	 //Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]<sensec[2]){
//	 position = readLine(sensorValues,1,0);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
	//detect sensor getting outside of line before turning at center to find new line


	 
	 
 
	 turn_at_center(inNext, turnspeed, 0, 1);
	 break;
	 
	 
    } 

    
    
  }


void QTRSensors::jebatFinderWhite(int inByte, int inNext, int laju, int turnspeed, float kp, float kd, int terus, int turndelay) // (type of junction, next robot action, robot speed, turn speed percentage)
{
    
    int sensorc= (calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
    int sensec[4];
    sensec[0]=(calibratedMaximumOn[0]+calibratedMinimumOn[0])/2;
    sensec[1]=(calibratedMaximumOn[1]+calibratedMinimumOn[1])/2;
    sensec[2]=(calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
    sensec[3]=(calibratedMaximumOn[3]+calibratedMinimumOn[3])/2;
    sensec[4]=(calibratedMaximumOn[4]+calibratedMinimumOn[4])/2;
	//position = readLine(sensorValues,1,1); //0 black on white, 1 white on black


    
    //Serial.println(sensorc);
    int basespeed=255;
    int lajur=laju;
    int lajul=laju;
//  int terus=100;
    int dturn=0;
    int turn=10;

	//position = readCalibrated(sensorValues,0); //0 black on white, 1 white on black
    
    
    //Junction Right
   switch (inByte)
   {
      case 1:    
     
     while (sensorValues[0] < sensec[0]|| sensorValues[1] < sensec[1] || sensorValues[2] < sensec[2])  //4=left, 0=right
     {

     pid_line(lajur, lajul, 10, 255, kp, kd, 1, sensorc); 
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }  

     
    
     advance(lajur,lajul);

     delay(terus);	  

//Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]>sensec[2]){
//		 position = readLine(sensorValues,1,1);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
	 if (inNext==2) {
		 while ((sensorValues[4]>sensec[4]) || (sensorValues[0]>sensec[0])){
		pid_line(lajur, lajul, 100, 255, kp, kd, 1, sensorc); 

	 }
	 break;
	 }
	 
	 
		 turn_at_center(inNext, turnspeed, 0, 0);
		 break;
    
        //Junction Left

    case 2:    
      
       while (sensorValues[4] < sensec[4] || sensorValues[3] < sensec[3] || sensorValues[2] < sensec[2]) // 300
     {
        pid_line(lajur, lajul, 100, 255, kp, kd, 1, sensorc); 
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }
     
//Allow robot to turn a little bit first to ensure on black line during this time
     
     advance(lajur,lajul);
     delay(terus);	
     
	 //Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]>sensec[2]){
//		 position = readLine(sensorValues,1,1);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
if (inNext==2) {
		 while ((sensorValues[4]>sensec[4]) || (sensorValues[0]>sensec[0])){
		pid_line(lajur, lajul, 100, 255, kp, kd, 1, sensorc); 
	 }
	 break;
	 }     
     
      turn_at_center(inNext, turnspeed, 0, 0);
	  break;
           
               //Junction Middle
  
    case 0:   

     
        while (sensorValues[0] < sensec[0] || sensorValues[4] < sensec[4] || sensorValues[2] < sensec[2] || sensorValues[3] < sensec[3] || sensorValues[1] < sensec[1])
     {
        pid_line(lajur, lajul, 100, 255, kp, kd, 1, sensorc); 

     }
      //position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black   
     advance(lajur,lajul);
     delay(terus);	  
     
     
	 //Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]>sensec[2]){
//		 position = readLine(sensorValues,1,1);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
	//detect sensor getting outside of line before turning at center to find new line


	 
	 
if (inNext==2) {
		 while ((sensorValues[4]>sensec[4]) || (sensorValues[0]>sensec[0])){
		pid_line(lajur, lajul, 100, 255, kp, kd, 1, sensorc); 
	 }
	 break;
	 }   
	 turn_at_center(inNext, turnspeed, 0, 0);
	 break;
	 
	 //middleside
	 case 3:   

     
        while (sensorValues[0] < sensec[0] || sensorValues[4] < sensec[4]  )
     {
        pid_line(lajur, lajul, 100, 255, kp, kd, 1, sensorc); 
        Serial.print(sensorValues[4]);
       Serial.print(".S5.");
      Serial.print(sensec[4]);
      Serial.print("         ");
      Serial.print(sensorValues[3]);
       Serial.print(".S4.");
      Serial.print(sensec[3]);
       Serial.print("         ");
      Serial.print(sensorValues[2]);
       Serial.print(".S3.");
      Serial.print(sensec[2]);
      Serial.print("         ");
      Serial.print(sensorValues[1]);
       Serial.print(".S2.");
      Serial.print(sensec[1]); 
       Serial.print("         ");
      Serial.print(sensorValues[0]);
       Serial.print(".S1.");
      Serial.println(sensec[0]);
     }
      //position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black   
     advance(lajur,lajul);
     delay(terus);	  
     
     
	 //Allow robot to turn a little bit first to ensure on black line during this time

//	 while(sensorValues[2]>sensec[2]){
//		 position = readLine(sensorValues,1,1);
		 if (inNext==1) {turn_R_center(turnspeed);delay(turndelay); }
	 else if (inNext==0) {turn_L_center(turnspeed);delay(turndelay);}
	 
//	 }
	 
	//detect sensor getting outside of line before turning at center to find new line


	 
	 

	 turn_at_center(inNext, turnspeed, 0, 0);
	 break;
	 
	 
    } 
  }


void QTRSensors::turn_at_center(int direction, int speed,int sensorc, int linef)  //linef 0 for black on white 
{
	
	//int sensor1= (calibratedMaximumOn[1]+calibratedMinimumOn[1])/2;
	//int sensor3= (calibratedMaximumOn[3]+calibratedMinimumOn[3])/2;
	int sensecenter=(calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
	position = readLine(sensorValues,1,linef);

	
	
	
	
	if (linef==1){
		
		//left
	if (direction==1){
	position = readLine(sensorValues,1,1);
	while(sensorValues[2]>sensecenter) {
	position = readLine(sensorValues,1,1);
	turn_R_center(speed);
	}
	}
	//right
	if (direction==0){
	position = readLine(sensorValues,1,1);
	while(sensorValues[2]>sensecenter) {
	position = readLine(sensorValues,1,1);
	turn_L_center(speed);
	}
	}
		
		
	} else if (linef==0){
		
		
			//left
	if (direction==1){
	position = readLine(sensorValues,1,0);
	while(sensorValues[2]<sensecenter) {
	position = readLine(sensorValues,1,0);
	turn_R_center(speed);
	}
	}
	//right
	if (direction==0){
	position = readLine(sensorValues,1,0);
	while(sensorValues[2]<sensecenter) {
	position = readLine(sensorValues,1,0);
	turn_L_center(speed);
	}
	}
	
		}
	
	
	
	
	
	
	
	
	
	stop();
}

void QTRSensors::jebatDtracer(int lajur, int lajul, int speedturn, float kp, float kd, int sensorc, int linef, int dtracer) // (type of junction, next robot action, robot speed, turn speed percentage)
{
    long currentmillis = millis();
	while (millis() - currentmillis < dtracer)  
     {
       pid_line(lajur, lajul, speedturn, 255, kp, kd, linef, sensorc); 
      //rightb=100, leftb=100, speedturn=150, maxspeed=200, Kp=0.01, Kd=0.05, line=0 black on white, 1 white on black, sensor turn value
     }  
     stop();
}


void QTRSensors::jebatflineW(int lajur, int lajul, int sensorc, int linef) // (right speed, left speed, sensor, line format)
{
	sensorc =(calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
    position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black
	
	while (sensorValues[2] > sensorc)
     {
        position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black
		advance(lajur,lajul);
     }  
     stop();
}

void QTRSensors::jebatflineB(int lajur, int lajul, int sensorc, int linef) // (right speed, left speed, sensor, line format)
{
	sensorc =(calibratedMaximumOn[2]+calibratedMinimumOn[2])/2;
    position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black
	
	while (sensorValues[2] < sensorc)
     {
        position = readLine(sensorValues,1,linef); //0 black on white, 1 white on black
		advance(lajur,lajul);
     }  
     stop();
}


void QTRSensors::pid_line(int right_base, int left_base, int speedturn, int maxSpeed, float Kp, float Kd, int line_format, int senspeed)
{
    // Position of robot through QTRlibrary

 position = readLine(sensorValues,1,line_format); //0 black on white, 1 white on black
// LEDsense(position); 

    
  int error = position-2000;  // error

  //////////// speed correction via PID
  int correct_speed = Kp * error + Kd*(error - last_error);  //correction speed
  last_error = error; // lasterror = error
    
   //////////// Exact speed settings to be applied to the motors
   right_motor_pwm = right_base + correct_speed  ; //right motor
   left_motor_pwm = left_base - correct_speed  ; //left motor
  
   if (right_motor_pwm < 0)
    right_motor_pwm = 0;
  if (left_motor_pwm < 0)
    left_motor_pwm = 0;

    right_motor_pwm=constrain(right_motor_pwm,0,maxSpeed);
    left_motor_pwm=constrain(left_motor_pwm,0,maxSpeed);

      advance(right_motor_pwm,left_motor_pwm);
      
  //   Make the bottom line active to show error on serial monitor, right and left motor speed values
  //   Serial.print(error);  Serial.print(" "); Serial.print(right_motor_pwm); Serial.print(" "); Serial.println(left_motor_pwm); delay(100);  
}




void QTRSensors::LEDsense(int positionx)

{
 switch (positionx)
   {
      case 0:     digitalWrite(led1, LOW);
      break;
      case 1000:   digitalWrite(led2, LOW);
      break;
      case 2000:   digitalWrite(led3, LOW);
      break;
      case 3000:   digitalWrite(led4, LOW);
      break;
      case 4000:   digitalWrite(led5, LOW);
      break;
	  default:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    
    break;
      }
}



void QTRSensors::Motor(int M1, int M2, int MD1, int MD2)

{
  pinMode(M1, OUTPUT);
  _pin1 = M1;
  pinMode(M2, OUTPUT);
  _pin2 = M2;
  pinMode(MD1, OUTPUT);
  _pin3 = MD1;
  pinMode(MD2, OUTPUT);
  _pin4 = MD2;
}

void QTRSensors::stop()
{
  digitalWrite(_pin1,LOW);
  digitalWrite(_pin2,LOW);
}


void QTRSensors::advance(char a, char b)
{
  analogWrite (_pin1,a); //PWM Speed Control
  digitalWrite(_pin3,HIGH);
  analogWrite (_pin2,b);
  digitalWrite(_pin4,HIGH);
  
}

void QTRSensors::reverse(char a, char b)
{
  analogWrite (_pin1,a);
  digitalWrite(_pin3,LOW);
  analogWrite (_pin2,b);
  digitalWrite(_pin4,LOW);
}


void QTRSensors::turn_L(char a, char b)
{
  analogWrite (_pin1,a);
  digitalWrite(_pin3,HIGH);
  analogWrite (_pin2,b);
  digitalWrite(_pin4,HIGH);
}

void QTRSensors::turn_R(char a, char b)
{
 analogWrite (_pin1,a);
 digitalWrite(_pin3,HIGH);
 analogWrite (_pin2,b);
 digitalWrite(_pin4,HIGH);
  
}

void QTRSensors::turn_R_center(char a)
{
 analogWrite (_pin1,a);
 digitalWrite(_pin3,LOW);
 analogWrite (_pin2,a);
 digitalWrite(_pin4,HIGH);
  
}

void QTRSensors::turn_L_center(char a)
{
 analogWrite (_pin1,a);
 digitalWrite(_pin3,HIGH);
 analogWrite (_pin2,a);
 digitalWrite(_pin4,LOW);
  
}


