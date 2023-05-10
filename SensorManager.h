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
}