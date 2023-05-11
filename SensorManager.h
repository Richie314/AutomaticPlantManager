#include <float16.h>
namespace Sensors
{
  class MoistureSensor
  {
    uint8_t m_AnalogPin;
    ushort m_WetLevel;
    bool Good()const;
  public:

    MoistureSensor();

    MoistureSensor(uint8_t AnalogPin);

    MoistureSensor(uint8_t AnalogPin, ushort WetLevel);

    operator bool () const;

    short RawRead() const;

    float16 MoistureLevel() const;

    bool IsWet() const;

    bool IsDry() const;

    bool IsWet(const float16& MoistureLevel) const;

    bool IsDry(const float16& MoistureLevel) const;

    bool Calibrate(ushort WetLevel);

    bool CalibrateFromCurrentValue(const float16* oldData, size_t dataLength);
  };
  inline float16& operator >> (const MoistureSensor& sensor, float16& fNumber)
  {
    fNumber = sensor.MoistureLevel();
    return fNumber;
  };
  class UltrasonicSensor
  {
    const uint8_t m_Trig, m_Echo;
    unsigned long RawRead() const;
  public:
    UltrasonicSensor() : UltrasonicSensor(0, 0) {};
    UltrasonicSensor(const uint8_t Trig, const uint8_t Echo);
    float16 Read_m() const
    {
      static long divisor = 5820L;
      return float16( (double)RawRead() / divisor);
    }
    float16 Read_cm() const
    {
      static float16 hundred(100.0);
      return Read_m() * hundred;
    }
    float16 Read_mm()const
    {
      static float16 thousand(1000.0);
      return Read_m() * thousand;
    }
    float16 operator () () const
    {
        return Read_cm();
    }
    bool Good()const
    {
      return m_Trig != 0 && m_Echo != 0 && m_Trig != m_Echo;
    }
    operator bool ()const
    {
      return Good();
    }
  };
  inline float16& operator >> (const UltrasonicSensor& sensor, float16& fNumber)
  {
    fNumber = sensor();
    return fNumber;
  }
}