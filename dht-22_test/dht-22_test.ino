// Based on example testing sketch for various DHT humidity/temperature sensors
// by ladyada, public domain
#include "DHT.h"
#define DHTPIN 4        // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT-22 test!");
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();        // Read temperature as Celsius (the default)
  float f = dht.readTemperature(true);    // Read temperature as Fahrenheit (isFahrenheit = true)

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
  float hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)

  Serial.print("Humidity: "); Serial.print(h); Serial.print(" %\t");
  Serial.print("Temperature: "); Serial.print(t); Serial.print(" °C ("); Serial.print(f); Serial.print(" °F)\t\t");
  Serial.print("Heat index: "); Serial.print(hic); Serial.print(" °C ("); Serial.print(hif); Serial.println(" °F)");
}
