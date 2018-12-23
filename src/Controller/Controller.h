#ifndef __INC_ANTXCITY_CONTROLLER_H
#define __INC_ANTXCITY_CONTROLLER_H

#include "../Oled/Oled.h"
#include "../Config/Config.h"

class Controller {
private:
    Oled *m_oled;
    Config *m_config;

    int m_currentConfigItem = 0;
    bool m_displayActive = false;

    void activateDisplay();
    void deactivateDisplay();

    void updateDisplay();

protected:
    void _show();

public:
    Controller(Oled *oled, Config *config);

    void onJoystickLeft();
    void onJoystickRight();
    void onJoystickUp();
    void onJoystickDown();
    void onJoystickButton();
};

#endif