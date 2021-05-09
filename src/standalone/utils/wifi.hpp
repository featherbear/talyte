#include <WiFi.h>

namespace WifiUtils {

String getMACPrefix();
String getIPAddress();
void initWiFi(const char* ssid, const char* password);
void waitForConnect();

}  // namespace WifiUtils