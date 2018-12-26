#ifndef __INC_ANTXCITY_LAMP_H
#define __INC_ANTXCITY_LAMP_H

#include "../LedLight/LedLight.h"
#include "../Joystick/Joystick.h"
#include "LampJoystickHandler.h"
#include "../../setup.h"
#include "../Oled/Oled.h"
#include "../Config/Config.h"

class LampJoystickHandler;

class Lamp
{
private:
    LedLight m_ledLight;
    Joystick *m_joystick;
    LampJoystickHandler *m_joystickHandler;

    int m_currentConfigItem = 0;
    bool m_displayActive = false;

    Oled *m_oled;
    Config *m_config;

protected:
    void _show();

public:
    Lamp();
    ~Lamp();

    Joystick *getJoystick();

    void loop();

    void activateDisplay();
    void deactivateDisplay();

    void updateDisplay();

    void onJoystickLeft();
    void onJoystickRight();
    void onJoystickUp();
    void onJoystickDown();
    void onJoystickButton();        
};

#endif