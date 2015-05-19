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
  Serial.print(".");    // Serial monitor heartbeat
  delay(1000);          // Simple 1 second do nothing
}

