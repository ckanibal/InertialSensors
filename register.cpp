// register.cpp

#include "register.h"

void setRegister(int device, byte reg, byte val) {
  Wire.beginTransmission(device);
  Wire.write(reg); 
  Wire.write(val);
  Wire.endTransmission();
}

byte readRegister(int device, byte reg) {
  Wire.beginTransmission(device);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(device, 1);
  while(!Wire.available()) {
  }
  byte val = Wire.read();
  return val;
}

int readRegisterInt(int device, byte reg) {
  unsigned char msb, lsb;

  Wire.beginTransmission(device);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(device, 2);
  while(Wire.available()<2) {
  }
  msb = Wire.read();
  lsb = Wire.read();

  return (int) msb<<8 | lsb;
}
