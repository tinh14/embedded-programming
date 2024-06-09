#include <ArduinoJson.h>

#include "TemperatureHumiditySensor.h"
#include "SoilMoistureSensor.h"
#include "Displayer.h"

// Số lượng bit được truyền trong 1 giây
const unsigned long baudRate = 115200;

// Khai báo các tham số cho cảm biến nhiệt độ, độ ẩm
const int dhtSensorPin = 9;
const int dhtType = DHT11;

// Khai báo các tham số cho cảm biến độ ẩm đất
const int smsPin = A0;
const int smsPowerPin = 7;

// Khai báo các tham số cho màn hình hiển thị
const int displayerAddr = 0x27;
const int displayerCols = 20;
const int displayerRows = 4;

// Khai báo các đối tượng cảm biến và màn hình hiển thị
TemperatureHumiditySensor tths(dhtSensorPin, dhtType);
SoilMoistureSensor sm(smsPin, smsPowerPin);
Displayer displayer(displayerAddr, displayerCols, displayerRows);

void setup() { 
    // Khởi tạo cổng Serial, cảm biến và màn hình hiển thị
    Serial.begin(baudRate);
    tths.begin();
    sm.begin();
    displayer.begin();

    // Hiển thị tiêu đề cho màn hình hiển thị
    displayer.display(0, 0, "Nhiet do: ");
    displayer.display(0, 1, "Do am: ");
    displayer.display(0, 2, "Do am dat: ");
}

void loop() {
    // Đọc dữ liệu từ các cảm biến
    int tem = tths.readTemperature(); 
    int hum = tths.readHumidity(); 
    int soil = sm.readMoisture(); 

    // Định dạng dữ liệu hiển thị
    String displayedTemp = String(tem) + " C";
    String displayedHum = String(hum) + " %";
    String displayedSoi = String(soil) + " %";
    
    // Hiển thị dữ liệu lên màn hình hiển thị
    displayer.display(11, 0, displayedTemp);
    displayer.display(11, 1, displayedHum);
    displayer.display(11, 2, displayedSoi);

    // Khởi tạo một đối tượng JSON
    StaticJsonDocument<200> doc;
    // Đưa dữ liệu cảm biến vào đối tượng JSON
    doc["temperature"] = tem;
    doc["humidity"] = hum;
    doc["soilMoisture"] = soil;

    // Khai báo một chuỗi để lưu trữ dữ liệu JSON
    String sensorJsonData;
    // Chuyển đối tượng JSON thành chuỗi JSON
    serializeJson(doc, sensorJsonData);

    // Truyền dữ liệu JSON qua cổng Serial
    Serial.println(sensorJsonData);

    // Đợi 3 giây cho lần truyền dữ liệu tiếp theo
    delay(3000);
}
