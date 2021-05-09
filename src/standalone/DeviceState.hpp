#ifndef DEVICESTATE_H
#define DEVICESTATE_H

#include "../TalyteState.hpp"
#include "utils/wifi.hpp"
#include "views/views.hpp"

struct DeviceState {
    enum View currentView;
    struct {
        String ipAddress() {
            return WifiUtils::getIPAddress();
        }
    } network;
    struct TalyteState *talyte;
};

#endif