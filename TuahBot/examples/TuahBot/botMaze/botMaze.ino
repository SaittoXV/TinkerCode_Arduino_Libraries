//Wall Follower with infrared
//
//This code is created for Tuah robot developed for Petrosain Robotic Challenge 2018.
//Created by Fauzan Khairi Che Harun
// 2018

#include <Tuah.h> //include Tuah library


tuah bot((unsigned char[]) { A4, A3, A2, A1, A0} ,5, 4, QTR_NO_EMITTER_PIN);  //initialize tuah robot with QTR Sensor Library (5 sensor 4 samples)


void setup() {
  


}

void loop() {

bot.MazeRunner(200); //trigger maze runner with at PIN 9 and 10 (connected to obstacle sensor)

}
