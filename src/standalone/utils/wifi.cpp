#include "wifi.hpp"

namespace WifiUtils {

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Disconnected from WiFi access point");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(info.disconnected.reason);
    Serial.println("Trying to Reconnect");
    // TODO: Check
    // WiFi.begin?
    // WiFi.reconnect()
}

String getMACPrefix() {
    String MAC = WiFi.macAddress();
    MAC.replace(":", "");
    return MAC.substring(0, 6);
}

void initWiFi(
    const char* ssid, const char* password) {
    WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(("Talyte-" + getMACPrefix()).c_str());
    WiFi.begin(ssid, password);
    Serial.begin(9600);
    Serial.print(WiFi.getAutoReconnect());
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

}  // namespace WifiUtils