// wifi-web-esp-01-sensors
// This recipe uses the bportaluri WiFiEsp library https://github.com/bportaluri/WiFiEsp with
// some library dependancy fixes and the SMTPClient.h added (not tested). The fixed library 
// can be found at https://github.com/Tweeks-va/WiFiEsp and this wifi-web-esp-01-sensors sketch
// can be downloaded from https://github.com/LetsCodeBlacksburg/arduino-recipes

// Wireless Libraries & Variables
///////////////////////////////////////
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include "WiFiEsp.h"
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif
char ssid[] = "LOCAL-WIFI-SSID";        // the network SSID (name) you're connecting to
char pass[] = "LOCAL-WIFI-PASSWD";      // the network password (blank if none)
int status = WL_IDLE_STATUS;            // the Wifi radio's status
int reqCount = 0;                       // number of requests received
WiFiEspServer server(80);

const int buzzerPin = 3;          // Sound Buzzer

// See Light Sensor recipe
char sensorLightHeader[]= "Current Light Level (0-1023) = ";
int sensorLightData = 0;

// See DHT-22 recipe to make work
char sensorTempHeader[] = "Current Temperature(°C) = ";
float sensorTempData = 0;

// See DHT-22 recipe
char sensorHumidHeader[]= "Current Humidity(%) = ";
float sensorHumidData = 0;


///////// Setup 
////////////////////////////////
void setup()
{
  pinMode(buzzerPin, OUTPUT);           // Sets buzzerPin as output
  digitalWrite(buzzerPin, HIGH);

  ////// Setup WiFi
  Serial.begin(9600);       // initialize serial for debugging
  Serial1.begin(9600);      // initialize serial for ESP module
  WiFi.init(&Serial1);      // initialize ESP module
  if (WiFi.status() == WL_NO_SHIELD) {    // check for ESP-01
    Serial.println("WiFi shield not present");
    //buzzer("fail");         // hmmm.. this would be useful if it worked.
    while (true);           // don't continue
  }
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);    // Connect to WPA/WPA2 network
  }
  tone(buzzerPin, 2000, 50); delay(50); noTone(buzzerPin);  // Connected w/wifi
  Serial.println("You're connected to the network");
  printWifiStatus();
  server.begin();    // start the web server on port 80
}

//// loop()
/////////////////////////////////////
void loop()
{
serveWebPage();   // This is all we do here. :)
}



//// serveWebPage
////////////////////////////////////
void serveWebPage(){
  // listen for incoming clients
  WiFiEspClient client = server.available();
  if (client) {
    Serial.println("New client");
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
          sampleSensorData();
          Serial.println("Sending response");
          
          // send a standard http response header
          // use \r\n instead of many println statements to speedup data send
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"  // the connection will be closed after completion of the response
            "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<h1>My WiFi Arduino!</h1>\r\n");
          client.print("Requests received: ");
          client.print(++reqCount);
          client.print("<br>\r\n");
          client.print(sensorLightHeader);
          client.print(sensorLightData);
          client.print("<br>\r\n");
          // put more sensors here
          client.print("</html>\r\n");
          //buzzer("chirp");      // See buzzer Alarms recipe if this looks cool
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
    delay(100);

    // close the connection:
    client.stop();
    Serial.println("Client disconnected");
  } 
}


//// printWiFiStatus
////////////////////////////////////
void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
  // make a chirp sound once on network
  tone(buzzerPin, 2000, 50); delay(50); noTone(buzzerPin);
}

//// sampleSensorData()
///////////////////////////////////
void sampleSensorData(){
  // This is where you do your light, temperature and humidity sampling (DHT-22 could take TWO SECONDS)

  // Light Sensor (see receipe for more info)
  sensorLightData = analogRead(A5);

  // DHT-22 Humidity/Temp Sensor (see recipe for more info)

  // Other sensors to sample?
    tone(buzzerPin, 1000, 50); delay(50); noTone(buzzerPin);
}

