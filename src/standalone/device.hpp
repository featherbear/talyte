#pragma once
#ifndef DEVICaE_H
#define DEVICaE_H

#include <M5StickC.h>

#include "../TalyteClient.hpp"
#include "DeviceState.hpp"

namespace Device {

extern struct DeviceState State;

void setup(const char* ssid, const char* password);
void link_talyte_instance(TalyteClient* client);

void setView(enum View view);
void refreshScreen(bool force = false);
void resetScreen();

void loop();
}  // namespace Device

#endif