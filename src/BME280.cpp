#include "BME280.hpp"

BME280::BME280(uint8_t sensor_address)
    : _sensor_address(sensor_address) {}

bool BME280::begin(uint8_t mode)
{
    Wire.begin();
    readCalibrationData();

    Wire.beginTransmission(_sensor_address);
    Wire.write(ctrl_hum); // ctrl_hum register
    Wire.write(humidty_oversampling); // humidity oversampling x1
    Wire.write(control_address); // ctrl_meas register
    Wire.write(mode); // temp and pressure oversampling x1, mode
    Wire.endTransmission();

    return true;
}

void BME280::readCalibrationData()
{
    dig_T1 = read16_lsb(dig_T1_lsb_address);
    dig_T2 = readS16_lsb(dig_T2_lsb_address);
    dig_T3 = readS16_lsb(dig_T3_lsb_address);
    dig_P1 = read16_lsb(dig_P1_lsb_address);
    dig_P2 = read16_lsb(dig_P2_lsb_address);
    dig_P3 = read16_lsb(dig_P2_lsb_address);
    dig_P4 = read16_lsb(dig_P4_lsb_address);
    dig_P5 = read16_lsb(dig_P5_lsb_address);
    dig_P6 = read16_lsb(dig_P6_lsb_address);
    dig_P7 = read16_lsb(dig_P7_lsb_address);
    dig_P8 = read16_lsb(dig_P8_lsb_address);
    dig_P9 = read16_lsb(dig_P9_lsb_address);
    dig_H1 = read8(dig_H1_address);
    dig_H2 = readS16_lsb(dig_H2_lsb_address);
    dig_H3 = read8(dig_H3_address);
    dig_H4 = (int16_t)((read8(dig_H4_msb_address) << 4 | read8(dig_H4_lsb_address) & 0b00001111));
    dig_H5 = (int16_t)((read8(dig_H5_lsb_address) & 0b11110000) >> 4 | read8(dig_H5_msb_address) << 4);
    dig_H6 = read8S(dig_H6_address);

}

void BME280::changeMode(){


}

uint8_t BME280::read8(uint8_t reg){
    uint8_t value;
    Wire.beginTransmission(_sensor_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_sensor_address, 1);
    value = Wire.read();
    return value;
}

int8_t BME280::read8S(uint8_t reg)
{
    return (int8_t)read8(reg);
}
uint16_t BME280::read16_lsb(uint8_t reg)
{
    uint16_t value;
    Wire.beginTransmission(_sensor_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_sensor_address, (uint8_t)2);
    value = (Wire.read() | (Wire.read() << 8));
    return value;
}

uint16_t BME280::read16_msb(uint8_t reg)
{
    uint16_t value;
    Wire.beginTransmission(_sensor_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_sensor_address, (uint8_t)2);
    value = ((Wire.read() << 8) | Wire.read());
    return value;
}

int16_t BME280::readS16_lsb(uint8_t reg)
{
    return (int16_t)read16_lsb(reg);
}

int16_t BME280::readS16_msb(uint8_t reg)
{
    return (int16_t)read16_msb(reg);
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
  int32_t adc_T = read24(temp_address) >> 4;
  int32_t temp = compensateTemperature(adc_T);
  return temp / 100.0;
}

float BME280::getPressure() {
    int32_t adc_P = read24(pressure_address) >> 4;
    uint32_t press = compensatePressure(adc_P);
    return press / 25600.0;
}

float BME280::getHumidity() {
    int32_t adc_H = read16_msb(hum_address);
    uint32_t humidity = compensateHumidity(adc_H);
    return humidity / 1024.0;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
uint32_t BME280::compensatePressure(int32_t adc_P)
{
int64_t var1, var2, p;
var1 = ((int64_t)t_fine) - 128000;
var2 = var1 * var1 * (int64_t)dig_P6;
var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
var2 = var2 + (((int64_t)dig_P4)<<35);
var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
if (var1 == 0)
{
return 0; // avoid exception caused by division by zero
}
p = 1048576-adc_P;
p = (((p<<31)-var2)*3125)/var1;
var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
var2 = (((int64_t)dig_P8) * p) >> 19;
p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
return (uint32_t)(p);
}


// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
// Output value of “47445” represents 47445/1024 = 46.333 %RH
uint32_t BME280::compensateHumidity(int32_t adc_H)
{
int32_t v_x1_u32r;
v_x1_u32r = (t_fine - ((int32_t)76800));
v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) *
v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r *
((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) +
((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_H2) +
8192) >> 14));
v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
((int32_t)dig_H1)) >> 4));
v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
return (uint32_t)(v_x1_u32r>>12);
}

