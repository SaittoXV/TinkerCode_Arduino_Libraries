//This code test the function of Line Sensor on Tuah
//This code does not use the library


//Infrared LineFollow
int data ;
const int s1 = A0;
const int s2 = A1;
const int s3 = A2;
const int s4 = A3;
const int s5 = A6;



void setup() {
  // initialize serial communication at 9600 bits per second:
    //initialize line follow sensor
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.print("        S1:");
  Serial.print(analogRead(s1));
  Serial.print("        S2:");
  Serial.print(analogRead(s2));
  Serial.print("        S3:");
  Serial.print(analogRead(s3));
  Serial.print("        S4:");
  Serial.print(analogRead(s4));
  Serial.print("        S5:");
  Serial.println(analogRead(s5));
  delay(1);        // delay in between reads for stability
}
