#include <ArduinoJson.h>

class SensorData {
public:
    SensorData(int temp, int hum, int soil) {
        temperature = temp;
        humidity = hum;
        soilMoisture = soil;
    }

    String toJson() {
        DynamicJsonDocument doc(200);
        doc["temperature"] = temperature;
        doc["humidity"] = humidity;
        doc["soilMoisture"] = soilMoisture;

        String json;
        serializeJson(doc, json);
        return json;
    }

private:
    int temperature;
    int humidity;
    int soilMoisture;
};