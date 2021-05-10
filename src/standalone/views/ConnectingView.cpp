
#include "../device.hpp"
#include "viewUtils.hpp"
#include "views.hpp"

namespace ViewInterfaces {
ViewInterface Connecting = {
    .handleDraw = []() {
        Title("Connecting");
        return; },
    .handleAltButtonPress = [](bool longPress) {},
    .handleAltButtonStateChange = [](bool isPressed) {},
    .resetState = []() {}};
}  // namespace ViewInterfaces