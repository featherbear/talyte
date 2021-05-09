#include "device.hpp"

namespace Device {
void setup() {
    
    // Save power - reduce CPU clock
    setCpuFrequencyMhz(80);

    // Save power - disable Bluetooth
    btStop();

    M5.Lcd.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(
        "yeah");
}
}  // namespace Device
