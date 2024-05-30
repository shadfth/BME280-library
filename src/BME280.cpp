#include "BME280.hpp"

BME280::BME280(uint8_t sensor_address)
    : _sensor_address(sensor_address) {}

bool BME280::begin()
{
    Wire.begin();
    readCalibrationData();

    Wire.beginTransmission(_sensor_address);
    Wire.write(0xF2); // ctrl_hum register
    Wire.write(0x01); // humidity oversampling x1
    Wire.write(0xF4); // ctrl_meas register
    Wire.write(0x27); // temp and pressure oversampling x1, mode normal
    Wire.endTransmission();

    return true;
}

void BME280::readCalibrationData()
{
    dig_T1 = read16(0x88);
    dig_T2 = readS16S(0x8A);
    dig_T3 = readS16S(0x8C);
}

uint16_t BME280::read16(uint8_t reg)
{
    uint16_t value;
    Wire.beginTransmission(_sensor_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_sensor_address, (uint8_t)2);
    value = (Wire.read() | (Wire.read() << 8));
    return value;
}

int16_t BME280::readS16S(uint8_t reg)
{
    return (int16_t)read16(reg);
}

int32_t BME280::read24(uint8_t reg)
{
    uint32_t value;
    Wire.beginTransmission(_sensor_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_sensor_address, (uint8_t)3);
    value = Wire.read();
    value <<= 8;
    value |= Wire.read();
    value <<= 8;
    value |= Wire.read();
    return (int32_t)value;
}

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
// t_fine carries fine temperature as global value
int32_t BME280::compensateTemperature(int32_t adc_T) {
  int32_t var1, var2, T;
  var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
  var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
  t_fine = var1 + var2;
  T = (t_fine * 5 + 128) >> 8;
  return T;
}

float BME280::getTemperature() {
  int32_t adc_T = read24(0xFA) >> 4;
  int32_t temp = compensateTemperature(adc_T);
  return temp / 100.0;
}