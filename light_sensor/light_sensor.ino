// With a 1k resistor in series with this light sensor, you should
// get around 900 range in the dark, around 600 in ambient, and
// around 2-200 range with an LED shining on it.
// This is for a CdS photo resistor cell with approximate attributes
// of:    DARK ~ 100k      AMBIENT ~ 2k      LIT ~ 0.7k

int ls = A5;   		  //analog pin to which LS is connected
int ls_value = 0;        //variable to store LS values, 
                         //we'll set this to zero first.

void setup()
{
  Serial.begin(9600);   //Start the serial monitor
  pinMode(ls, INPUT);   //Tell arduino that this pin is for input
}

void loop()
{
  ls_value = analogRead(ls);     //reads the light sensor values
  Serial.println(ls_value);      //prints the LS values to serial monitor
  delay(50);                     //slow it down a bit
}

