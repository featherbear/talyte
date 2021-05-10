
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
static bool linkButtonPressed = false;

void drawOBS() {
    if (!talyteState) {
        Title("Talyte is not initialised");
        return;
    }

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
    if (talyteState) {
        M5.Lcd.println(Spill(String("OBS: ") + talyteState->network.host + ":" + String(talyteState->network.port)));
    } else {
        M5.Lcd.println("OBS: Not connected");
    }
    M5.Lcd.println("");

    // Battery
    uint8_t batteryLevel = Device::State.getBatteryLevel();
    M5.Lcd.println(String("Battery: ") + min(batteryLevel, (uint8_t)100) + "%" + ((batteryLevel >= 100) ? " (charging)" : ""));
}

void drawAssign() {
    if (!talyteState) {
        Title("Talyte is not initialised");
        return;
    }

    M5.Lcd.println("Assigned program:\n" + Spill("> " + NA_ifEmpty(talyteState->linkedProgram)));

    // Linked <> Program
    if (!(talyteState->linkedProgram.equalsConstantTime(talyteState->currentProgram))) {
        M5.Lcd.println("Current program:");
        M5.Lcd.println(Spill("> " + NA_ifEmpty(talyteState->currentProgram)));
        M5.Lcd.println("\nHold button (6s) to link..");

        M5.Lcd.print("           ");  // Aligned with the LCD and button
        if (linkButtonPressed) M5.Lcd.setTextColor(BLACK, WHITE);
        M5.Lcd.println("vvvv Link");
        if (linkButtonPressed) M5.Lcd.setTextColor(WHITE, BLACK);
    }
}

namespace ViewInterfaces {
ViewInterface Info = {
    .handleDraw = []() {
            Device::resetScreen();

            talyteState = Device::State.talyte;
            char titleBuff[26];
            snprintf(titleBuff, sizeof(titleBuff), "Info      %hhu/%hhu", (uint8_t) currentPage + 1, N_PAGES);
            Title(titleBuff);

            M5.Lcd.println("");
            
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

            // Long press
        } else if (currentPage == Pages::Assign) {
            Device::State.talyteClient->setLinkedProgram(talyteState->currentProgram);
        }

        Device::refreshScreen(); },
    .handleAltButtonStateChange = [](bool isPressed) {
        // Only handle button press for the assign page GUI
        if (currentPage != Pages::Assign) return;
        linkButtonPressed = isPressed;
        Device::refreshScreen(); },
    .resetState = []() { currentPage = Pages::OBS; linkButtonPressed = false; }};
}  // namespace ViewInterfaces