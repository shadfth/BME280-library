// =============================================================
//
// File         : BME280.hpp
// Copyright    : shad.fatah@student.hu.nl 2024
//
// =============================================================

// This file contains Doxygen comments
/// @file BME280.hpp

#ifndef BME280_HPP
#define BME280_HPP

#include <Wire.h>

/**
 * @class BME280
 * @brief A class to interface with the BME280 sensor to read temperature, pressure, and humidity.
 */
class BME280
{
private:
    /// @brief Constant variable addresses and writing data addresses.
    const uint8_t humidty_oversampling = 0x01;  ///< Humidity oversampling setting.
    const uint8_t ctrl_hum = 0xf2;              ///< Control register for humidity.
    const uint8_t config_address = 0xF5;        ///< Configuration register.
    const uint8_t control_address = 0xF4;       ///< Control register for measurements.
    const uint8_t pressure_address = 0xF7;      ///< Pressure data address.
    const uint8_t temp_address = 0xFA;          ///< Temperature data address.
    const uint8_t hum_address = 0xFD;           ///< Humidity data address.
    const uint8_t complete_data_address = 0xF7; ///< Complete data start address.

    /// @brief Constant compensation data addresses.
    const uint8_t dig_T1_lsb_address = 0x88; ///< LSB of T1 compensation data.
    const uint8_t dig_T1_msb_address = 0x89; ///< MSB of T1 compensation data.
    const uint8_t dig_T2_lsb_address = 0x8a; ///< LSB of T2 compensation data.
    const uint8_t dig_T2_msb_address = 0x8b; ///< MSB of T2 compensation data.
    const uint8_t dig_T3_lsb_address = 0x8c; ///< LSB of T3 compensation data.
    const uint8_t dig_T3_msb_address = 0x8d; ///< MSB of T3 compensation data.
    const uint8_t dig_P1_lsb_address = 0x8e; ///< LSB of P1 compensation data.
    const uint8_t dig_P1_msb_address = 0x8f; ///< MSB of P1 compensation data.
    const uint8_t dig_P2_lsb_address = 0x90; ///< LSB of P2 compensation data.
    const uint8_t dig_P2_msb_address = 0x91; ///< MSB of P2 compensation data.
    const uint8_t dig_P3_lsb_address = 0x92; ///< LSB of P3 compensation data.
    const uint8_t dig_P3_msb_address = 0x93; ///< MSB of P3 compensation data.
    const uint8_t dig_P4_lsb_address = 0x94; ///< LSB of P4 compensation data.
    const uint8_t dig_P4_msb_address = 0x95; ///< MSB of P4 compensation data.
    const uint8_t dig_P5_lsb_address = 0x96; ///< LSB of P5 compensation data.
    const uint8_t dig_P5_msb_address = 0x97; ///< MSB of P5 compensation data.
    const uint8_t dig_P6_lsb_address = 0x98; ///< LSB of P6 compensation data.
    const uint8_t dig_P6_msb_address = 0x99; ///< MSB of P6 compensation data.
    const uint8_t dig_P7_lsb_address = 0x9a; ///< LSB of P7 compensation data.
    const uint8_t dig_P7_msb_address = 0x9b; ///< MSB of P7 compensation data.
    const uint8_t dig_P8_lsb_address = 0x9c; ///< LSB of P8 compensation data.
    const uint8_t dig_P8_msb_address = 0x9d; ///< MSB of P8 compensation data.
    const uint8_t dig_P9_lsb_address = 0x9e; ///< LSB of P9 compensation data.
    const uint8_t dig_P9_msb_address = 0x9f; ///< MSB of P9 compensation data.
    const uint8_t dig_H1_address = 0xa1;     ///< H1 compensation data address.
    const uint8_t dig_H2_lsb_address = 0xe1; ///< LSB of H2 compensation data.
    const uint8_t dig_H2_msb_address = 0xe2; ///< MSB of H2 compensation data.
    const uint8_t dig_H3_address = 0xe3;     ///< H3 compensation data address.
    const uint8_t dig_H4_msb_address = 0xe4; ///< MSB of H4 compensation data.
    const uint8_t dig_H4_lsb_address = 0xe5; ///< LSB of H4 compensation data.
    const uint8_t dig_H5_lsb_address = 0xe5; ///< LSB of H5 compensation data.
    const uint8_t dig_H5_msb_address = 0xe6; ///< MSB of H5 compensation data.
    const uint8_t dig_H6_address = 0xe7;     ///< H6 compensation data address.

