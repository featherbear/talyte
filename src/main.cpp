#include <Arduino.h>
#include <Preferences.h>

#include "TalyteClient.hpp"
#include "standalone/device.hpp"

std::unique_ptr<TalyteClient> Talyte = NULL;

static Preferences preferences;
void setup() {
    preferences.begin("talyte-config", true);
    String tally_host = preferences.getString("tally_host");
    unsigned short tally_port = preferences.getUShort("tally_port", 4444);
    String tally_program = preferences.getString("tally_program");
    preferences.end();

    Talyte = std::unique_ptr<TalyteClient>(new TalyteClient(tally_host, tally_port));

    Device::link_talyte_instance(Talyte.get());
    Device::setup();

    Talyte->set_change_event_handler(ChangeEventType::ALL, [](String _) {
        Device::refreshScreen();
    });
    Talyte->setLinkedProgram(tally_program);

    Talyte->connect();
    while (!Talyte->isConnected()) {
        Talyte->loop();
        if (Device::wasBtnAPressed()) Configurator::startConfigurator();
    }

    Device::refreshScreen();
    delay(3000);

    Device::setView(View::INFO);
}

void loop() {
    Device::loop();
    Talyte->loop();
}