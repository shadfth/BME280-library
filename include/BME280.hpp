#ifndef BME280_HPP
#define BME280_HPP

#include <Wire.h>

class BME280
{
private:
    const uint8_t config_address = 0xF5;
    const uint8_t control_address = 0xF4;
    const uint8_t sensor_address = 0x76;
    void byteRead(uint8_t address, unsigned int length);

public:
    void initSensor();
    BME280();
    void changeMode();
    void temperatureRead();
    void humidityRead();
    void airpressureRead();
};

#endif // BME280_HPP