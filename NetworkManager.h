#include <Arduino.h>
namespace Network
{
  bool SetUp(const String& DeviceName);

  bool Stop();

  void DeleteCredentials();

  void ServerBegin();

  bool MapRoute(const String& path, const String& method, const String& mime, std::function<String()> f);

  bool MapStaticRoute(const String& path, const String& mime, const String& file);
}