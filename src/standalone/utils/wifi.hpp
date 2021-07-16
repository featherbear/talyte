#include <WiFi.h>

namespace WifiUtils {

String getHostname();
String getSSID();
String getMACPrefix();
String getIPAddress();
void initWiFi(const char* ssid, const char* password);
void waitForConnect();
void waitForConnect(bool (*)());

String discoverNetworks();

bool isConnected();
}  // namespace WifiUtils