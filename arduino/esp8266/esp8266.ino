#include <ESP8266WiFi.h> 
#include "WiFiConnector.h"
#include "HTTPSender.h"

String ssid = "Chi Huy"; 
String password = "999999999"; 
String serverUrl = "http://192.168.1.101:8080/api/v1/sensors";

const unsigned long baudRate = 115200;

WiFiConnector wifiConnector;
HTTPSender httpSender(serverUrl);
 
void setup() { 
    Serial.begin(baudRate);
    wifiConnector.connect(ssid, password);
} 
 
void loop() { 
    String sensorJsonData = "";
    bool received = false;

    while (Serial.available() > 0) {
      char incomingChar = Serial.read();
      if (incomingChar == '\n') {
        received = true;
        break;
      }
      sensorJsonData += incomingChar;
    }

    if (received) {
      httpSender.send(sensorJsonData);
    }
    
    delay(3000);
} 