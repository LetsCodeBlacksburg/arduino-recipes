int soundOut = 5;		// Sound output pin
int del = 2;		// This determines how long the signal stays
				// HIGH or LOW in milliseconds

void setup()
{
  pinMode(soundOut, OUTPUT);
}

void loop()
{
  digitalWrite(soundOut, HIGH); 
  delay(del);
  digitalWrite(soundOut, LOW); 
  delay(del);
}
