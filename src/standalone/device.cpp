#include "device.hpp"

#include "utils/wifi.hpp"

namespace Device {

struct DeviceState State = {
    .currentView = View::CONNECTING};

// Functions to draw
ViewInterface currentViewInterface = ViewInterfaces::Connecting;

void setup(const char* ssid, const char* password) {
    setCpuFrequencyMhz(80);  // Save power - reduce CPU clock
    btStop();                // Save power - disable Bluetooth
    Serial.begin(9600);

    M5.Lcd.begin();
    M5.Lcd.setRotation(3);
    refreshScreen(true);

    WifiUtils::initWiFi(ssid, password);
    WifiUtils::waitForConnect();

    Serial.println(State.network.ipAddress());
}

void link_talyte_instance(TalyteClient* client) {
    State.talyte = &(client->State);
}

void setView(enum View view) {
    switch ((State.currentView = view)) {
        case TALLY:
            currentViewInterface = ViewInterfaces::Tally;
            break;
        case INFO:
            currentViewInterface = ViewInterfaces::Info;
            break;
        case CONNECTING:
            currentViewInterface = ViewInterfaces::Connecting;
            break;
    }

    resetScreen();
    // currentViewInterface.resetState();
    refreshScreen(true);
}

void resetScreen() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(0, 0);
}

void refreshScreen(bool force) {
    // TODO: check for force
    currentViewInterface.handleDraw();
}

void switchModes() {
    switch (State.currentView) {
        case TALLY:
            setView(View::INFO);
            return;
        case INFO:
            setView(View::TALLY);
            return;
        default:
            return;
    }
}

void loop() {
    M5.BtnA.read();
    M5.BtnB.read();

    if (M5.BtnA.wasPressed()) {
        switchModes();
    } else if (M5.BtnB.wasPressed()) {
        currentViewInterface.handleAltButtonPress(false);
    }
}
}  // namespace Device
