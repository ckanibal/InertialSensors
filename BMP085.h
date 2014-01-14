// BMP085.h

#ifndef BMP085_H
#define BMP085_H

#include "register.h"

struct BMP085 {
  int ac1;
  int ac2;
  int ac3;
  unsigned int ac4;
  unsigned int ac5;
  unsigned int ac6;
  int b1;
  int b2;
  int mb;
  int mc;
  int md;
  
  long b5;
};
typedef struct BMP085 BMP085;

void initBMP085(int device, BMP085 *data);
void readTemperature(int device, unsigned int *data);
void readPressure(int device, unsigned long *data);

float getTemperature(unsigned int raw, BMP085 *data);
unsigned long getPressure(unsigned long raw, BMP085 *data);

#endif
