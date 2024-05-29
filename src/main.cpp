#include <Arduino.h>
#include "BME280.hpp"

BME280 sensor{};

void setup() {
    sensor.initSensor();
    Serial.begin(9600);
    Wire.beginTransmission(0x76);
    Wire.write(0xf4);
    Wire.write(0b01001011);
    Wire.endTransmission();
}

void loop() {
    Wire.beginTransmission(0x76);
    Wire.write(0xfa);
    Wire.endTransmission();
    Wire.requestFrom(0b1110110, 3);
    while (Wire.available()){
        int i = Wire.read();
        Serial.println(i);
    }
    Serial.println("==========================");
    delay(1000);
}