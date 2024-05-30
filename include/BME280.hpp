#ifndef BME280_HPP
#define BME280_HPP

#include <Wire.h>

class BME280
{
private:
    const uint8_t config_address = 0xF5;
    const uint8_t control_address = 0xF4;
    uint8_t _sensor_address;
    uint8_t _address;
    uint16_t dig_T1;
    int16_t dig_T2, dig_T3;
    int32_t t_fine;
    
    uint16_t read16(uint8_t reg);
    int16_t readS16S(uint8_t reg);
    int32_t read24(uint8_t reg);
    int32_t compensateTemperature(int32_t adc_T);

public:
    BME280(uint8_t sensor_address = 0x76);
    bool begin();
    void readCalibrationData();
    uint16_t read16(uint8_t reg);
    int16_t readS16S(uint8_t reg);
    int32_t read24(uint8_t reg);
    int32_t compensateTemperature(int32_t adc_T);
    float getTemperature();
    void changeMode();
};

#endif // BME280_HPP