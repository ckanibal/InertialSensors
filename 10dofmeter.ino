/* read all sensor values */

#include <Wire.h> //I2C Arduino Library

#include "gyro.h"
#include "compass.h"
#include "BMP085.h"

#define gyro  0x69 // L3G4200D
#define acc   0x53 // ADXL345
#define comp  0x1E // HMC5883
#define baro  0x77 // BMP085

// forward declarations
void readAccelerometer(Vector3 *data);

// variables
Vector3 compData;
Vector3 gyroData;
Vector3 accData;

BMP085 calibrationData;
 
float temp;
unsigned long pressure;

void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();
  
  initCompass(comp);
  initGyro(gyro);
  
  // setup ADXL345(accelerometer)
  // TODO
  
  // setup BMP085
  initBMP085(baro, &calibrationData);
}

void loop(){
  readCompass(comp, &compData);
  readGyro(gyro, &gyroData);
  readAccelerometer(&accData);
  
  unsigned int rawTemp;
  readTemperature(baro, &rawTemp);
  unsigned long rawPressure;
  readPressure(baro, &rawPressure);
  
  temp = getTemperature(rawTemp, &calibrationData);
  pressure = getPressure(rawPressure, &calibrationData);
  
  Serial.print("Compass: ");
  printVector(&compData);
  
  Serial.print("Gyroscope: ");
  printVector(&gyroData);
  
  Serial.print("Temperature: ");
  Serial.println(temp);
  
  Serial.print("Pressure: ");
  Serial.println(pressure);
  
  delay(1000);
}

void readAccelerometer(Vector3 *data) {
  // TODO
}