    /// @brief Declaring sensor address.
    uint8_t _sensor_address;

    /// @brief Compensation data.
    int8_t dig_H6;                                                                                                  ///< H6 compensation data.
    uint8_t dig_H1, dig_H3;                                                                                         ///< H1 and H3 compensation data.
    uint16_t dig_T1, dig_P1;                                                                                        ///< T1 and P1 compensation data.
    int16_t dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9, dig_H2, dig_H4, dig_H5; ///< Other compensation data.
    int32_t t_fine;                                                                                                 ///< Fine temperature variable for compensation calculations.

    /**
     * @brief Reads all the calibration data from the sensor.
     */
    void readCalibrationData();

    /**
     * @brief Reads an 8-bit value from the specified register.
     * @param reg The register address.
     * @return The 8-bit value read from the register.
     */
    uint8_t read8(uint8_t reg);

    /**
     * @brief Reads an 8-bit signed value from the specified register.
     * @param reg The register address.
     * @return The 8-bit signed value read from the register.
     */
    int8_t read8S(uint8_t reg);

    /**
     * @brief Reads a 16-bit value from the specified register with LSB first.
     * @param reg The register address.
     * @return The 16-bit value read from the register.
     */
    uint16_t read16_lsb(uint8_t reg);

    /**
     * @brief Reads a 16-bit value from the specified register with MSB first.
     * @param reg The register address.
     * @return The 16-bit value read from the register.
     */
    uint16_t read16_msb(uint8_t reg);

    /**
     * @brief Reads a 16-bit signed value from the specified register with LSB first.
     * @param reg The register address.
     * @return The 16-bit signed value read from the register.
     */
    int16_t readS16_lsb(uint8_t reg);

    /**
     * @brief Reads a 16-bit signed value from the specified register with MSB first.
     * @param reg The register address.
     * @return The 16-bit signed value read from the register.
     */
    int16_t readS16_msb(uint8_t reg);

    /**
     * @brief Reads a 24-bit value from the specified register.
     * @param reg The register address.
     * @return The 24-bit value read from the register.
     */
    int32_t read24(uint8_t reg);

    /**
     * @brief Compensates the raw temperature value.
     * @param adc_T The raw temperature value.
     * @return The compensated temperature value.
     */
    int32_t compensateTemperature(int32_t adc_T);

    /**
     * @brief Compensates the raw pressure value.
     * @param adc_P The raw pressure value.
     * @return The compensated pressure value.
     */
    uint32_t compensatePressure(int32_t adc_P);

    /**
     * @brief Compensates the raw humidity value.
     * @param adc_H The raw humidity value.
     * @return The compensated humidity value.
     */
    uint32_t compensateHumidity(int32_t adc_H);

public:
    /**
     * @brief Constructor for BME280 class.
     * @param sensor_address The I2C address of the sensor.
     */
    BME280(uint8_t sensor_address = 0x76);

    const uint8_t normal_mode = 0x27; ///< Normal mode setting.
    const uint8_t force_mode = 0x25;  ///< Forced mode setting.
    const uint8_t sleep_mode = 0x24;  ///< Sleep mode setting.

    /**
     * @struct SensorData
     * @brief Structure to hold temperature, pressure, and humidity data.
     */
    struct SensorData
    {
        float temperature; ///< Temperature value.
        float pressure;    ///< Pressure value.
        float humidity;    ///< Humidity value.
    };

    /**
     * @brief Initializes the sensor with the specified mode.
     * @param mode The mode to set for the sensor.
     * @return True if initialization is successful, otherwise false.
     */
    bool begin(uint8_t mode);

    /**
     * @brief Reads all sensor data (temperature, pressure, and humidity).
     * @return A SensorData structure containing the sensor data.
     */
    SensorData getAll();

    /**
     * @brief Reads the temperature from the sensor.
     * @return The temperature value.
     */
    float getTemperature();

    /**
     * @brief Reads the pressure from the sensor.
     * @return The pressure value.
     */
    float getPressure();

    /**
     * @brief Reads the humidity from the sensor.
     * @return The humidity value.
     */
    float getHumidity();
};

#endif // BME280_HPP
