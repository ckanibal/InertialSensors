// gyro.cpp

#include "gyro.h"
#include "register.h"

void initGyro(int device) {
  // setup L3G4200D(gyro)
  setRegister(device, 0x20, 0b00001111); // CTRL_REG1
  setRegister(device, 0x21, 0b00000000); // CTRL_REG2
  setRegister(device, 0x22, 0b00001000); // CTRL_REG3
  setRegister(device, 0x23, 0b00000000); // CTRL_REG4
  setRegister(device, 0x24, 0b00010000); // CTRL_REG5
}

void readGyro(int device, Vector3 *data) {
  data->x = (readRegister(device, 0x29) << 8);
  data->x |= readRegister(device, 0x28);
  
  data->y = (readRegister(device, 0x2B) << 8);
  data->y |= readRegister(device, 0x2A);
  
  data->z = (readRegister(device, 0x2D) << 8);
  data->z |= readRegister(device, 0x2C);
}
