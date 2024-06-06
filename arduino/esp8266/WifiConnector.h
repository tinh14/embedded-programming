#ifndef WIFI_CONNECTOR_H
#define WIFI_CONNECTOR_H

#include <ESP8266WiFi.h>

class WiFiConnector {
public:
    WiFiConnector();
    void connect(String ssid, String password);
    bool isConnected();
    String getLocalIP();
};

WiFiConnector::WiFiConnector() {}

void WiFiConnector::connect(String ssid, String password) {
    WiFi.begin(ssid, password);
    while (!isConnected()) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

bool WiFiConnector::isConnected() {
   return WiFi.status() == WL_CONNECTED;
}

String WiFiConnector::getLocalIP() {
    IPAddress ip = WiFi.localIP();
    return ip.toString();
}

#endif