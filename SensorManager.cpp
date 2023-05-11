#include <Arduino.h>
#include "SensorManager.h"
using namespace Sensors;
bool MoistureSensor::Good()const
{
  return m_WetLevel != 0;
}

MoistureSensor::MoistureSensor() : m_AnalogPin(0), m_WetLevel(0)
{ };

MoistureSensor::MoistureSensor(uint8_t AnalogPin) : m_AnalogPin(AnalogPin), m_WetLevel(0)
{ };

MoistureSensor::MoistureSensor(uint8_t AnalogPin, ushort WetLevel) : m_AnalogPin(AnalogPin), m_WetLevel(WetLevel)
{ };

MoistureSensor::operator bool () const
{
  return Good();
}

short MoistureSensor::RawRead() const
{
  return analogRead(m_AnalogPin);
}

float16 MoistureSensor::MoistureLevel() const
{
  if (!Good())
  {
    return float16();
  }
  return float16( (double) (RawRead() / m_WetLevel) );
}

bool MoistureSensor::IsWet() const
{
  return IsWet(MoistureLevel());
}

bool MoistureSensor::IsDry() const
{
  return IsDry(MoistureLevel());
}

bool MoistureSensor::IsWet(const float16& MoistureLevel) const
{
  static float16 One(1.0);
  return One <= MoistureLevel;
}

bool MoistureSensor::IsDry(const float16& MoistureLevel) const
{
  static float16 One(1.0);
  return One > MoistureLevel;
}

bool MoistureSensor::Calibrate(ushort WetLevel)
{
  if (WetLevel != 0)
  {
    m_WetLevel = WetLevel;
    return true;
  }
  return false;
}

bool MoistureSensor::CalibrateFromCurrentValue(const float16* oldData, size_t dataLength)
{
  if (!oldData || dataLength == 0 || !Good())
  {
    return false;
  }
  float16 max = oldData[0];
  for (size_t i = 1; i < dataLength; ++i)
  {
    if (max < oldData[i])
    {
      max = oldData[i];
    }
  }
  if (max <= float16())
  {
    return false;
  }
  m_WetLevel = (ushort)(max * float16((double)m_WetLevel)).toDouble();
  return true;
}

unsigned long UltrasonicSensor::RawRead() const
{
    digitalWrite(m_Trig, LOW);
    delayMicroseconds(2U);
    digitalWrite(m_Trig, HIGH);
    delayMicroseconds(10U);
    digitalWrite(m_Trig, LOW);
    return pulseIn(m_Echo, HIGH);
}
UltrasonicSensor::UltrasonicSensor(const uint8_t Trig, const uint8_t Echo) : m_Trig(Trig), m_Echo(Echo) 
{
  if (Good())
  {
    pinMode(m_Trig, OUTPUT);
    pinMode(m_Echo, INPUT); 
  } 
};

