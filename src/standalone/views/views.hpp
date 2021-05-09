#ifndef VIEWS_H
#define VIEWS_H

enum View {
    TALLY,
    INFO,
    CONNECTING
};

struct ViewInterface {
    std::function<void()> handleDraw;
    std::function<void(bool longPress)> handleAltButtonPress;
    std::function<void()> resetState;
};

namespace ViewInterfaces {
extern ViewInterface Tally;
extern ViewInterface Info;
extern ViewInterface Connecting;
}  // namespace ViewInterfaces
#endif