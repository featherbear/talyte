
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

static TalyteState *talyteState;

namespace ViewInterfaces {
ViewInterface Tally = {
    .handleDraw = []() {
        talyteState = Device::State.talyte;

        if (!talyteState) {
            Title("\n\nTalyte is not initialised");
            return;
        }
        bool programLinked = !(talyteState->linkedProgram.isEmpty());

        if (programLinked) {
            if (talyteState->linkedProgram == talyteState->currentProgram) {
                M5.Lcd.fillScreen(RED);
                return;
            } else if (talyteState->linkedProgram == talyteState->currentPreview) {
                M5.Lcd.fillScreen(GREEN);
                return;
            }
        }
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextDatum(CC_DATUM);
        M5.Lcd.drawString("IDLE", M5.Lcd.width() / 2, M5.Lcd.height() / 2, 1);

        return; },
    .handleAltButtonPress = [](bool longPress) {},
    .handleAltButtonStateChange = [](bool isPressed) {},
    .resetState = []() {}};
}  // namespace ViewInterfaces