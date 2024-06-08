#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include <Arduino.h>

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

void SoilMoistureSensor::begin() {
    pinMode(sensorPowerPin, OUTPUT);
    digitalWrite(sensorPowerPin, LOW);
}

int SoilMoistureSensor::readMoisture() {
    digitalWrite(sensorPowerPin, HIGH);
    delay(10);

    int analogValue = analogRead(sensorPin);
    int moisturePercentage = map(analogValue, 0, 1023, 0, 100);

    digitalWrite(sensorPowerPin, LOW);
    return moisturePercentage;
}

#endif