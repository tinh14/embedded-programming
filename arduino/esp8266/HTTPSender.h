#ifndef HTTP_SENDER_H
#define HTTP_SENDER_H

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class HTTPSender {
public:
    HTTPSender(String serverUrl);
    void setServerUrl(String serverUrl);
    void send(String sensorJsonData);
private:
    String serverUrl;
    String defaultContentType = "application/json";
};

HTTPSender::HTTPSender(String serverUrl) : serverUrl(serverUrl) {}

void HTTPSender::send(String sensorJsonData) {

    HTTPClient http;
    WiFiClient wifiClient;
    http.begin(wifiClient, serverUrl);
    http.addHeader("Content-Type", defaultContentType);
    
    http.POST(sensorJsonData);

    http.end();
}

#endif