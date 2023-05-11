#include "NetworkManager.h"
#include <WiFiManager.h>
#define WEBSERVER_H
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
WiFiManager wifiManager;
bool WiFiOperational = false;

void wifiConfigModeCallback (WiFiManager *pWiFiManager)
{
  if (!pWiFiManager)
    return;
  //WiFi.softAPIP()
  //pWiFiManager->getConfigPortalSSID()
}
bool Network::SetUp(const String& DeviceName)
{
  //Cleaner output
  wifiManager.setDebugOutput(false);
  wifiManager.setDarkMode(true);
  //Inform user that
  wifiManager.setAPCallback(wifiConfigModeCallback);
  //Network handling
  wifiManager.setMinimumSignalQuality(20);
  wifiManager.setRemoveDuplicateAPs(false);
  
  String NetworkName = DeviceName + String(" - Network Soft AP");
  return WiFiOperational = wifiManager.autoConnect(NetworkName.c_str());
}

bool Network::Stop()
{
  return wifiManager.disconnect();
}

void Network::DeleteCredentials()
{
  wifiManager.resetSettings();
}


void Network::ServerBegin()
{
  if (WiFiOperational)
    server.begin();
}
bool Network::MapRoute(const String& path, const String& method, const String& mime, std::function<String()> f)
{
  if (!f || mime.isEmpty() || path.isEmpty() || method.isEmpty())
    return false;
  HTTPMethod Method = HTTP_GET;
  if (method.equalsIgnoreCase("POST"))
  {
    Method = HTTP_POST;
  } else if (method.equalsIgnoreCase("PUT"))
  {
    Method = HTTP_PUT;
  } else if (method.equalsIgnoreCase("HEAD"))
  {
    Method = HTTP_HEAD;
  }
  server.on(path.c_str(), Method, [&](AsyncWebServerRequest *request){
    request->send(200, mime, f());
  });
  return true;
}
bool Network::MapStaticRoute(const String& path, const String& mime, const String& file)
{
  if (file.isEmpty() || mime.isEmpty() || path.isEmpty())
    return false;
  server.on(path.c_str(), HTTP_GET, [&](AsyncWebServerRequest *request){
    static String fileContent = file;
    request->send(200, mime, fileContent);
  });
  return true;
}