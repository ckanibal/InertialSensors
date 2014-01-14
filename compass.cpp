// compass.cpp

#include "compass.h"

void initCompass(int device) {
  // setup HMC5883(compass) operating mode
  setRegister(device, 0x02, 0x00);
}

void readCompass(int device, Vector3 *data) {
  Wire.beginTransmission(device);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
  Wire.requestFrom(device, 6);
  while(Wire.available() < 6) {
    // wait
  }
  data->x = Wire.read() << 8; //X msb
  data->x |= Wire.read(); //X lsb
  data->z = Wire.read() << 8; //Z msb
  data->z |= Wire.read(); //Z lsb
  data->y = Wire.read() << 8; //Y msb
  data->y |= Wire.read(); //Y lsb
}
