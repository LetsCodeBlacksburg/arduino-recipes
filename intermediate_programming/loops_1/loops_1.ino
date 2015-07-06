void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Ready to launch!");
  for(int x = 10; x >= 0; x--) {
    Serial.print(x);
    Serial.println("...");
    delay(1000);
  }
  Serial.println("Liftoff!");
}
