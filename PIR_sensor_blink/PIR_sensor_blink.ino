/////////////////////////////
//VARIABLES
int calibrationTime = 20; //the time we give the sensor to calibrate (20-30sec)
int pirPin = 2;     //the digital pin connected to the PIR sensor's output
int ledPin = 13;    // the built in LED pin

/////////////////////////////
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);       // Set up the various I/O pins
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate (monitor state on the serial port)
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

////////////////////////////
void loop(){

  if(digitalRead(pirPin) == HIGH){        // If the PIR is HIGH
       digitalWrite(ledPin, HIGH);        // then turn on the LED pin and
       Serial.println("HIGH (motion)");   // print "HIGH (motion)" on serial port
  }
  else {
       digitalWrite(ledPin, LOW);         // else, make the LED pin low and
       Serial.println("LOW (no motion)"); // print "LOW (no motion)" on serial port
  }
  delay(250);                             // 250mS delay
}
