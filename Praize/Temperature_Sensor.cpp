#include "DHT.h"            //This is an include directive
#define DHTTYPE DHT11       // This is to define the Sensor Type
#define dht_dpin D1         // This is to define the datapin
DHT dht(dht_dpin, DHTTYPE); // This is to initialze the sensor
void setup()
{
    dht.begin(); // This is to start the sensor
    Serial.begin(9600);
    delay(10);
    Serial.println("Initializing ESP8266...");
}

void loop()
{
    delay(3000); // Wait 3 secs between readings
    float t = dht.readTemperature();
    Serial.print("Temperature is: ");
    Serial.print(t);
    Serial.println("C");
}