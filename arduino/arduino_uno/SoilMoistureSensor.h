#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include <Arduino.h>

// Lớp SoilMoistureSensor dùng để đọc dữ liệu từ cảm biến độ ẩm đất
class SoilMoistureSensor {
public:
    SoilMoistureSensor(int sensorPin, int sensorPowerPin);
    void begin();
    int readMoisture();
private:
    int sensorPin;
    int sensorPowerPin;
};

SoilMoistureSensor::SoilMoistureSensor(int sensorPin, int sensorPowerPin) : sensorPin(sensorPin), sensorPowerPin(sensorPowerPin) {}

// Khởi tạo cảm biến độ ẩm đất
void SoilMoistureSensor::begin() {
    // Khai báo chân cảm biến độ ẩm đất là OUTPUT
    pinMode(sensorPowerPin, OUTPUT);
    // Tắt nguồn điện cho cảm biến
    digitalWrite(sensorPowerPin, LOW);
}

// Đọc dữ liệu từ cảm biến độ ẩm đất
int SoilMoistureSensor::readMoisture() {
    // Bật nguồn điện cho cảm biến
    digitalWrite(sensorPowerPin, HIGH);
    // Đợi cảm biến ổn định
    delay(10);

    // Đọc giá trị analog từ cảm biến
    int analogValue = analogRead(sensorPin);
    // Chuyển giá trị analog sang phần trăm độ ẩm
    int moisturePercentage = map(analogValue, 0, 1023, 0, 100);

    // Tắt nguồn điện cho cảm biến
    digitalWrite(sensorPowerPin, LOW);

    return moisturePercentage;
}

#endif