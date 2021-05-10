
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

static TalyteState *talyteState;

namespace ViewInterfaces {
ViewInterface Tally = {
    .handleDraw = []() {
        talyteState = Device::State.talyte;

        Title("Tally");

        return; },
    .handleAltButtonPress = [](bool longPress) { Serial.println("Alt press on tally"); },
    .handleAltButtonStateChange = [](bool isPressed) {},
    .resetState = []() {}};
}  // namespace ViewInterfaces