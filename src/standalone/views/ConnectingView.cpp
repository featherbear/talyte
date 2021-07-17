
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

static TalyteState *talyteState;
static TalyteClient *talyteClient;

namespace ViewInterfaces {
ViewInterface Connecting = {
    .handleDraw = []() {
        Device::resetScreen();
        
        talyteState = Device::State.talyte;
        talyteClient = Device::State.talyteClient;

        bool isWiFiConnected = WifiUtils::isConnected();
        bool isTalyteConnected = talyteClient && talyteClient->isConnected();

        Title((isWiFiConnected && isTalyteConnected) ? "Connected": "Connecting...");
        M5.Lcd.println("");

        if (isWiFiConnected) {
            M5.Lcd.setTextColor(GREEN);
            M5.Lcd.println("Connected to network");
            M5.Lcd.println(Spill(String("> ") + Device::State.network.SSID()));
            M5.Lcd.setTextColor(WHITE);
        } else {
            M5.Lcd.println("Connecting to network...");
            M5.Lcd.println(Spill(String("> ") + Device::State.network.requestedSSID));
        }
        M5.Lcd.println("");
        
        if (talyteClient) {
            if (isTalyteConnected) {
                M5.Lcd.setTextColor(GREEN);
                M5.Lcd.println("Connected to OBS");
                M5.Lcd.println(Spill(String("> ") + talyteState->network.host + ":" + String(talyteState->network.port)));
                M5.Lcd.setTextColor(WHITE);
            } else {
                M5.Lcd.println("Connecting to OBS...");
                M5.Lcd.println(Spill(String("> ") + (talyteState->network.host.isEmpty() ? "0.0.0.0" : talyteState->network.host) + ":" + String(talyteState->network.port)));
            }
        }
        

        return; },
    .handleAltButtonPress = [](bool longPress) {},
    .handleAltButtonStateChange = [](bool isPressed) {},
    .resetState = []() {}};
}  // namespace ViewInterfaces