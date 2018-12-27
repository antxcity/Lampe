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
    Oled *m_oled;
    Config *m_config;
    Joystick *m_joystick;
    LampJoystickHandler *m_joystickHandler;
    LedLight m_ledLight;

    int m_currentConfigItem = 2;
    bool m_displayActive = true;

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

    unsigned long millis() { return (unsigned long) (esp_timer_get_time() / 1000); };
};

#endif