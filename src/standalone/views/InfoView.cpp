
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

namespace ViewInterfaces {
ViewInterface Info = {
    .handleDraw = []() {
        auto &talyteState = Device::State.talyte;

        Title("Info");

        if (!talyteState) {
            Title("\nTalyte is not initialised");
            return;
        }

        resetFontSize();
        // Preview
        if (!talyteState->currentPreview.isEmpty()) {
            M5.Lcd.println((String("Preview: ") + talyteState->currentPreview));
        }

        WifiUtils::getHostname();
        WifiUtils::getSSID();

        // Program
        M5.Lcd.println((String("Program: ") + (talyteState->currentProgram.isEmpty() ? "N/A" : talyteState->currentProgram)));

        // IP
        M5.Lcd.println((String("IP Address: ") + Device::State.network.ipAddress())); },
    .handleAltButtonPress = [](bool longPress) { Serial.println(longPress ? "Alt long press on info" : "Alt press on info"); },
    .resetState = []() {}};
}  // namespace ViewInterfaces