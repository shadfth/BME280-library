#include <Arduino.h>
#include "BME280.hpp"

BME280 sensor;

void setup() {
    sensor.begin(sensor.force_mode);
    Serial.begin(9600);
}

void loop() {
    sensor.begin(sensor.force_mode);
    BME280::SensorData data = sensor.getAll();
    float temperature = sensor.getTemperature();
    float pressure = sensor.getPressure();
    float humidity = sensor.getHumidity();

    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.println("°C");
    Serial.println("==========================");
    Serial.print("Pressure: ");
    Serial.print(data.pressure);
    Serial.println(" hPa");
    Serial.println("==========================");
    Serial.print("Humidity: ");
    Serial.print(data.humidity);
    Serial.println(" %RH");
    Serial.println("==========================");
    delay(1000);
}