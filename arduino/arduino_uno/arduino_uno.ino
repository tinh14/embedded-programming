#include "TemperatureHumiditySensor.h"
#include "SoilMoistureSensor.h"
#include "Displayer.h"
#include "../shared/SensorData.h"

const unsigned long baudRate = 115200;

const int dhtSensorPin = 9;
const int dhtType = DHT11;

const int smsPin = A0;
const int smsPowerPin = 7;

const int displayerAddr = 0x27;
const int displayerCols = 20;
const int displayerRows = 4;

TemperatureHumiditySensor tths(dhtSensorPin, dhtType);
SoilMoistureSensor sm(smsPin, smsPowerPin);
Displayer displayer(displayerAddr, displayerCols, displayerRows);

void setup() { 
    Serial.begin(baudRate);
    tths.begin();
    sm.begin();
    displayer.begin();

    displayer.display(0, 0, "Nhiet do: ");
    displayer.display(0, 1, "Do am: ");
    displayer.display(0, 2, "Do am dat: ");
}

void loop() {
    int tem = tths.readTemperature(); 
    int hum = tths.readHumidity(); 
    int soil = sm.readMoisture(); 

    SensorData sensorData(tem, hum, soil);
    
    Serial.println(sensorData.toJson());

    String displayedTemp = String(tem) + " C";
    String displayedHum = String(hum) + " %";
    String displayedSoi = String(soil) + " W";
    
    displayer.display(11, 0, displayedTemp);
    displayer.display(11, 1, displayedHum);
    displayer.display(11, 2, displayedSoi);

    delay(3000);
}
