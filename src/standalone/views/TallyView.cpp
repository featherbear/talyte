
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

        if (talyteState->linkedProgram == talyteState->currentProgram) {
            M5.Lcd.fillScreen(RED);
        } else if (talyteState->linkedProgram == talyteState->currentPreview) {
            M5.Lcd.fillScreen(GREEN);
        }

        return; },
    .handleAltButtonPress = [](bool longPress) {},
    .handleAltButtonStateChange = [](bool isPressed) {},
    .resetState = []() {}};
}  // namespace ViewInterfaces