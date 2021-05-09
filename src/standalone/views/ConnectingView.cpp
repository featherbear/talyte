
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

namespace ViewInterfaces {
ViewInterface Connecting = {
    .handleDraw = []() {
        Title("Connecting");
        return; },
    .handleAltButtonPress = [](bool longPress) { Serial.println("Alt press on connecting"); },
    .resetState = []() { Serial.println("Reset state"); }};
}  // namespace ViewInterfaces