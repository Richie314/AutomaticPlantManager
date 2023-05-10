#include "DataStorageManager.h"
#include "NetworkManager.h"
#include "SensorManager.h"
#define SENSOR_PIN A1

Sensors::MoistureSensor(SENSOR_PIN);

void setup()
{
  Serial.println("Device started.");

}

void loop()
{
  delay(100);
}
