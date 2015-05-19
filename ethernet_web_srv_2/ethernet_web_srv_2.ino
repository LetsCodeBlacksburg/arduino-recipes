#include <SPI.h>
#include <Ethernet.h>

// Change at least the last hex number below to any two digit value so that
// you have a unique address on your class network. Otherwise, there will
// be MAC address conflicts and you and your neighbors will have problems.
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

// Initialize the Ethernet server library
// with using DHCP for your IP (see serial monitor) and port you wish 
// to use (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
   ; // wait for serial port to connect. Needed for Leonardo only

    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // no point in carrying on, so do nothing forevermore:
      for(;;)
       ;
    }
   }

  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  Serial.print("Arduino server is at ");
  Serial.println(Ethernet.localIP());
}

// Main execution loop
void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  // If a client has connected, do this
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after gets response
	   client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");			// Opens HTML content
          client.println("<pre>");			// Preformatted text block
          client.println("================================");
          client.println("=== Tweeks Arduino Webserver ===");
          client.println("================================");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            // Adjust the for loop, adjust “n” of  x<sensorReading/n to 
		// scale the 1023 bar graph (play with it)
            int x=0;
            for (x=0 ; x<sensorReading/15 ; x=x+1) {
              client.print("=");    // builds your ASCII TXT bar graph
            }
            client.print(sensorReading);  // prints the actual value
            client.print("<br />");       
          }
          client.println("</pre>");
          client.println("</html>");      // closes out html web page
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

