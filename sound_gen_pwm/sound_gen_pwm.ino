int soundOut = 5;		// Sound output pin

void setup()
{
  pinMode(soundOut, OUTPUT);
  
  // Doing this here shows that we keep generating sound
  // Even after setup is complete and the loop can do
  // other things
  analogWrite(soundOut, 128);
}

void loop()
{
}

