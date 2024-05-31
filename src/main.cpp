#include <Arduino.h>
#include "BME280.hpp"

BME280 sensor;

void setup() {
    sensor.begin();
    Serial.begin(9600);
}

void loop() {
    float temperature = sensor.getTemperature();
    float pressure = sensor.getPressure();
    float humidity = sensor.getHumidity();

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
    Serial.println("==========================");
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" hPa");
    Serial.println("==========================");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %RH");
    Serial.println("==========================");
    delay(1000);
}