#include "device.hpp"

#include "utils/wifi.hpp"

namespace Device {

void setup(const char* ssid, const char* password) {
    setCpuFrequencyMhz(80);  // Save power - reduce CPU clock
    btStop();                // Save power - disable Bluetooth

    WifiUtils::initWiFi(ssid, password);
    WifiUtils::waitForConnect();

    Serial.begin(9600);
    Serial.println(State.network.ipAddress());

    M5.Lcd.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(
        "yeah");
}

void setView(enum View view) {
    State.currentView = view;
}

// void updateScreen() {
//     State.currentView;
// }
}  // namespace Device
