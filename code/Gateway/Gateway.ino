#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Hardware
const int buzzerPin = 23;

// WiFi Credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT Broker
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// MQTT Topics
const char* EVENT_TOPIC = "zoneguard/floo2026/events";
const char* SYSTEM_TOPIC = "zoneguard/floo2026/system";

// MQTT Client
WiFiClient espClient;
PubSubClient client(espClient);

// Heartbeat Timer
unsigned long lastHeartbeat = 0;

// -------------------- MQTT Callback --------------------
void callback(char* topic, byte* payload, unsigned int length) {

  StaticJsonDocument<256> doc;

  if (deserializeJson(doc, payload, length)) {
    return;
  }

  String status = doc["status"];

  Serial.println(doc["message"].as<const char*>());

  if (status == "EMERGENCY") {
    tone(buzzerPin, 1000);
    delay(1000);
    noTone(buzzerPin);
  }
}

// -------------------- WiFi --------------------
void connectWiFi() {

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

// -------------------- MQTT --------------------
void connectMQTT() {

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {

    if (client.connect("GatewayESP32_01")) {

      client.subscribe(EVENT_TOPIC);

    } else {

      delay(2000);

    }
  }
}

// -------------------- Setup --------------------
void setup() {

  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);

  connectWiFi();
  connectMQTT();
}

// -------------------- Loop --------------------
void loop() {

  if (!client.connected()) {
    connectMQTT();
  }

  client.loop();

  // Publish heartbeat every 5 seconds
  if (millis() - lastHeartbeat > 5000) {

    StaticJsonDocument<64> doc;
    doc["status"] = "ONLINE";

    char payload[64];
    serializeJson(doc, payload);

    client.publish(SYSTEM_TOPIC, payload);

    lastHeartbeat = millis();
  }
}
