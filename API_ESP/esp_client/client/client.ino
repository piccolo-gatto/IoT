#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#define SERVER_IP "192.168.1.42" // подставить свой ip
#define PORT "8005"
#define ID "🐍🐍🐍"
#define PASSWORD "11111111"
#define LOCATION "kitchen"
#define DEVICE_ID "1"
// const char* location = "room";


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ID, PASSWORD);
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected!");
}


int average(String payload) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload);
  if (doc.containsKey("values")) {
    float sum = 0;
    int count = 0;
    JsonArray values = doc["values"];
    else {
    for (int i = 0; i < values.size(); i++) {
      sum += values[i].as<float>();
      count++;
    }
    return sum / count;
    }
  } 
  else {
    return 0;
  }
}


void postRequest(float value) {
  WiFiClient client;
  HTTPClient http;
  DynamicJsonDocument doc(200);
  doc["value"] = value;
  doc["location"] = LOCATION;
  doc["device_id"] = DEVICE_ID;
  String json;
  serializeJson(doc, json);
  http.begin(client, "http://"  SERVER_IP ":" PORT "/submit_temperature");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(json);
  if (httpCode == HTTP_CODE_OK) {
    Serial.println("POST success");
  } else {
    Serial.printf("POST error", http.errorToString(httpCode).c_str());
  }
  http.end();
}


void getRequest() {
  WiFiClient client;
  HTTPClient http;
  if (http.begin(client, "http://"  SERVER_IP ":" PORT "/temperature?location=" LOCATION)) {
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.printf("GET error", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
}


void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    if (Serial.available() > 0){
      float value = Serial.parseFloat();
      postRequest(value);
    }
    getRequest(httpCode);
    float avgTemperature = average(payload);
    Serial.print("Average temperature ");
    Serial.println(avgTemperature);
  }

 else {
      Serial.println("Unable to connect");
    }

  delay(10000);
}