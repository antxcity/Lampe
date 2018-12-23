#ifndef __INC_ANTXCITY_OLED_H
#define __INC_ANTXCITY_OLED_H

#include <SSD1306Wire.h>

class Oled {
    private:
        SSD1306Wire display;

    public:
        Oled(int interface, int SCL_pin, int SDA_pin, OLEDDISPLAY_GEOMETRY resolution);

        void showBar(String title, int value, int min_value, int max_value);
        void showVolumeBar(String title, int value, int min_value, int max_value);
        void showBool(String title, bool value);
        void showMessage(String message);

        void activate();
        void deactivate();
};

#endif