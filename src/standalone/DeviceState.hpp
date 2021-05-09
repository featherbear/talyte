#ifndef DEVICESTATE_H
#define DEVICESTATE_H

#include "enums.hpp"
#include "utils/wifi.hpp"

struct DeviceState {
    enum View currentView;
    struct {
        String ipAddress() {
            return WifiUtils::getIPAddress();
        }
    } network;
};

#endif