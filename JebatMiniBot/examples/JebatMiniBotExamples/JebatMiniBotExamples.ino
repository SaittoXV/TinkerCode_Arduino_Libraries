//Complete Example including Bluetooth for use with TuahMini Library
//This code is created for Tuah robot developed for Petrosain Robotic Challenge 2018.
//Created by Fauzan Khairi Che Harun
// 2018



int speedvalue;


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
//const int bluetoothrx=1;
//const int bluetoothtx =0;

#include <TuahMini.h>
#include <SoftwareSerial.h>

SoftwareSerial bluez(bluetoothrx, bluetoothtx); // RX, TX

char BTdata; // variable for bluetooth


tuahmini bot((unsigned char[]) { A6, A3, A2, A1, A0} ,5, 4, QTR_NO_EMITTER_PIN);  //initialize tuah robot with QTR Sensor Library (5 sensor 4 samples)


void setup()
{

  bluez.begin(9600);

  speedvalue = 200;
}


void loop()
{
  if (bluez.available()) {
    BTdata = bluez.read();
  }

  if (BTdata == 'q')
  {
    //Get Speed variable from Tuah Apps when 'q' is setting is long pressed
   // while (!bluez.available()) {}

    if (bluez.available()) {
    int speedy = bluez.read();
    speedvalue = speedy;
    if (speedvalue == 0) speedvalue = 255;
}
    
  }

  if (BTdata == 'f')
  {
    bot.motorsteer("forward", speedvalue);
  }
  else if (BTdata == 'l')
  {
    bot.motorsteer("left", speedvalue);
  }
  else if (BTdata == 'r')
  {
    bot.motorsteer("right", speedvalue);
  }
  else if (BTdata == 'b')
  {
    bot.motorsteer("backward", speedvalue);
  }

  else if (BTdata == '1')
  {
    bot.RelaySwitch(300);//red
  }
  else if (BTdata == '2')
  {
    bot.pid_line(150, 150, 100, 255, 0.05,0.08, 0, 500);

  }
  else if (BTdata == '3')
  {
    bot.calibrate(1000);//blue
  }
  else if (BTdata == '4')
  {
    bot.MazeRunner(200);//green
  }
  else if (BTdata == '5')
  {
    bot.megablink(speedvalue);    //knightrider(delay speed);
  }

  else if (BTdata == '6')
  {
    bot.knightrider(speedvalue);    //knightrider(delay speed);
  }
  else {
    bot.motorsteer("stop", 0);
  }

}


