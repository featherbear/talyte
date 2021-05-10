#ifndef VIEWS_H
#define VIEWS_H

enum View {
    TALLY,
    INFO,
    CONNECTING
};

struct ViewInterface {
    // Draw function
    std::function<void()> handleDraw;

    // When the Alt button is released
    // Tip: Use this for handling the alt button press
    std::function<void(bool longPress)> handleAltButtonPress;

    // When the Alt button is pressed
    // Tip: Only use this for GUI updates, not actions
    std::function<void(bool isPressed)> handleAltButtonStateChange;

    // Reset state
    std::function<void()> resetState;
};

namespace ViewInterfaces {
extern ViewInterface Tally;
extern ViewInterface Info;
extern ViewInterface Connecting;
}  // namespace ViewInterfaces
#endif