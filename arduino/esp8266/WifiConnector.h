#ifndef WIFI_CONNECTOR_H
#define WIFI_CONNECTOR_H

#include <ESP8266WiFi.h>

// Lớp WiFiConnector dùng để quản lý việc kết nối với mạng WiFi
class WiFiConnector {
public:
    WiFiConnector();
    void connect(String ssid, String password);
    bool isConnected();
};

WiFiConnector::WiFiConnector() {}

// Kết nối ESP8266 với mạng WiFi
void WiFiConnector::connect(String ssid, String password) {
    // Bắt đầu kết nối với mạng WiFi
    WiFi.begin(ssid, password);
    // Đợi cho đến khi kết nối thành công
    while (!isConnected()) {
        delay(1000);
        Serial.print(".");
    }
    // In ra màn hình Serial thông báo kết nối thành công
    Serial.println("Connected to WiFi");
}

// Kiểm tra xem ESP8266 đã kết nối với mạng WiFi chưa
bool WiFiConnector::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

#endif