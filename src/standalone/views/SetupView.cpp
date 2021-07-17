
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

static TalyteState *talyteState;
static TalyteClient *talyteClient;

namespace ViewInterfaces {
ViewInterface Setup = {
    .handleDraw = []() {
        Device::resetScreen();
        
        talyteState = Device::State.talyte;
        talyteClient = Device::State.talyteClient;

        Title("Setup");
        M5.Lcd.println("");

        // M5.Lcd.setTextColor(GREEN);
        M5.Lcd.println("SSID: " + Device::State.network.hostname());
        M5.Lcd.println("IP  : " + WiFi.softAPIP().toString());
        M5.Lcd.println("");
        M5.Lcd.println(
            "Join the above network and"
            "navigate to the IP address"
            "to set up this device"
        );

        return; },
    .handleAltButtonPress = [](bool longPress) {},
    .handleAltButtonStateChange = [](bool isPressed) {},
    .resetState = []() {}};
}  // namespace ViewInterfaces