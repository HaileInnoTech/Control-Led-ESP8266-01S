#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

// Wi-Fi network credentials
const char* ssid = "Quan Houes";
const char* password = "10051990";

// MQTT broker credentials
const char* mqttServer = "35.165.89.144";
const char* mqttTopic = "ledcontrol";

// Initialize the Wi-Fi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect
  }

  // Connect to the Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi network...");
  }
  Serial.println("Connected to Wi-Fi network.");

  // Connect to the MQTT broker
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP8266Client", NULL, NULL)) {
      Serial.println("Connected to MQTT broker.");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  // Keep the MQTT client connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Send the received message to the Arduino board in the desired format
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  message.replace("[", "");
  message.replace("]", "");
  message.replace(",", " ");
  Serial.println(message);
}
void reconnect() {
  // Attempt to reconnect to the MQTT broker every 5 seconds
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP8266Client", NULL, NULL)) {
      Serial.println("Connected to MQTT broker.");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}