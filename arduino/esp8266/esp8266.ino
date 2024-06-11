#include <ESP8266WiFi.h> 
#include "WiFiConnector.h"
#include "HTTPSender.h"

// Số lượng bit được truyền trong 1 giây
const unsigned long baudRate = 115200;

// Khai báo các thông số cho kết nối WiFi
String ssid = "DatG"; 
String password = "Dattran1234"; 

// Địa chỉ của server nhận dữ liệu
String serverUrl = "http://192.168.144.224:8080/api/v1/sensors";

// Khai báo các đối tượng kết nối WiFi và gửi yêu cầu HTTP 
WiFiConnector wifiConnector;
HTTPSender httpSender(serverUrl);
 
void setup() { 
    // Khởi tạo cổng Serial
    Serial.begin(baudRate);
    // Kết nối WiFi
    wifiConnector.connect(ssid, password);
}
 
void loop() { 
    // Kiểm tra xem dữ liệu có tồn tại trên cổng Serial không
    while (Serial.available() == 0){}

    // Đọc dữ liệu từ cổng Serial
    String sensorJsonData = Serial.readStringUntil('\n');

    // Gửi dữ liệu lên server
    httpSender.send(sensorJsonData);
} 