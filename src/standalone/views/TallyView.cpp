
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

namespace ViewInterfaces {
ViewInterface Tally = {
    .handleDraw = []() {
        Title("Tally");
        return; },
    .handleAltButtonPress = [](bool longPress) { Serial.println("Alt press on tally"); },
    .resetState = []() { Serial.println("Reset state"); }};
}  // namespace ViewInterfaces