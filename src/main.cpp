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

    // TODO: Info page - SSID, Server IP, Battery, charging
    // TODO: Shutdown procedure

    // event handler
    Talyte.set_change_event_handler(ChangeEventType::ALL, [](std::string a) {
       Serial.println("Yeah something happened");
        return;
    });
    Talyte.connect(OBS_HOST, OBS_PORT);
}

void loop() {
    Talyte.loop();
}