#ifndef HTTP_SENDER_H
#define HTTP_SENDER_H

#include <ESP8266HTTPClient.h>

// Lớp HTTPSender dùng để gửi dữ liệu lên server thông qua giao thức HTTP
class HTTPSender {
public:
    HTTPSender(String serverUrl);
    void setServerUrl(String serverUrl);
    void send(String sensorJsonData);
private:
    String serverUrl;
    // Loại dữ liệu mặc định được gửi lên server (json)
    String defaultContentType = "application/json";
    // WifiClient để thiết lập kết nối TCP đến server
    WiFiClient wifiClient;
};

HTTPSender::HTTPSender(String serverUrl) : serverUrl(serverUrl) {}

// Gửi dữ liệu đến server
void HTTPSender::send(String sensorJsonData) {
    // Khởi tạo đối tượng HTTPClient để gửi yêu cầu HTTP
    HTTPClient http;
    
    // Bắt đầu kết nối đến server
    http.begin(wifiClient, serverUrl);
    // Đặt kiểu dữ liệu của dữ liệu gửi lên server
    http.addHeader("Content-Type", defaultContentType);
    
    // Gửi một yêu cầu POST đến server với dữ liệu là chuỗi sensorJsonData
    http.POST(sensorJsonData);

    // Đóng kết nối đến server
    http.end();
}

#endif