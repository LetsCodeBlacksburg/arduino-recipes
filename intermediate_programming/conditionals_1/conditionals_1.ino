int count = 0;
int inc = 1;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // add inc to the count
  count = count + inc;

  if(count == 10) {
    Serial.println("Max hit. Counting down");
    inc = -1;
  } else if(count == 0) {
    Serial.println("Min hit. Counting up");
    inc = 1;
  } else {
    // print the count
    Serial.println(count);
  }
  delay(500);        // delay in between reads for stability
}
