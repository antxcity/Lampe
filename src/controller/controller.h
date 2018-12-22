#include "oled.h"

class controller {
    private:
        configItem configItems[];
        int currentConfigItem = 0;
        bool displayActive = false;
        oled oled;

        void activateDisplay();
        void deactivateDisplay();

        void updateDisplay();

    public:
        controller(oled oled); // constructor

        void onJoystickLeft();
        void onJoystickRight();
        void onJoystickUp();
        void onJoystickDown();
        void onJoystickButton();
};
