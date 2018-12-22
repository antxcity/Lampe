#include "oled.h"
#include <SSD1306Wire.h>

oled::oled(int interface, int SCL_pin, int SDA_pin, OLEDDISPLAY_GEOMETRY resolution) :
    display(interface, SCL_pin, SDA_pin, resolution)
{
};

void oled::showBar(String title, int value) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, title + ": " + value);
    display.drawRect(0, 18, display.width() - 1, display.height() - 18);
    display.fillRect(2, 20, (display.width() / 2) - 3, display.height() - 22);
    display.display();
};

void oled::showBool(String title, int value) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, title + ": " + (value ? "An" : "Aus") );
    display.display();
}

void oled::showMessage(String message) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, message);
    display.display();
}

void oled::activate() {
    // not yet implemented
}

void oled::deactivate() {
    // not yet implemented
}
