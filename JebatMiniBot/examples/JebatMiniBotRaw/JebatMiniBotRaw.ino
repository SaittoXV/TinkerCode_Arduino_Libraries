//
//This code is created for Zuzumi robot developed for RObofair 2018.
//Created by Fauzan Khairi Che Harun
// 2018
// THis is the code without using library. Raw library code in this file


//MOTOR1
const int PWM1 = 5;
const int dir1 = 2;
//MOTOR2
const int PWM2 = 23;
const int dir2 = 17;

//Button Init
const int zbutton = 0;

//LED Init
const int led5 = 11;
const int led4 = 13;
const int led3 = 7;
const int led2 = 4;
const int led1 = 12;

//Bluetooth Init
const int bluetoothrx = 0;
const int bluetoothtx = 1;


//Infrared LineFollow
int data ;
const int s1 = 25;
const int s2 = 34;
const int s3 = 22;
const int s4 = 33;
const int s5 = 35;

//PID
double goal;//setting goal
int PID1;//set value for s1
int PID2;//set value for s2
int PID3;//set value for s3
int PID4;
int PID5;
int pid1;
int pid2;
int pid3;
int pid4;
int pid5;
double  error;//
double prev_error = 0;
double difference;
double place;
double p;
double d;
double kp;//constant kp
double kd;//constant kd
int fast1;//pmw speeed set motorright
int fast2;//pwm speed set motorleft
int treshold;
int sensorMin1 = 4023;   // minimum sensor value
int sensorMin2 = 4023;
int sensorMin3 = 4023;
int sensorMin4 = 4023;
int sensorMin5 = 4023;
int sensorMax1 = 0;    // maximum sensor value
int sensorMax2 = 0;
int sensorMax3 = 0;
int sensorMax4 = 0;
int sensorMax5 = 0;
int sensorValue1 = 0;  // Placeholder reading value
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;


//Init extra pin
const int irR = 4;//need to double check
const int irL = 26;
int R, L; // IR Sensor
const int Relay = 4;
#include <Servo.h>
Servo myservo;  // create servo object to control a servo



//Init Ultrasound
const int Ltrig = 21;
const int Lecho = 22;

#include <SoftwareSerial.h>

SoftwareSerial bluez(bluetoothrx, bluetoothtx); // RX, TX

char BTdata; // variable for bluetooth
long dur1;
int dis1;



//initialize EEPROM Save
#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int speedadd = 0;
byte speedvalue=100;



void setup()
{
  //initializr serial
  //  Serial.begin(9600);
  //initialize bluetooth
  bluez.begin(9600);

  //Initialize Ultrasonic
  pinMode(Ltrig, OUTPUT);
  pinMode(Lecho, INPUT);


  //initialize LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  //initialize button
  pinMode(zbutton, INPUT);

  //initialize line follow sensor
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);


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

}


void loop()
{
  if (bluez.available()) {
    BTdata = bluez.read();
    //   Serial.println(BTdata);
  }

  ////PushButton Test
  //int push=digitalRead(zbutton);
  //if (push==0)


  //Speed extract from ROM

  if (BTdata == 'q')
  {
    while (!bluez.available()) {}
    int speedy = bluez.read();
    //   Serial.println(speedy,DEC);
    EEPROM.write(0x39, 0);
    delay(10);
    speedvalue = EEPROM.read(0);
    speedvalue = speedy;
    if (speedvalue == 0) speedvalue = 255;
    //Serial.println(speedvalue,DEC);

  }




  if (BTdata == 'f')
  {
    motorsteer("forward", speedvalue);
  }
  else if (BTdata == 'l')
  {
    motorsteer("left", speedvalue);
  }
  else if (BTdata == 'r')
  {
    motorsteer("right", speedvalue);
  }
  else if (BTdata == 'b')
  {
    motorsteer("backward", speedvalue);
  }

  else if (BTdata == '1')
  {
    RelaySwitch();//red
  }
  else if (BTdata == '2')
  {
    ServoGunFire ();//purple
  }
  else if (BTdata == '3')
  {
    LineFollowing();//blue
  }
  else if (BTdata == '4')
  {
    MazeRunner();//green
  }
  else if (BTdata == '5')
  {
    megablink(speedvalue);    //knightrider(delay speed);
  }

  else if (BTdata == '6')
  {
    knightrider(speedvalue);    //knightrider(delay speed);
  }
  else {
    motorsteer("x", 0);
  }

}

