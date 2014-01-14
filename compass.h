// compass.h

#ifndef COMPASS_H
#define COMPASS_H

#include "Vector3.h"
#include "register.h"

void initCompass(int device);
void readCompass(int device, Vector3 *data);

#endif
