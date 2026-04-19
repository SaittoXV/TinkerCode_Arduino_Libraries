/*
 * Maker Kit library support routines
 * (C) Mohd Ridzuan 2020
 * Last edit: 19/04/2020
 */

#ifndef __MakerKit_H__
#define __MakerKit_H__

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define DHTLIB_OK				0
#define DHTLIB_ERROR_CHECKSUM	-1
#define DHTLIB_ERROR_TIMEOUT	-2

class dht11
{
public:
    int read(int pin);
	int humidity;
	int temperature;
};

int ultrasonic(byte trig,byte echo);
float lm35_celsius(byte pin);
float tmp35_celsius(byte pin);
 
#endif
