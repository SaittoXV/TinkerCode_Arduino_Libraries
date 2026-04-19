//Line Follow with Tuah. Black line on White
//
//This code is created for Tuah robot developed for Petrosain Robotic Challenge 2018.
//Created by Fauzan Khairi Che Harun
// 2018

#include <Tuah.h> //include Tuah library

tuah bot((unsigned char[]) { A4, A3, A2, A1, A0} ,5, 4, QTR_NO_EMITTER_PIN);


void setup() {

 for (int i=1;i<1000;i++){
 bot.calibrate(); //run threshold function with 1000 samples
}

}


void loop() {


    bot.pid_line(150, 150, 100, 255, 0.05,0.08, 0, 500);
  }
