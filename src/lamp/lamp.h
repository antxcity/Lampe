#ifndef INC_CLAMP_H
#define INC_CLAMP_H

#include "../ledstrip/ledstrip.h"
#include "../joystick/joystick.h"
#include "../../setup.h"

class CLamp : public IJoystickHandler
{
    private:
        CLedStripBase *m_ledstrips[NUM_STRIPS];
        CJoystick m_joystick;
        // COledDisplay m_display;
        // CWlan m_wlan;

    public:
        CLamp();
        ~CLamp();

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