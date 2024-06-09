#include <ESP8266WiFi.h> 
#include "WiFiConnector.h"
#include "HTTPSender.h"

// Số lượng bit được truyền trong 1 giây
const unsigned long baudRate = 115200;

// Khai báo các thông số cho kết nối WiFi và gửi dữ liệu
String ssid = "Chi Huy"; 
String password = "999999999"; 

// Địa chỉ của server nhận dữ liệu
String serverUrl = "http://192.168.1.101:8080/api/v1/sensors";

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
    // Định nghĩa một biến lưu trữ dữ liệu được đọc từ cổng Serial
    String sensorJsonData = "";
    // Định nghĩa một biến kiểm tra xem đã nhận đủ dữ liệu chưa
    bool received = false;

    // Kiểm tra xem dữ liệu có tồn tại trên cổng Serial không
    while (Serial.available() > 0) {
      // Đọc một ký tự từ cổng Serial
      char incomingChar = Serial.read();
      // Nếu ký tự đọc được là ký tự xuống dòng thì dừng việc đọc dữ liệu
      if (incomingChar == '\n') {
        received = true;
        break;
      }
      // Nếu ký tự đọc được không phải là ký tự xuống dòng thì thêm vào chuỗi dữ liệu
      sensorJsonData += incomingChar;
    }

    // Nếu đã nhận đủ dữ liệu thì gửi dữ liệu lên server
    if (received) {
      httpSender.send(sensorJsonData);
    }
    
    // Đợi 3 giây trước khi gửi dữ liệu tiếp theo
    delay(3000);
} 