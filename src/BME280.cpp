#include "BME280.hpp"

void BME280::initSensor(){
    Wire.begin(sensor_address);
    Wire.beginTransmission(sensor_address);
    Wire.write(config_address);
    Wire.write(0b01001011);
    Wire.endTransmission();
}

BME280::BME280(){}