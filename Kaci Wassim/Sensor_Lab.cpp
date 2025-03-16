#include <NewPing.h> // Library to handle ultrasonic sensor readings

// Define pins for the ultrasonic sensor
#define TRIG_PIN D1      // Trigger pin for HC-SR04
#define ECHO_PIN D2      // Echo pin for HC-SR04
#define MAX_DISTANCE 200 // Maximum measurable distance (in cm)

// Define pin for the MQ gas sensor
#define MQ_SENSOR A0 // Analog pin for MQ sensor readings

// Initialize the ultrasonic sensor using NewPing
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
    Serial.begin(115200);      // Start serial communication for debugging
    pinMode(MQ_SENSOR, INPUT); // Set MQ sensor pin as input
}

void loop()
{
    // Get distance from the ultrasonic sensor in cm
    int distance = sonar.ping_cm();

    // Read gas concentration from the MQ sensor (0-1023)
    int gasValue = analogRead(MQ_SENSOR);

    // Display sensor readings in the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm | Gas Level: ");
    Serial.println(gasValue);

    // Check for close objects (less than 10 cm)
    if (distance > 0 && distance < 10)
    {
        Serial.println("⚠ Warning: Object detected within 10 cm!");
    }

    // Check if gas concentration is too high (adjust threshold if needed)
    if (gasValue > 500)
    {
        Serial.println("⚠ Warning: High gas concentration detected!");
    }

    delay(1000); // Pause 1 second before taking the next reading
}