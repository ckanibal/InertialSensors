// gyro.h

#ifndef GYRO_H
#define GYRO_H

#include "Vector3.h"

void initGyro(int device);
void readGyro(int device, Vector3 *data);

#endif


