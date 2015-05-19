int soundOut = 5;		// Sound output pin

void setup()
{
  pinMode(soundOut, OUTPUT);
}

void loop()
{
  tone(soundOut, 440);	  // Surprise! Arduino can play sounds directly!
}

