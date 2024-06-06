#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include "WiFiConnector.h"
#include "HTTPSender.h"

String ssid = "Unnamed"; 
String password = "12345678"; 
String serverUrl = "http://192.168.106.224:8080/api/v1/sensors";

const unsigned long baudRate = 115200;

WiFiConnector wifiConnector;
HTTPSender httpSender(serverUrl);
 
void setup() { 
    Serial.begin(baudRate);
    wifiConnector.connect(ssid, password);
} 
 
void loop() { 
  if (Serial.available() > 0) {
      String sensorJsonData = Serial.readStringUntil('\n'); 
      httpSender.send(sensorJsonData);
    }
    
    delay(3000);
} 