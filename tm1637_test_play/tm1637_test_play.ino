#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 8
#define DIO 9

// The amount of time (in milliseconds) between tests
#define TEST_DELAY_SLOW   2000
#define TEST_DELAY_FAST   20

TM1637Display display(CLK, DIO);

void setup()
{
  display.setBrightness(0xff);
}

void loop()
{
  // Implementing a song playlist counter
  Serial.println("============== start of playlist ============");
  for (int x=0; x<100; x++){
    Serial.println(x);        // Use Serial.print() to troubleshoot what's going on.
    display.showNumberDec(x); // This is the only line you need to make the display
    delay(TEST_DELAY_FAST); 
  }
Serial.println("============== end of playlist ============");


  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };


  // All segments on
//  display.setSegments(data);
  delay(TEST_DELAY_SLOW);

  // Selectively set different digits
  data[0] = 0b01001001;
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);

  for(k = 3; k >= 0; k--) {
	display.setSegments(data, 1, k);
	delay(TEST_DELAY_SLOW);
	}

  display.setSegments(data+2, 2, 2);
  delay(TEST_DELAY_SLOW);

  display.setSegments(data+2, 2, 1);
  delay(TEST_DELAY_SLOW);

  display.setSegments(data+1, 3, 1);
  delay(TEST_DELAY_SLOW);


  // Show decimal numbers with/without leading zeros
  bool lz = false;
  for (uint8_t z = 0; z < 2; z++) {
	for(k = 0; k < 10000; k += k*4 + 7) {
		display.showNumberDec(k, lz);
		delay(TEST_DELAY_SLOW);
	}
	lz = true;
  }

  // Show decimal number whose length is smaller than 4
  for(k = 0; k < 4; k++)
	data[k] = 0;
  display.setSegments(data);

	// Run through all the dots
	for(k=0; k <= 4; k++) {
		display.showNumberDecEx(0, (0x80 >> k), true);
		delay(TEST_DELAY_SLOW);
	}

  display.showNumberDec(153, false, 3, 1);
  delay(TEST_DELAY_SLOW);
  display.showNumberDec(22, false, 2, 2);
  delay(TEST_DELAY_SLOW);
  display.showNumberDec(0, true, 1, 3);
  delay(TEST_DELAY_SLOW);
  display.showNumberDec(0, true, 1, 2);
  delay(TEST_DELAY_SLOW);
  display.showNumberDec(0, true, 1, 1);
  delay(TEST_DELAY_SLOW);
  display.showNumberDec(0, true, 1, 0);
  delay(TEST_DELAY_SLOW);

  // Brightness Test
  for(k = 0; k < 4; k++)
	data[k] = 0xff;
  for(k = 0; k < 7; k++) {
    display.setBrightness(k);
    display.setSegments(data);
    delay(TEST_DELAY_SLOW);
  }
  
  // On/Off test
  for(k = 0; k < 4; k++) {
    display.setBrightness(7, false);  // Turn off
    display.setSegments(data);
    delay(TEST_DELAY_SLOW);
    display.setBrightness(7, true); // Turn on
    display.setSegments(data);
    delay(TEST_DELAY_SLOW);  
  }


  while(1);
}
