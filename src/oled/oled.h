// #include <Wire.h>
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
