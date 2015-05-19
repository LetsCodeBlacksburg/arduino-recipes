int soundOut = 5;	// Sound output pin
int del = 1;	// Delay or duration of HIGH and LOW pulses 
                  // Longer delay times = lower frequency
			// So shorter delay 1 = high tone, longer delay 2 = low tone

int count = 0;	// Counter to control how long to play a high or low tone

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
  
  // Since del is the square wave's pulse time (inverse of frequency)
  // and count is a total amount of time, add del to count so we 
  // always wait the same amount of time
   count += del;
  
  // If the desired amount of time as been reached, reset the
  // count and toggle the frequency (1 to 2)
  if(count > 500)   // if past tone count (try 100, 25, 10, 4, 3, 2, 1 !)
  {
    count = 0;      // reset the duration counter
    if(del == 1)    // a == compares two things
    {
      del = 2;      // toggles the tone
    } else {
      del = 1;      // a single = sets a variable
    }
  }
}

