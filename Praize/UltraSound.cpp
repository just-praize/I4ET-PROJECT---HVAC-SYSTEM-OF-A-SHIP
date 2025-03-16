#include <NewPingESP8266.h>

#define TRIGGER_PIN D1
#define ECHO_PIN D2
#define MAX_DISTANCE 400 // Set Distance or Range of Sensor

NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // To initialize the sensor

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    delay(1000);                    // Wait about 1 ping/sec
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS)
    unsigned int Distance = uS / US_ROUNDTRIP_CM;

    Serial.print("Range: ");
    Serial.print(Distance); // Convert Ping time to distance and print result
    Serial.println("cm");

    if (Distance > 250 || Distance == 0)
    {
        // If distance is greater than 250 cm, or no object detected (distance == 0)
        Serial.println("No Occupancy Detected");
    }
    else
    {
        // If object is within 250 cm
        Serial.println("Occupancy Detected");
    }
}