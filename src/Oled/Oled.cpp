#include "Oled.h"

Oled::Oled(int interface, int SCL_pin, int SDA_pin, OLEDDISPLAY_GEOMETRY resolution) :
    display(interface, SCL_pin, SDA_pin, resolution)
{
    display.init();
    display.flipScreenVertically();
}

void Oled::showBar(String title, int value, int min_value, int max_value) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, title + ": " + value);
    int width = map(value, min_value, max_value, 0, display.width() - 5);
    display.drawRect(0, 18, display.width() - 1, display.height() - 18);
    display.fillRect(2, 20, width, display.height() - 22);
    display.display();
}

void Oled::showVolumeBar(String title, int value, int min_value, int max_value) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, title + ": " + value);
    int width = map(value, min_value, max_value, 0, display.width() - 5);
    int height = map(value, min_value, max_value, 0, display.height() - 22);
    display.drawRect(0, 18, display.width() - 1, display.height() - 18);
    display.fillRect(2, display.height()-height-2, width, height);
    display.display();
}

void Oled::showBool(String title, bool value) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, title + ": " + (value ? "An" : "Aus") );
    display.display();
}

void Oled::showMessage(String message) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, message);
    display.display();
}

void Oled::showString(String title, String value) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, title + ":");
    display.drawString(0, 16, value);
    display.display();
}

void Oled::activate() {
    // not yet implemented
}

void Oled::deactivate() {
    // not yet implemented
}
