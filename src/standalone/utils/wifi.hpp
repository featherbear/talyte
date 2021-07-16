#include <WiFi.h>

namespace WifiUtils {

String getHostname();
String getSSID();
String getMACPrefix();
String getIPAddress();
void initWiFi();
void waitForConnect();
void waitForConnect(bool (*)());

String discoverNetworks();

bool isConnected();

void setWifiAuth(const char* ssid, const char* password);

void setWifiIPMode(bool isDHCP);
void setWifiIPMode(bool isDHCP, const char* ip, const char* mask);

}  // namespace WifiUtils