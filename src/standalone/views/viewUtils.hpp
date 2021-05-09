// // 6 characters per line
// #define H1(x) M5.Lcd.setTextSize(4); M5.Lcd.println(x);

// // 8 characters max
// #define H2(x) M5.Lcd.setTextSize(3); M5.Lcd.println(x);

#define Title(x)           \
    M5.Lcd.setTextSize(2); \
    M5.Lcd.println(x);

#define resetFontSize() M5.Lcd.setTextSize(1);