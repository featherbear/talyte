#include "wifi.hpp"

#include <ArduinoJson.h>

namespace WifiUtils {

String lastScanResult = "[]";
uint32_t lastScanFinishedTime = 0;
bool isScanning = false;

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

String discovery() {
    // If already scanning, ignore
    if (isScanning) return lastScanResult;

    // If last scan was performed less than 5 seconds ago, ignore
    if (millis() - lastScanFinishedTime < 5000) return lastScanResult;

    isScanning = true;

    int n_networks = WiFi.scanNetworks();
    Serial.printf("Found %d networks\n", n_networks);

    // Calculate size
    uint32_t docSize = 0;
    for (int i = 0; i < n_networks; i++) {
        docSize += 64 + 4;  // 64 - structure, 4 - 4-byte length
        docSize += WiFi.SSID(i).length();
        docSize += WiFi.BSSIDstr(i).length();
    }

    DynamicJsonDocument doc(docSize);
    for (int i = 0; i < n_networks; i++) {
        JsonArray apArray = doc.createNestedArray();
        apArray.add(WiFi.SSID(i));
        apArray.add(WiFi.BSSIDstr(i));
        apArray.add(WiFi.RSSI(i));
    }

    lastScanResult.clear();
    serializeJson(doc, lastScanResult);
    isScanning = false;
    lastScanFinishedTime = millis();
    return lastScanResult;
}

void startConfigurator() {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(WiFi.getHostname());
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    Serial.println(discovery());
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