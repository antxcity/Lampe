#include <SSD1306Wire.h>

class oled {
    private:
        SSD1306Wire display;

    public:
        oled(int interface, int SCL_pin, int SDA_pin, OLEDDISPLAY_GEOMETRY resolution);

        void showBar(String title, int value);
        void showBool(String title, int value);
        void showMessage(String message);

        void activate();
        void deactivate();
};
