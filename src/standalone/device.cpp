#include "device.hpp"

#include "utils/wifi.hpp"

namespace Device {

struct DeviceState State = {
    .currentView = View::CONNECTING};

bool altButtonEventActive = false;

// Functions to draw
ViewInterface currentViewInterface = ViewInterfaces::Connecting;

void setup(const char* ssid, const char* password) {
    setCpuFrequencyMhz(80);  // Save power - reduce CPU clock
    btStop();                // Save power - disable Bluetooth
    Serial.begin(9600);

    Serial.println("Talyte starting...");

    M5.Axp.begin();  // Enable battery module
    M5.Axp.ScreenBreath(11);
    Serial.println("> Battery module initialised");

    M5.Lcd.begin();
    M5.Lcd.setRotation(3);
    Serial.println("> LCD module initialised");

    State.network.requestedSSID = ssid;
    WifiUtils::initWiFi(ssid, password);
    Serial.println("> WiFi module initialised");

    refreshScreen(true);  // Show the (Connecting) screen

    WifiUtils::waitForConnect();
    Serial.println("> Connected to " + WifiUtils::getSSID() +
                   "\n  IP address: " + WifiUtils::getIPAddress() +
                   "\n  Hostname: " + WifiUtils::getHostname());

    refreshScreen(true);
}

void link_talyte_instance(TalyteClient* client) {
    State.talyteClient = client;
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

    currentViewInterface.resetState();

    // Reset alt button states
    // Otherwise you can hold Alt
    // and press M5 then release Alt
    altButtonEventActive = false;
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

void loop() {
    M5.BtnA.read();
    M5.BtnB.read();

    // M5 button pressed
    if (M5.BtnA.wasPressed()) {
        switchModes();

        // Start timer
    } else if (M5.BtnB.wasPressed()) {
        altButtonEventActive = true;
        buttonBPressStart = M5.BtnB.lastChange();
        currentViewInterface.handleAltButtonStateChange(true);

        // If side button held for >= 6000ms then trigger the long press event
    } else if (altButtonEventActive && M5.BtnB.pressedFor(6000)) {
        altButtonEventActive = false;

        currentViewInterface.handleAltButtonPress(true);

        // On short release (<= 1000ms), trigger short press event
        // On long release, ignore
    } else if (M5.BtnB.wasReleased()) {
        if (!altButtonEventActive) return;
        altButtonEventActive = false;

        currentViewInterface.handleAltButtonStateChange(false);

        uint32_t duration = M5.BtnB.lastChange() - buttonBPressStart;
        if (duration <= 1000) {
            currentViewInterface.handleAltButtonPress(false);
        }
    }
}
}  // namespace Device
