#include "wifi.hpp"

namespace WifiUtils {

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Disconnected from WiFi access point");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(info.disconnected.reason);
    Serial.println("Trying to Reconnect");
    // TODO: Check
    WiFi.reconnect();
}

String getMACPrefix() {
    String MAC = WiFi.macAddress();
    MAC.replace(":", "");
    return MAC.substring(0, 6);
}

String getHostname() {
    return WiFi.getHostname();
}

String getSSID() {
    return WiFi.SSID();
}

void initWiFi(
    const char* ssid, const char* password) {
    WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(("Talyte-" + getMACPrefix()).c_str());
    WiFi.begin(ssid, password);
}

void waitForConnect() {
    while (WiFi.status() != WL_CONNECTED) delay(1000);
}

String getIPAddress() {
    return WiFi.localIP().toString();
}

}  // namespace WifiUtils