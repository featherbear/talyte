#include <WiFi.h>

namespace WifiUtils {

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
String getMACPrefix();
void initWiFi(const char* ssid, const char* password);

}  // namespace WifiUtils