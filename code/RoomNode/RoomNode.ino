#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>

// WiFi Credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT Broker
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// MQTT Topic
const char* TOPIC = "zoneguard/floo2026/events";

// Hardware
const int buttonPin = 18;
bool lastButtonState = HIGH;

// MQTT Client
WiFiClient espClient;
PubSubClient client(espClient);

// Node Information
const char* NODE = "ROOM_NODE";
const char* ZONE = "ROOM_101";
const char* STATUS_TEXT = "SAFE";
const char* MESSAGE = "Patient entered Room 101";

// -------------------- WiFi --------------------
void connectWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Configure Indian Time (UTC +5:30)
  configTime(19800, 0, "pool.ntp.org");
}

// -------------------- Get Current Time --------------------
String getCurrentTime() {
  struct tm t;

  if (!getLocalTime(&t))
    return "Time Error";

  char buffer[30];
  strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &t);

  return String(buffer);
}

// -------------------- MQTT --------------------
void connectMQTT() {
  client.setServer(mqtt_server, mqtt_port);

  while (!client.connected()) {
    if (client.connect(NODE)) {
      // Connected
    } else {
      delay(2000);
    }
  }
}

// -------------------- Publish Event --------------------
void publishEvent() {

  StaticJsonDocument<256> doc;

  doc["patientId"] = "P001";
  doc["zone"] = ZONE;
  doc["node"] = NODE;
  doc["status"] = STATUS_TEXT;
  doc["message"] = MESSAGE;
  doc["timestamp"] = getCurrentTime();

  char payload[256];
  serializeJson(doc, payload);

  client.publish(TOPIC, payload);
}

// -------------------- Setup --------------------
void setup() {

  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

  connectWiFi();
  connectMQTT();
}

// -------------------- Loop --------------------
void loop() {

  if (!client.connected()) {
    connectMQTT();
  }

  client.loop();

  bool currentState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentState == LOW) {
    publishEvent();
    delay(300);   // Debounce
  }

  lastButtonState = currentState;
}
