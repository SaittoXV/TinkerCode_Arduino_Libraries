//Complete Example including Bluetooth for use with Tuah Library
//This code is created for Tuah robot developed for Petrosain Robotic Challenge 2018.
//Created by Fauzan Khairi Che Harun
// 2018
int speedvalue;
// These Wiring API is already defined in the library. Please don't comment out the wiring API. 
// There are for guidance only.
//The Wiring API here is only for reference. These has been declared in the library. Please don't comment this out
////MOTOR1
//const int PWM1 = 6;
//const int dir1 = 2;
////MOTOR2
//const int PWM2 = 5;
//const int dir2 = 3;
//
////Button Init
//const int zbutton = 8;
//
////LED Init
//const int led1 = 11;
//const int led2 = 13;
//const int led3 = 7;
//const int led4 = 4;
//const int led5 = 12;
//
////Infrared LineFollow
//
//const int s1 = A0;
//const int s2 = A1;
//const int s3 = A2;
//const int s4 = A3;
//const int s5 = A6;
//
////Init extra pin
//const int irR = 9;//need to double check
//const int irL = 10;
//const int Relay = 9;
//
////Init Ultrasound
//const int Ltrig = A2;
//const int Lecho = A1;
//const int bluetoothrx=0;
//const int bluetoothtx=0;


#include <JebatMini.h>
#include <SoftwareSerial.h>

SoftwareSerial bluez(bluetoothrx, bluetoothtx); // RX, TX

char BTdata; // variable for bluetooth


jebatmini bot((unsigned char[]) { 35, 33, 22, 34, 25} ,5, 23, QTR_NO_EMITTER_PIN);  //initialize tuah robot with QTR Sensor Library (5 sensor 4 samples)


void setup()
{

  bluez.begin(9600);
  speedvalue = 200;
}


void loop()
{

 bot.LED(led4,"ON");
 delay(100);
 bot.LED(led4,"OFF");
 delay(100);
 
}


