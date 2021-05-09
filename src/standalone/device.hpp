#pragma once
#ifndef DEVICaE_H
#define DEVICaE_H

#include <M5StickC.h>

#include "DeviceState.hpp"

namespace Device {
static struct DeviceState State;

void setup(const char* ssid, const char* password);
}  // namespace Device

#endif