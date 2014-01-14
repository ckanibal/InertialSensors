// BMP085.cpp

#include "BMP085.h"

void initBMP085(int device, BMP085 *data) {
  data->ac1 = readRegisterInt(device, 0xAA);
  data->ac2 = readRegisterInt(device, 0xAC);
  data->ac3 = readRegisterInt(device, 0xAE);
  data->ac4 = readRegisterInt(device, 0xB0);
  data->ac5 = readRegisterInt(device, 0xB2);
  data->ac6 = readRegisterInt(device, 0xB4);
  
  data->b1 = readRegisterInt(device, 0xB6);
  data->b2 = readRegisterInt(device, 0xB6);
  
  data->mb = readRegisterInt(device, 0xBA);
  data->mc = readRegisterInt(device, 0xBC);
  data->md = readRegisterInt(device, 0xBE);
}

void readTemperature(int device, unsigned int *data) {
  setRegister(device, 0xF4, 0x2E); // request temperature
  delay(5); // wait for the sensor to provide the data
  *data = readRegisterInt(device, 0xF6);
}

void readPressure(int device, unsigned long *data) {
  unsigned char msb, lsb, xlsb;

  setRegister(device, 0xF4, 0x34);
  delay(5);
  
  msb = readRegister(device, 0xF6);
  lsb = readRegister(device, 0xF7);
  xlsb = readRegister(device, 0xF8);

  *data = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb);
}

float getTemperature(unsigned int raw, BMP085 *data) {
  long x1, x2;
  
  x1 = (((long)raw - (long)data->ac6)*(long)data->ac5) >> 15;
  x2 = ((long)data->mc << 11)/(x1 + data->md);
  data->b5 = x1 + x2;

  float temp = ((data->b5 + 8)>>4);
  temp = temp /10;
  
  return temp;
}

unsigned long getPressure(unsigned long raw, BMP085 *data) {
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;

  b6 = data->b5 - 4000;
  // Calculate B3
  x1 = (data->b2 * (b6 * b6)>>12)>>11;
  x2 = (data->ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)data->ac1)*4 + x3)) + 2)>>2;

  // Calculate B4
  x1 = (data->ac3 * b6)>>13;
  x2 = (data->b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (data->ac4 * (unsigned long)(x3 + 32768))>>15;

  b7 = ((unsigned long)(raw - b3) * 50000);
  if (b7 < 0x80000000) {
    p = (b7<<1)/b4;
  } else {
    p = (b7/b4)<<1;
  }

  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}
