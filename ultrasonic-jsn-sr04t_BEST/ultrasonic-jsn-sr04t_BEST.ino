#include <Arduino.h>
// ultrasonic_jsn-sro4t_BEST                       v2020-10-04 tweeks-homework@theweeks.org
//  
// For more reliably getting distance readings from the jsn-sr04t(v3) sensor, careful timing,
// not using Serial.print()s within the getDistance() loop, and error rejection (noise over
// 610cm *20ft) needs to be detected and reattempted (20 times max).
//
// Original (broken) sample code from https://www.makerguides.com/jsn-sr04t-arduino-tutorial/
//        NOTE: Do not use Serial.print()s within the getDistance() function or within
//        the timing while loop. The printing seems to interfere with the UART timing
//        of pulseIN() function in some systems. 

const int triggerPin = 2;
const int echoPin = 3;

void setup() {
  Serial.begin(9600);           // For outputting distance data
  pinMode(echoPin,INPUT_PULLUP);  // Someone said this also helped with errant readings...
  pinMode(triggerPin, OUTPUT);  // Make the triggerPin an OUTPUT
  digitalWrite(triggerPin, LOW);
}

void loop()
{
  int dist = 0;
  dist = getDistance();
  Serial.print(dist); Serial.println("cm");   // took Serial.prints() out of getDistance()
  delay(50);
}



// better code
int getDistance() {

  long duration = 0;
  int distance = 0;
  int watchloop = 0;

  // Clear the triggerPin by setting it LOW and wait for any pulses to expire:
  digitalWrite(triggerPin, LOW);      // setting state to low and
  delay(2);                           // waiting 2,000uS (or 686cm (>22ft) to eliminate "echo noise")

  // only grab values under 20ft/610cm (for some reason, 676 is a common return error for ∞ distance)
  while ( (distance == 0) || (distance > 610) ) {
    // Trigger the sensor by setting the triggerPin high for 10 microseconds:
    digitalWrite(triggerPin, HIGH);         // start sending the 40kHz wave...
    delayMicroseconds(20);                  // sending for 20uS
    digitalWrite(triggerPin, LOW);          // stop sending 40kHz wave

    // Read the echoPin. pulseIn() duration of when the wave-echo stops (in microseconds):
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance:
    distance = duration * 0.034 / 2;
    //Serial.print("distance=");Serial.println(distance);

    // Catch funky ∞ distance readings
    watchloop++;        
    if (watchloop > 20){      // If errant "676" readings 20 times
      distance = 610;         // set distance to 610cm (20ft) 
      break;                  // and break out of loop (not really needed if forced to 610)
    }
    
  }

  return (distance);
}


/*
  // problem code

  int getDistance(){
  int  distance=0;
  // Clear the trigPin by setting it LOW:
  digitalWrite(triggerPin, LOW);

  delayMicroseconds(5);
  while(distance==0){
    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  long duration = pulseIn(echoPin, HIGH);
    Serial.print("Dur / Dist = ");
    Serial.print(duration); Serial.print(" / ");

    // Calculate the distance:
    distance = duration*0.034/2;
    Serial.print(distance);Serial.println("cm");
  }
  return(distance);
  }
*/
