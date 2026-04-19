//
//This code is created for Tuah robot developed for Petrosain Robotic Challenge 2018.
//Created by Fauzan Khairi Che Harun
// 2018

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(12, 11); // RX | TX

void setup()
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
// BTSerial.write("AT\n\r");
 
 }

void loop()
{
  //char newname[16]="AT+NAME=Tuah-001";
  // Keep reading from HC-05 and send to Arduino Serial Monitor
 
  
  if (BTSerial.available())
  Serial.write(BTSerial.read());
    
  if (Serial.available()){
  char xname=Serial.read();
  if (xname!="C")
  BTSerial.write(xname);
  else {
    BTSerial.write('at');
    
    
    }
  
  }

  
}
