// Vector3.cpp

#include "Vector3.h"

void printVector(Vector3 *data) {
  Serial.print("(x= ");
  Serial.print(data->x);
  Serial.print("; y= ");
  Serial.print(data->y);
  Serial.print("; z= ");
  Serial.print(data->z);
  Serial.println(")");
}
