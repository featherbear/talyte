#include <Arduino.h>

#include "TalyteClient.hpp"
#include "standalone/device.hpp"
//////////////

const char* ssid = "";
const char* password = "";
const char* OBS_HOST = "";
const unsigned short OBS_PORT = 4444;

TalyteClient Talyte;

void setup() {
    Device::setup(ssid, password);
    Device::link_talyte_instance(&Talyte);

    // TODO: Info page - SSID, Server IP, Battery, charging
    // TODO: Shutdown procedure

    // event handler
    Talyte.set_change_event_handler(ChangeEventType::ALL, [](String _) {
        Device::refreshScreen();
    });

    Talyte.connect(OBS_HOST, OBS_PORT);

    // TODO: Connecting screen
    Serial.println("Go to info");
    Device::setView(View::INFO);
}

void loop() {
    Device::loop();
    Talyte.loop();
}