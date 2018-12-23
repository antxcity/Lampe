#ifndef __INC_ANTXCITY_LAMP_H
#define __INC_ANTXCITY_LAMP_H

#include "../LedStrip/LedStrip.h"
#include "../Joystick/Joystick.h"
#include "Controller/Controller.h"
#include "../../setup.h"

class Lamp : public IJoystickHandler
{
    private:
        LedStripBase *m_ledstrips[NUM_STRIPS];
        Joystick m_joystick;

        Oled *m_oled;
        Config *m_config;
        Controller *m_controller;

        // COledDisplay m_display;
        // CWlan m_wlan;

    public:
        Lamp();
        ~Lamp();

        void loop();

        virtual void onLeftIn();
        virtual void onLeftOut();
        virtual void onRightIn();
        virtual void onRightOut();
        virtual void onDownIn();
        virtual void onDownOut();
        virtual void onUpIn();
        virtual void onUpOut();
        virtual void onSwitchDown();
        virtual void onSwitchUp();
        virtual void onChanged();
};

#endif