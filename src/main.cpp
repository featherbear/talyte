#include <Arduino.h>

/* Headers? What that */
// #include "Client.cpp"

#include "TalyteClient.hpp"
#include "standalone/device.hpp"
#include "standalone/utils/wifi.hpp"
//////////////

const char* ssid = "";
const char* password = "";
const char* OBS_HOST = "";
const unsigned short OBS_PORT = 4444;

TalyteClient C;

void setup() {
    WifiUtils::initWiFi(ssid, password);

    Device::setup();

    // TODO: Info page - SSID, Server IP, Battery, charging
    // TODO: Shutdown procedure

    // event handler
    C.setup(OBS_HOST, OBS_PORT);
}

void loop() {
    C.loop();
}