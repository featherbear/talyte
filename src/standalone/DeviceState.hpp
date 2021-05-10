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
        String SSID() {
            return WifiUtils::getSSID();
        }
        String hostname() {
            return WifiUtils::getHostname();
        }
        String requestedSSID;
    } network;
    uint8_t getBatteryLevel() {
        // https://community.m5stack.com/post/5841
        // Deprecated: M5.Axp.GetVbatData() * 1.1 / 1000
        // Use: GetBatVoltage()
        return floor(100.0 * ((M5.Axp.GetBatVoltage() - 3.0) / (4.07 - 3.0)));
    };
    TalyteClient *talyteClient;
    struct TalyteState *talyte;
};

#endif