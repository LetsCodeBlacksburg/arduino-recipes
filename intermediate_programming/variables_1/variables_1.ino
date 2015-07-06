int count = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // print the count
  Serial.println(count);
  // add one to the count
  count = count + 1;
  delay(1);        // delay in between reads for stability
}
