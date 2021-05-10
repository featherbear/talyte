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

    M5.Axp.begin(); // Enable battery module

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
    resetScreen();
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

uint32_t buttonBPressStart = 0;
bool buttonBLongPressHandled = false;

void loop() {
    M5.BtnA.read();
    M5.BtnB.read();

    // M5 button pressed
    if (M5.BtnA.wasPressed()) {
        switchModes();

        // Start timer
    } else if (M5.BtnB.wasPressed()) {
        buttonBPressStart = M5.BtnB.lastChange();

        // If side button held for >= 6000ms then trigger the long press event
    } else if (M5.BtnB.pressedFor(6000) && !buttonBLongPressHandled) {
        buttonBLongPressHandled = true;
        currentViewInterface.handleAltButtonPress(true);

        // On short release (<= 1000ms), trigger short press event
        // On long release, ignore
    } else if (M5.BtnB.wasReleased()) {
        bool wasButtonBLongPressHandled = buttonBLongPressHandled;
        buttonBLongPressHandled = false;
        if (wasButtonBLongPressHandled) return;

        uint32_t duration = M5.BtnB.lastChange() - buttonBPressStart;
        if (duration <= 1000) {
            currentViewInterface.handleAltButtonPress(false);
        }
    }
}
}  // namespace Device
