// Vector3.h

#ifndef VECTOR3_H
#define VECTOR3_H

#include <Arduino.h>

struct Vector3 {
  int x;
  int y;
  int z;
};
typedef struct Vector3 Vector3;

void printVector(Vector3 *data);

#endif
