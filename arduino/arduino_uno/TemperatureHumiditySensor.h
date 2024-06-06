#ifndef TEMPERATURE_HUMIDITY_SENSOR_H
#define TEMPERATURE_HUMIDITY_SENSOR_H

#include <DHT.h>

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

void TemperatureHumiditySensor::begin() {
    dht.begin();
}

float TemperatureHumiditySensor::readTemperature() {
    return dht.readTemperature();
}

float TemperatureHumiditySensor::readHumidity() {
    return dht.readHumidity();
}

#endif