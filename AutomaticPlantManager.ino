#include "DataStorageManager.h"
#include "NetworkManager.h"
#include "SensorManager.h"

#define SOIL_SENSOR_PIN A0
#define ULTRASONIC_TRIG_PIN 10
#define ULTRASONIC_ECHO_PIN 11

Sensors::MoistureSensor moistureSensor(SOIL_SENSOR_PIN);
Sensors::UltrasonicSensor ultrasonicSensor(ULTRASONIC_TRIG_PIN, ULTRASONIC_ECHO_PIN);
String DeviceName = "Soil Web Monitor";

void setup()
{
  //Load Device Name from SD if present


  if (false)
  {
    Network::DeleteCredentials();
  }
  while (!Network::SetUp(DeviceName))
  {
    delay(2000);
  }
  Network::ServerBegin();
  
  Network::MapRoute("/", "GET", "text/html", HandleRoot);
  Network::MapStaticRoute("/script.js", "text/javascript", "");
  Network::MapStaticRoute("/style.css", "text/css", "");
}
String HandleRoot()
{
  return "<h1>Route</h1>";
}
void loop()
{
  
  delay(100);
}
