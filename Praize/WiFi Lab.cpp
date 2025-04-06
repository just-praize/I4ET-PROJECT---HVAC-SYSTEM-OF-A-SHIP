#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <NewPingESP8266.h>

// ==== WiFi Credentials ====
const char *ssid = "Ghost";
const char *password = "55556666";

// ==== MQTT Configuration ====
const char *mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char *mqtt_subscribe_topic = "devices/Spandroit-HVACI4ET"; // MQTT topic for receiving remote commands

// ==== DHT11 Sensor ====
#define DHTTYPE DHT11
#define DHTPIN D1
DHT dht(DHTPIN, DHTTYPE);

// ==== Ultrasonic Sensor ====
#define TRIGGER_PIN D1
#define ECHO_PIN D2
#define MAX_DISTANCE 400
NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

WiFiClient espClient;
PubSubClient client(espClient);

// ==== MQTT Callback ====
void callback(char *topic, byte *payload, unsigned int length)
{
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Serial.print("Command received [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(message);

    if (message == "1")
    {
        Serial.println("Command: ACTIVATE HVAC");
    }
    else if (message == "0")
    {
        Serial.println("Command: DEACTIVATE HVAC");
    }
    else
    {
        Serial.println("Unknown command❗");
    }
}

// ==== WiFi Connection ====
void setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

// ==== MQTT Reconnect ====
void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT...");
        if (client.connect("Spandroit-HVACI4ET"))
        {
            Serial.println("Connected!");
            client.subscribe(mqtt_subscribe_topic);
            Serial.println("Subscribed to topic: " + String(mqtt_subscribe_topic));
        }
        else
        {
            Serial.print("Error, error=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    dht.begin();

    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    // === Sensor Readings ===
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    unsigned int uS = sonar.ping();
    unsigned int distance = uS / US_ROUNDTRIP_CM;
    bool occupancy = (distance > 0 && distance <= 250);

    // === Serial Output ===
    Serial.println("---- SENSOR DATA ----");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.print("Occupancy: ");
    Serial.println(occupancy ? "YES" : "NO");
    Serial.println("----------------------");

    delay(5000);
}
