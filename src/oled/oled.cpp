#include "oled.h"
#include <SSD1306Wire.h>

class Oled {
    private:
        int _interface = 0x3c;
        int _SCL_pin;
        int _SDA_pin;
        int _resoluton;
        SSD1306Wire display;

    public:
        Oled(int interface, int SCL_pin, int SDA_pin, OLEDDISPLAY_GEOMETRY resolution);

        void Show(String title, int value);
};

Oled::Oled(int interface, int SCL_pin, int SDA_pin, OLEDDISPLAY_GEOMETRY resolution) {
    _interface = interface;
    _SCL_pin = SCL_pin;
    _SDA_pin = SDA_pin;
    _resoluton = resolution;

    display = SSD1306Wire(0x3c, 21, 22, GEOMETRY_128_32);
};

void Oled::Show(String title, int value) {
    //display.
};
