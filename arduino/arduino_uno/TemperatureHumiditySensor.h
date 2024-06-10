#ifndef TEMPERATURE_HUMIDITY_SENSOR_H
#define TEMPERATURE_HUMIDITY_SENSOR_H

#include <DHT.h>

// Lớp TemperatureHumiditySensor dùng để đọc dữ liệu từ cảm biến nhiệt độ, độ ẩm
class TemperatureHumiditySensor {
public:
    TemperatureHumiditySensor(int pin, int type);
    void begin();
    float readTemperature();
    float readHumidity();
private:
    DHT dht;
};

TemperatureHumiditySensor::TemperatureHumiditySensor(int pin, int type) : dht(pin, type) {}

// Khởi tạo cảm biến nhiệt độ, độ ẩm
void TemperatureHumiditySensor::begin() {
    // Khởi tạo cảm biến nhiệt độ, độ ẩm
    dht.begin();
}

// Đọc dữ liệu từ cảm biến nhiệt độ
float TemperatureHumiditySensor::readTemperature() {
    return dht.readTemperature();
}

// Đọc dữ liệu từ cảm biến độ ẩm
float TemperatureHumiditySensor::readHumidity() {
    return dht.readHumidity();
}

#endif