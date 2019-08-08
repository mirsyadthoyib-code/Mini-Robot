#include <AFMotor.h>

AF_DCMotor motorKiri1(1);
AF_DCMotor motorKiri2(2);
AF_DCMotor motorKanan1(3);
AF_DCMotor motorKanan2(4);

#define trigPin A4
#define echoPin A5

#define sensorPin1 A0
#define sensorPin2 A1
#define sensorPin3 A2
#define sensorPin4 A3

#define modePin 2

int sensorData1;
int sensorData2;
int sensorData3;
int sensorData4;
int putih = 300;
int keluarArena = 0;
int adaMusuh = 0;
long duration;
long distance;
int count = 0;
char state="S";

int sensorUltrasonik() 
{
  
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.println(distance);
  
  if (distance <= 100)
  {
    adaMusuh = 1;
  }
  else
  {
    adaMusuh = 0;
  }
  delay(200);
  return adaMusuh;
}

int sensorGaris()
{
  sensorData1 = analogRead(sensorPin1);
  sensorData2 = analogRead(sensorPin2);
  sensorData3 = analogRead(sensorPin3);
  sensorData4 = analogRead(sensorPin4);
  
//  Serial.print(sensorData1);
//  Serial.print(" ");
//  Serial.print(sensorData2);
//  Serial.print(" ");
//  Serial.print(sensorData3);
//  Serial.print(" ");
//  Serial.println(sensorData4);
//  Serial.println(keluarArena);
  if(sensorData1 <= putih || sensorData2 <= putih)
  {
    keluarArena = 1;
  }
  else
  {
    keluarArena = 0;
  }
  return keluarArena;
}

void maju(int kecepatan)
{
  //Motor Kiri
  motorKiri1.setSpeed(kecepatan-50);
  motorKiri1.run(FORWARD);
  motorKiri2.setSpeed(kecepatan-50);
  motorKiri2.run(FORWARD);

  //Motor Kanan
  motorKanan1.setSpeed(kecepatan);
  motorKanan1.run(FORWARD);
  motorKanan2.setSpeed(kecepatan);
  motorKanan2.run(FORWARD);
}

void mundur(int kecepatan)
{
  //Motor Kiri
  motorKiri1.setSpeed(kecepatan-120);
  motorKiri1.run(BACKWARD);
  motorKiri2.setSpeed(kecepatan-120);
  motorKiri2.run(BACKWARD);

  //Motor Kanan
  motorKanan1.setSpeed(kecepatan);
  motorKanan1.run(BACKWARD);
  motorKanan2.setSpeed(kecepatan);
  motorKanan2.run(BACKWARD);
}

void muterKanan(int kecepatan)
{
  //Motor Kiri
  motorKiri1.setSpeed(kecepatan-50);
  motorKiri1.run(FORWARD);
  motorKiri2.setSpeed(kecepatan-50);
  motorKiri2.run(FORWARD);

  //Motor Kanan
  motorKanan1.setSpeed(kecepatan);
  motorKanan1.run(BACKWARD);
  motorKanan2.setSpeed(kecepatan);
  motorKanan2.run(BACKWARD);
}

void muterKiri(int kecepatan)
{
  //Motor Kiri
  motorKiri1.setSpeed(kecepatan-120);
  motorKiri1.run(BACKWARD);
  motorKiri2.setSpeed(kecepatan-120);
  motorKiri2.run(BACKWARD);

  //Motor Kanan
  motorKanan1.setSpeed(kecepatan);
  motorKanan1.run(FORWARD);
  motorKanan2.setSpeed(kecepatan);
  motorKanan2.run(FORWARD);
}

void berhenti()
{
  //Motor Kiri
  motorKiri1.run(RELEASE);
  motorKiri2.run(RELEASE);

  //Motor Kanan
  motorKanan1.run(RELEASE);
  motorKanan2.run(RELEASE);
}

void controlled()
{
  if(Serial.available())
  {
    state = Serial.read();
  }
  if (state == 'F') 
  {
    maju(255);
    Serial.println("maju");
  }
  else if(state == 'B')
  {
    mundur(255);
    Serial.println("mundur");
  }
  else if(state == 'R')
  {
    muterKanan(255);
    Serial.println("kanan");
  }
  else if(state == 'L')
  {
    muterKiri(255);
    Serial.println("kiri");
  }
  else
  {
    berhenti();
  }
}

void otomatis()
{
  if(sensorGaris() == 1)
  {
    mundur(255);
    delay(800);
    muterKiri(255);
    delay(1500);
  }
  else
  {
    if(sensorUltrasonik() == 1)
    {
      maju(255);
    }
    else
    {
      muterKanan(255);
      count++;
      if(count >= 300)
      {
        for(int i = 0; i<=5; i++)
        {
          maju(255);
          count = 0;
        }
      }
    }
  }
}

void setup()
{
    // Start up serial connection
    Serial.begin(9600); // baud rate
    motorKiri1.run(RELEASE);
    motorKiri2.run(RELEASE);
    motorKanan1.run(RELEASE);
    motorKanan2.run(RELEASE);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(sensorPin1, INPUT);
    pinMode(sensorPin2, INPUT);
    pinMode(sensorPin3, INPUT);
    pinMode(sensorPin4, INPUT);
}
     
void loop()
{
  if(modePin == true)
  {
    controlled();
  }
  else
  {
     otomatis();
  }
}
