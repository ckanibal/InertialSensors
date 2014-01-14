// register.h

#ifndef REGISTER_H
#define REGISTER_H

#include <Arduino.h>
#include <Wire.h>

void setRegister(int device, byte reg, byte val);
byte readRegister(int device, byte reg);
int readRegisterInt(int device, byte reg);

#endif REGISTER_H
