#include <LiquidCrystal.h>

// Create the LiquidCrystal object and define the pins used on the LCD shield
// The parameters are: rs, rw, enable, d4, d5, d6, d7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
 // Start the library, telling it we have a 16 column x 2 row display
 lcd.begin(16, 2);
 // Put the cursor on the first column of the first row
 lcd.setCursor(0, 0);
 lcd.print("Hello, world!");
 // First column of second row
 lcd.setCursor(0, 1);
 lcd.print("Seconds: ");
}
 
void loop()
{
 lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up
}
