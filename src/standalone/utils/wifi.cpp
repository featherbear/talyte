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

void startConfigurator() {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(WiFi.getHostname());
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    while (true) {
        delay(1000);
    }
}

void waitForConnect() {
    waitForConnect(NULL);
}
void waitForConnect(bool (*interrupt)()) {
    while (!isConnected()) {
        if (interrupt && interrupt()) {
            startConfigurator();
        }
        delay(1000);
    }
}

String getIPAddress() {
    return WiFi.localIP().toString();
}

bool isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
}  // namespace WifiUtils