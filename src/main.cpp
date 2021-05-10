#include <Arduino.h>

#include "TalyteClient.hpp"
#include "standalone/device.hpp"
//////////////

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* OBS_HOST = "OBS_OR_TALYTE_ASSISTANT_IP";
const unsigned short OBS_PORT = 4444;

TalyteClient Talyte(OBS_HOST, OBS_PORT);

void setup() {
    // TODO: Shutdown procedure

    Device::link_talyte_instance(&Talyte);
    Device::setup(ssid, password);

    Talyte.set_change_event_handler(ChangeEventType::ALL, [](String _) {
        Device::refreshScreen();
    });

    Talyte.connect();
    Talyte.waitForConnect();

    Device::refreshScreen();
    delay(3000);

    Device::setView(View::INFO);
}

void loop() {
    Device::loop();
    Talyte.loop();
}