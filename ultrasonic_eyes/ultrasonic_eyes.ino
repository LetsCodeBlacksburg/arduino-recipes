#include <Arduino.h>

const int triggerPin = 12;
const int echoPin = 13;

void setup() {
  Serial.begin(9600);           // For outputting distance data
  pinMode(echoPin, INPUT);      // Make echoPin an INPUT
  pinMode(triggerPin, OUTPUT);  // Make the triggerPin an OUTPUT
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches:
  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);

  // A HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the return echo time into a distance
  inches = duration / 74 / 2;
  
  Serial.print(inches);		// print it out to the serial port.
  Serial.println("in, ");
  
  delay(100);
}
