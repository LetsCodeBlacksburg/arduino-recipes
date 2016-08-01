const int buttonPin = 3;
const int ledPin = 13;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  if (digitalRead(buttonPin)) {        // If button push is true
    digitalWrite(ledPin, HIGH);        // light LED
    Serial.println("Button Pushed!");  // and print on serial port
    delay(10);
  }
  else {
    digitalWrite(ledPin, LOW);         // otherwise, turn off LED
    delay(1);
  }
 
  delay(10);        // delay in between reads for stability
}
