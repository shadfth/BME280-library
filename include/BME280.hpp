// =============================================================
//
// File         : BME280.hpp
// Copyright    : shad.fatah@student.hu.nl 2024
//
// =============================================================

// this file contains Doxygen comments
/// @file BME280.hpp

#ifndef BME280_HPP
#define BME280_HPP

#include <Wire.h>

/**
 * @class BME280 BME280.hpp 
*/
class BME280
{
private:
    /// @brief const variable addresses and writing data addresses.
    const uint8_t humidty_oversampling = 0x01;
    const uint8_t ctrl_hum = 0xf2;
    const uint8_t config_address = 0xF5;
    const uint8_t control_address = 0xF4;
    const uint8_t pressure_address = 0xF7;
    const uint8_t temp_address = 0xFA;
    const uint8_t hum_address = 0xFD;
    const uint8_t complete_data_address = 0xF7;

    /// @brief constant compensation data addresses.
    const uint8_t dig_T1_lsb_address = 0x88;
    const uint8_t dig_T1_msb_address = 0x89;
    const uint8_t dig_T2_lsb_address = 0x8a;
    const uint8_t dig_T2_msb_address = 0x8b;
    const uint8_t dig_T3_lsb_address = 0x8c;
    const uint8_t dig_T3_msb_address = 0x8d;
    const uint8_t dig_P1_lsb_address = 0x8e;
    const uint8_t dig_P1_msb_address = 0x8f;
    const uint8_t dig_P2_lsb_address = 0x90;
    const uint8_t dig_P2_msb_address = 0x91;
    const uint8_t dig_P3_lsb_address = 0x92;
    const uint8_t dig_P3_msb_address = 0x93;
    const uint8_t dig_P4_lsb_address = 0x94;
    const uint8_t dig_P4_msb_address = 0x95;
    const uint8_t dig_P5_lsb_address = 0x96;
    const uint8_t dig_P5_msb_address = 0x97;
    const uint8_t dig_P6_lsb_address = 0x98;
    const uint8_t dig_P6_msb_address = 0x99;
    const uint8_t dig_P7_lsb_address = 0x9a;
    const uint8_t dig_P7_msb_address = 0x9b;
    const uint8_t dig_P8_lsb_address = 0x9c;
    const uint8_t dig_P8_msb_address = 0x9d;
    const uint8_t dig_P9_lsb_address = 0x9e;
    const uint8_t dig_P9_msb_address = 0x9f;
    const uint8_t dig_H1_address = 0xa1;
    const uint8_t dig_H2_lsb_address = 0xe1;
    const uint8_t dig_H2_msb_address = 0xe2;
    const uint8_t dig_H3_address = 0xe3;
    const uint8_t dig_H4_msb_address = 0xe4;
    const uint8_t dig_H4_lsb_address = 0xe5;
    const uint8_t dig_H5_lsb_address = 0xe5;
    const uint8_t dig_H5_msb_address = 0xe6;
    const uint8_t dig_H6_address = 0xe7;

    /// @brief declaring sensor address
    uint8_t _sensor_address;


    /// @brief compensation data.
    int8_t dig_H6;
    uint8_t dig_H1, dig_H3;
    uint16_t dig_T1, dig_P1;
    int16_t dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9, dig_H2, dig_H4, dig_H5;
    int32_t t_fine;

    /// @brief function to read all of the calibration.
    void readCalibrationData();
    uint8_t read8(uint8_t reg);
    int8_t read8S(uint8_t reg);
    uint16_t read16_lsb(uint8_t reg);
    uint16_t read16_msb(uint8_t reg);
    int16_t readS16_lsb(uint8_t reg);
    int16_t readS16_msb(uint8_t reg);
    int32_t read24(uint8_t reg);
    int32_t compensateTemperature(int32_t adc_T);
    uint32_t compensatePressure(int32_t adc_P);
    uint32_t compensateHumidity(int32_t adc_H);

public:
    BME280(uint8_t sensor_address = 0x76);
    const uint8_t normal_mode = 0x27;
    const uint8_t force_mode = 0x25;
    const uint8_t sleep_mode = 0x24;
        
    struct SensorData {
        float temperature;
        float pressure;
        float humidity;
    };
    bool begin(uint8_t mode);
    SensorData getAll();
    float getTemperature();
    float getPressure();
    float getHumidity();
};

#endif // BME280_HPP