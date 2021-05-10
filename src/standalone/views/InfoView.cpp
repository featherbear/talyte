
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

#define N_PAGES 3
enum Pages {
    OBS,
    Network,
    Assign
};

static enum Pages currentPage = Pages::OBS;
static TalyteState *talyteState;

void drawOBS() {
    // Program
    Title("Program");
    M5.Lcd.println(Spill(talyteState->currentProgram.isEmpty() ? "N/A" : talyteState->currentProgram));
    // M5.Lcd.println((String("Program: ") + (talyteState->currentProgram.isEmpty() ? "N/A" : talyteState->currentProgram)));

    // Preview
    if (!talyteState->currentPreview.isEmpty()) {
        M5.Lcd.println("");
        Title("Preview");
        M5.Lcd.println(Spill(talyteState->currentPreview));
        // M5.Lcd.println((String("Preview: ") + talyteState->currentPreview));
    }
}

void drawNetwork() {
    // Device WiFi
    M5.Lcd.println(Spill(String("WiFi SSID: ") + Device::State.network.SSID()));
    M5.Lcd.println(Spill(String("Hostname : ") + Device::State.network.hostname()));
    M5.Lcd.println(Spill(String("Device IP: ") + Device::State.network.ipAddress()));
    M5.Lcd.println("");

    // OBS
    M5.Lcd.println(Spill(String("OBS: ") + talyteState->network.hostname + ":" + String(talyteState->network.port)));
    M5.Lcd.println("");

    // Battery
    uint8_t batteryLevel = Device::State.getBatteryLevel();
    M5.Lcd.println(String("Battery: ") + min(batteryLevel, (uint8_t)100) + "%" + ((batteryLevel >= 100) ? " (charging)" : ""));
}

void drawAssign() {
}

namespace ViewInterfaces {
ViewInterface Info = {
    .handleDraw = []() {
            talyteState = Device::State.talyte;
            char titleBuff[26];
            snprintf(titleBuff, sizeof(titleBuff), "Info      %hhu/%hhu", (uint8_t) currentPage + 1, N_PAGES);
            Title(titleBuff);

            M5.Lcd.println("");
            
            if (!talyteState) {
                Title("Talyte is not initialised");
                return;
            }

            switch (currentPage) {
                case OBS:
                    drawOBS(); 
                    break;
                case Network:
                    drawNetwork();
                    break;
                case Assign:
                    drawAssign(); 
                    break;
            } },
    .handleAltButtonPress = [](bool longPress) { 
        if (!longPress) {
           switch (currentPage) {
                case OBS:
                    currentPage = Pages::Network; 
                    break;
                case Network:
                    currentPage = Pages::Assign;
                    break;
                case Assign:
                    currentPage = Pages::OBS;
                    break;
           }

           Device::refreshScreen();
        }
        
        Serial.println(longPress ? "Alt long press on info" : "Alt press on info"); },
    .resetState = []() {}};
}  // namespace ViewInterfaces