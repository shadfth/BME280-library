#include <Arduino.h>
#include "BME280.hpp"

BME280 sensor;
// constants won't change
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N

void setup() {
    sensor.begin(sensor.force_mode);
    Serial.begin(9600);
    pinMode(ENA_PIN, OUTPUT);
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);

    digitalWrite(ENA_PIN, HIGH);

}

void loop() {
    sensor.begin(sensor.force_mode);
    BME280::SensorData data = sensor.getAll();
    float temperature = sensor.getTemperature();

    if(temperature > 25.0){
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
    }

    // trekt de actuator in als de temperatuur onder een bepaalde waarde komt.
    if(temperature < 24.5){
        digitalWrite(IN1_PIN, LOW);
        digitalWrite(IN2_PIN, HIGH);
    }
    Serial.println(temperature);
    delay(5000);
}