void motorsteer(char *robotdirection, int power)
{

  if (robotdirection == "forward")
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    analogWrite(PWM1, power);
    analogWrite(PWM2, power);
  }

  else if (robotdirection == "right")
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    analogWrite(PWM1, power / 2);
    analogWrite(PWM2, power);
  }

  else if (robotdirection == "left")
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    analogWrite(PWM1, power);
    analogWrite(PWM2, power / 2);
  }

  else if (robotdirection == "backward")
  {
    digitalWrite(dir1, HIGH);
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





void motortank(char *directionL, char *directionR, int powerL, int powerR)
{

  if (directionR == "forward")
  {
    digitalWrite(dir1, LOW);
  }

  else if (directionL == "backward")
  {
    digitalWrite(dir1, HIGH);
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


void knightrider(int delayx)
{

  digitalWrite(led1, LOW);
  delay(delayx);
  digitalWrite(led1, HIGH);
  delay(delayx);
  digitalWrite(led2, LOW);
  delay(delayx);
  digitalWrite(led2, HIGH);
  delay(delayx);
  digitalWrite(led3, LOW);
  delay(delayx);
  digitalWrite(led3, HIGH);
  delay(delayx);
  digitalWrite(led4, LOW);
  delay(delayx);
  digitalWrite(led4, HIGH);
  delay(delayx);
  digitalWrite(led5, LOW);
  delay(delayx);
  digitalWrite(led5, HIGH);
  delay(delayx);
  digitalWrite(led5, LOW);
  delay(delayx);
  digitalWrite(led5, HIGH);
  delay(delayx);
  digitalWrite(led4, LOW);
  delay(delayx);
  digitalWrite(led4, HIGH);
  delay(delayx);
  digitalWrite(led3, LOW);
  delay(delayx);
  digitalWrite(led3, HIGH);
  delay(delayx);
  digitalWrite(led2, LOW);
  delay(delayx);
  digitalWrite(led2, HIGH);
  delay(delayx);
  digitalWrite(led1, LOW);
  delay(delayx);
  digitalWrite(led1, HIGH);
}

void megablink(int del)
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(del);                       // wait for a second
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  delay(del);                       // wait for a second
}

void ultrasonic()
{

  digitalWrite(Ltrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ltrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Ltrig, LOW);
  dur1 = pulseIn(Lecho, HIGH);
  dis1 = dur1 * 0.034 / 2;

  return dis1;
}

void RelaySwitch()
{
  digitalWrite(Relay, HIGH);   //Turn off relay
  delay(1000);
  digitalWrite(Relay, LOW);    //Turn on relay
  //delay(2000);

}


void ServoGunFire() // 10 for separated nano, 9 for embedded nano.
{
  myservo.attach(10);  // attaches the servo on pin 10 to the servo object                           // waits for the servo to get there
  myservo.write(180);                  // sets the servo position according to the scaled value
  delay(2000);
  myservo.write(90);                  // sets the servo position according to the scaled value
  delay(2000);
  myservo.detach();
}






void MazeRunner ()
{
  while (!bluez.available())
  {

    R = digitalRead(irR); //RIGHT
    L = digitalRead(irL); //LEFT

    if ((R == 1) && (L == 1))
    {
      motorsteer("forward", 255);
    }

    else if ((R == 0) && (L == 1))
    {
      motortank("forward", "backward", 150, 150);
    }

    else if ((R == 1) && (L == 0))
    {
      motortank("forward", "backward", 150, 150);
    }

    else if ((R == 0) && (L == 0))
    {
      motorsteer("forward", 255);
    }

    else
    {
      motorsteer("stop", 0);
    }

  }
}






void calibrate()
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  for (double p = 0; p < 6000; p++)
  {

    // Grabs incoming data from the photosensor
    sensorValue1 = analogRead(s1);
    sensorValue2 = analogRead(s2);
    sensorValue3 = analogRead(s3);
    sensorValue4 = analogRead(s4);
    sensorValue5 = analogRead(s5);

    // Record the maximum sensor value, and sets as new limit
    if (sensorValue1 > sensorMax1) {
      sensorMax1 = sensorValue1;
    }
    if (sensorValue2 > sensorMax2) {
      sensorMax2 = sensorValue2;
    }
    if (sensorValue3 > sensorMax3) {
      sensorMax3 = sensorValue3;
    }
    if (sensorValue4 > sensorMax4) {
      sensorMax4 = sensorValue4;
    }
    if (sensorValue5 > sensorMax5) {
      sensorMax5 = sensorValue5;
    }

    // Record the minimum sensor value, and sets as new limit
    if (sensorValue1 < sensorMin1) {
      sensorMin1 = sensorValue1;
    }
    if (sensorValue2 < sensorMin2) {
      sensorMin2 = sensorValue2;
    }
    if (sensorValue3 < sensorMin3) {
      sensorMin3 = sensorValue3;
    }
    if (sensorValue4 < sensorMin4) {
      sensorMin4 = sensorValue4;
    }
    if (sensorValue5 < sensorMin5) {
      sensorMin5 = sensorValue5;
    }
  }
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
}




void LineFollowing()
{

  motortank("forward", "backward", 150, 150); //keep rotating

  calibrate();
  motorsteer("stop", 0);
  delay(3000);
  while (!bluez.available())
  {

    sensor();
    cvalue();
    calculation();
    motorfollow();
  }
}



void sensor()
{

  //to read the value of sensors
  PID1 = analogRead(s1);
  PID2 = analogRead(s2);
  PID3 = analogRead(s3);
  PID4 = analogRead(s4);
  PID5 = analogRead(s5);


  //to show the sensor value in digital
  //s1
  //  Serial.print("PID1");
  //  Serial.println(PID1);
  //delay(1000);
  if (PID1 < (sensorMin1 + sensorMax1) / 2)
  {
    pid1 = 1;
    digitalWrite(led1, LOW);
  }
  else
  {
    pid1 = 0;
      digitalWrite(led1, HIGH);

  }
  //  Serial.println(pid1);
  //s2
  //  Serial.println("PID2");
  //  Serial.println(PID2);
  //delay(1000);
  if (PID2 < (sensorMin2 + sensorMax2) / 2)
  {
    pid2 = 1;
    digitalWrite(led2, LOW);

  }
  else
  {
    pid2 = 0;
    digitalWrite(led2, HIGH);

  }
  //  Serial.println(pid2);
  //s3
  //  Serial.println("PID3");
  //  Serial.println(PID3);
  //delay(1000);
  if (PID3 < (sensorMin3 + sensorMax3) / 2)
  {
    pid3 = 1;
    digitalWrite(led3, LOW);

  }
  else
  {
    pid3 = 0;
    digitalWrite(led3, HIGH);

  }
  //  Serial.println(pid3);
  //delay(1000);
  if (PID4 < (sensorMin4 + sensorMax4) / 2)
  {
    digitalWrite(led4, LOW);

    pid4 = 1;
  }
  else
  {
    pid4 = 0;
    digitalWrite(led4, HIGH);

  }
  //  Serial.println(pid4);
  //delay(1000);
  if (PID5 < (sensorMin5 + sensorMax5) / 2)
  {
    digitalWrite(led5, LOW);

    pid5 = 1;
  }
  else
  {
    digitalWrite(led5, HIGH);
    pid5 = 0;
  }
  //  Serial.println(pid5);
  //delay(1000);
}

void cvalue()//to set coordinate value for sensor
{ //sensor1 is from left of user not car
  if (pid1 == 1 & pid2 == 1 & pid3 == 1 & pid4 == 1 & pid5 == 1 )//11111
  {
    place = 0;
    kp = -15;
    kd = -9;
    //but backward coding for motor
  }
  else if (pid1 == 1 & pid2 == 0 & pid3 == 0 & pid4 == 0 & pid5 == 0 )//1000 this shoud be 90 turn
  {
    place = -1.5;
    kp = -40;
    kd = -15;
  }
  else if (pid1 == 0 & pid2 == 1 & pid3 == 0 & pid4 == 0 & pid5 == 0 )//01000
  {
    place = -1.0;
    kp = -15;
    kd = -9;
  }
  else if (pid1 == 0 & pid2 == 0 & pid3 == 1 & pid4 == 0 & pid5 == 0) //00100
  {
    place = 0;
    kp = 15;
    kd = 9;
  }
  else if (pid1 == 0 & pid2 == 0 & pid3 == 0 & pid4 == 1 & pid5 == 0 ) // 00010
  {
    place = 1;
    kp = 15;
    kd = 9;
  }
  else if (pid1 == 0 & pid2 == 0 & pid3 == 0 & pid4 == 0 & pid5 == 1 )//00001 this shoud be 90 turn
  {
    place = 1.5;
    kp = 40;
    kd = 15;
  }


  //  Serial.print(pid1);
  //  Serial.print(pid2);
  //  Serial.print(pid3);
  //  Serial.print(pid4);
  //  Serial.println(pid5);
  //  delay(1000);
}

void calculation()
{
  //kp =-40;
  //kd =-25;

  goal = 0;

  error = place - goal;

  difference = prev_error - error;

  prev_error = error;



//  p = error * kp;
//  d = difference * kd;
    p = kp;
    d = kd;
}

void motorfollow()
{
  // setting the motorspeed
  fast1 = abs(p + d + 100);
  // if motor speed exit 255 it will use this speed
  if (fast1 > 255)
  {
    fast1 = 255;
  }
  // setting motor speed
  fast2 = abs( p + d - 100);
  // if motor speed exit 255 it will use this speed
  if (fast2 > 255)
  {
    fast2 = 255;
  }

  // setting motor speed

  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);//clockwise
  analogWrite(PWM1, fast1);//left
  analogWrite(PWM2, fast2);//right
}

void LED(int l,char *stat)
{

if (stat=="ON"){
digitalWrite(l, LOW);
}

else if (stat=="OFF")
{
digitalWrite(l, HIGH);
}

}

int ir_sense(int l)
{
int sensordata= analogRead(l);
return sensordata;
}








