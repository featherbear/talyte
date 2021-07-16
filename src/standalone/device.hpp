#pragma once
#ifndef DEVICaE_H
#define DEVICaE_H

#include <M5StickC.h>

#include "../TalyteClient.hpp"
#include "DeviceState.hpp"
#include "utils/configurator.hpp"

#define NVR_KEY_WIFI "talyte-wifi"
#define NVR_KEY_TALLY "talyte-config"

namespace Device {

extern struct DeviceState State;

void setup();
void link_talyte_instance(TalyteClient* client);

void setView(enum View view);
void refreshScreen();
void resetScreen();

bool wasBtnAPressed();

void loop();
}  // namespace Device

#endif