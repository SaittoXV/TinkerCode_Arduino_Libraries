//This examples show the LED Function of Tuah bot
//LED L1 and L5 is UNUSABLE when Arduino Nano SerialPort is used.
//
//This code is created for Tuah robot developed
//Created by Fauzan Khairi Che Harun
// 2018


 

#include <TuahMini.h> //include Tuah library


tuahmini bot((unsigned char[]) { A6, A3, A2, A1, A0} ,5, 4, QTR_NO_EMITTER_PIN);  //initialize tuah robot with QTR Sensor Library (5 sensor 4 samples)


void setup() {
  
}

void loop() {
bot.megablink(300);  //blink all 5 leds with delay specified - megablink(int delay)
delay(2000);
bot.knightrider(200); // control speed of light - knightrider(int delay)
delay(2000);
}
