#include <Arduino.h>
#include "BME280.hpp"

BME280 sensor;

void setup() {
    sensor.begin();
    Serial.begin(9600);
}

void loop() {
    float temperature = sensor.getTemperature();
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("*C");
    Serial.println("==========================");
    delay(1000);
}