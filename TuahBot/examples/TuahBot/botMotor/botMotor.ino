//This examples shows example how to move steer or tank for Tuah bot
//
//This code is created for Tuah robot developed for Petrosain Robotic Challenge 2018.
//Created by Fauzan Khairi Che Harun
// 2018

#include <Tuah.h> //include Tuah library


tuah bot((unsigned char[]) { A4, A3, A2, A1, A0} ,5, 4, QTR_NO_EMITTER_PIN);  //initialize tuah robot with QTR Sensor Library (5 sensor 4 samples)


void setup() {
  
}

void loop() {

bot.motorsteer("forward",200); //control direction and motor speed .  - motorsteer(char direction{forward, back, left, right, stop}, int speed{0-255})
delay(1000);
bot.motorsteer("backward",100); //control direction and motor speed .  - motorsteer(char direction{forward, back, left, right, stop}, int speed{0-255})
delay(1000);
bot.motorsteer("left",200); //control direction and motor speed .  - motorsteer(char direction{forward, back, left, right, stop}, int speed{0-255})
delay(2000);
bot.motorsteer("right",100); //control direction and motor speed .  - motorsteer(char direction{forward, back, left, right, stop}, int speed{0-255})
delay(3000);
bot.motorsteer("stop",0);
delay(1000);



bot.motortank("forward","backward",200,200);  //control direction and motor speed motortank(char direction left motor, char direction right motor, int speed motor left, int speed motor right)
delay(2000);
bot.motortank("forward","forward",100,255);
delay(2000);
}
