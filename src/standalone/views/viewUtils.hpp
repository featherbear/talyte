#ifndef VIEWUTILS_H
#define VIEWUTILS_H

// Size 4 - 6 characters max
// Size 3 - 8 characters max
// Size 2 - 13 characters max

#define Title(x)           \
    M5.Lcd.setTextSize(2); \
    M5.Lcd.println(x);     \
    M5.Lcd.setTextSize(1);

inline String Spill(String s) {
    if (s.length() <= 26) return s;
    return s.substring(0, 23) + "...";
}

inline String NA_ifEmpty(String s) {
    if (s.isEmpty()) return "N/A";
    return s;
}

#endif