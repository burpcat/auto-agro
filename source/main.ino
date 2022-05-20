#include <Servo.h>
#define sensorPower 7 // interfacing rain sensor power pin at pin 7
#define sensorPin 8 // interfacing rain sensor digital pin at pin 8

#define echoPin 2
#define trigPin 3

int waterpump=13; // interfacing relay module at pin 13
Servo myservo;

long duration;
int distance;
void setup(){
  digitalWrite(sensorPower, LOW);//keep the rain sensor low

  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  myservo.attach(9);//interfacing servomotor at pin 9
 
 }
void loop(){
  
  int val = readSensor();
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
 duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2);
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm ");
  delay(1000);
  if (distance==10) //fixed distance is 10cm
  {
    if (val)
    {
      digitalWrite(13,LOW);
      myservo.write(0);
    }
    else
    {
      digitalWrite(13,LOW);
      myservo.write(180);
      
    }
  }
  else if (distance>10)
  {
    if (val)
    {
      digitalWrite(13,HIGH);
      myservo.write(0);
    }
    else
    {
      digitalWrite(13,LOW);
      myservo.write(0);
    }
    
  }
 else if (distance<10)   
 {
    myservo.write(180);
    digitalWrite(13,LOW);
  
 }
 
}

int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // Allow power to settle
  int val = digitalRead(sensorPin); // Read the sensor output
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // Return the value
