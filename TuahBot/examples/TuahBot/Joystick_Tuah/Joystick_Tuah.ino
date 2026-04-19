
//This code is created for Tuah robot developed for RBTX
//Created by Fauzan Khairi Che Harun
// 2018
// This code doesn't use the library



#include<SoftwareSerial.h>
SoftwareSerial bt(12, 11);

//MOTORA
const int PWMA = 6;
const int DIRA = 2;
//MOTOR2
const int PWMB = 5;
const int DIRB = 3;

int data;
int datax, datay;
int motorSpeed1 = 0;
int motorSpeed2 = 0;
int manualMode();

void setup()
{
  Serial.begin(115200);
  bt.begin(9600);
  pinMode (PWMA, OUTPUT);
  pinMode (PWMB, OUTPUT);
  pinMode (DIRA, OUTPUT);
  pinMode (DIRB, OUTPUT);
}

void loop()
{
  if (bt.available() > 0)
  {
    data = bt.read();
    if (data == 254)
    {
      while (!bt.available()) {}
      datax = bt.read();
      if (datax > 100)datax = datax - 255;
    }

    else if (data == 253)
    {
      while (!bt.available()) {}
      datay = bt.read();
      if (datay > 100)datay = datay - 255;
    }

  }
  Serial.print("data:");
  Serial.print(data);
  Serial.print("     x:");
  Serial.print(datax);
  Serial.print("     y:");
  Serial.println(datay);
  manualMode();
}





//SUBFUNCTION FOR MANUAL MODE
int manualMode()
{
  //MOTOR STOP
  if ((data == 0) && (datax == 0) && (datay == 0))
  {
    analogWrite(PWMA, 0);
    digitalWrite(DIRA, LOW);
    analogWrite(PWMB, 0);
    digitalWrite(DIRB, LOW);
  }
  //MOTOR stop also
  else if ((data == 0) && (datax == 99) && (datay == 99))
  {
    analogWrite(PWMA, 0);
    digitalWrite(DIRA, LOW);
    analogWrite(PWMB, 0);
    digitalWrite(DIRB, LOW);
  }



  //FRONT LEFT
  else if ((datax >= 0) && (datax <= 100) && (datay <= 0) && (datay >= -100))
  {
    motorSpeed2 = map(datay, 0, -100, 200, 190); //Setting range (0 to -100)==(200 to 50 of pwm)
    motorSpeed1 = map(datay, 0, -100, 200, 255); //Setting range (0 to -100)==(200 to 255 of pwm)

    analogWrite(PWMA, motorSpeed1);
    digitalWrite(DIRA, LOW);
    analogWrite(PWMB, motorSpeed2);
    digitalWrite(DIRB, LOW);
  }

  //FRONT RIGHT
  else if ((datax >= 0) && (datax <= 100) && (datay > 0) && (datay <= 100))
  {
    motorSpeed2 = map(datay, 0, 100, 200, 255); //Setting range (0 to -100)==(200 to 255 of pwm)
    motorSpeed1 = map(datay, 0, 100, 200, 190); //Setting range (0 to -100)==(200 to 50 of pwm)
    analogWrite(PWMA, motorSpeed1);
    digitalWrite(DIRA, LOW);
    analogWrite(PWMB, motorSpeed2);
    digitalWrite(DIRB, LOW);
  }

  //BACK LEFT
  else if ((datax <= 0) && (datax >= -100) && (datay <= 0) && (datay >= -100))
  {
    motorSpeed2 = map(datay, 0, -100, 200, 190); //Setting range (0 to -100)==(200 to 50 of pwm)
    motorSpeed1 = map(datay, 0, -100, 200, 255); //Setting range (0 to -100)==(200 to 255 of pwm)
    analogWrite(PWMA, motorSpeed1);
    digitalWrite(DIRA, HIGH);
    analogWrite(PWMB, motorSpeed2);
    digitalWrite(DIRB, HIGH);
  }

  //BACK RIGHT
  else if ((datax <= 0) && (datax >= -100) && (datay > 0) && (datay <= 100))
  {
    motorSpeed2 = map(datay, 0, 100, 200, 255); //Setting range (0 to -100)==(200 to 255 of pwm)
    motorSpeed1 = map(datay, 0, 100, 200, 190); //Setting range (0 to -100)==(200 to 50 of pwm)
    analogWrite(PWMA, motorSpeed1);
    digitalWrite(DIRA, HIGH);
    analogWrite(PWMB, motorSpeed2);
    digitalWrite(DIRB, HIGH);
  }
  else
  {
    //STOP also
    analogWrite(PWMA, 0);
    digitalWrite(DIRA, LOW);
    analogWrite(PWMB, 0);
    digitalWrite(DIRB, LOW);
  }
}

