#ifndef __INC_ANTXCITY_LAMPJOYSTICKHANDLER_H
#define __INC_ANTXCITY_LAMPJOYSTICKHANDLER_H

#include "../Joystick/Joystick.h"
#include "Lamp.h"
#include "../../setup.h"

class Lamp;

class LampJoystickHandler : public JoystickHandlerBase {
private:
    Lamp *m_lamp;
    int m_delay = JOYSTICK_DELAY;
    int m_rate = JOYSTICK_RATE;
    
    int m_first_hit_time = 0;
    int m_last_hit_time = 0;

    void initDelay();
    bool isDelayDone();
    void stopDelay();

public:
    LampJoystickHandler(Lamp *lamp);

    virtual void onLeftIn();
    virtual void onLeft();
    virtual void onLeftOut();

    virtual void onRightIn();
    virtual void onRight();    
    virtual void onRightOut();    

    virtual void onDownIn();
    //virtual void onDown();

    virtual void onUpIn();
    virtual void onSwitchDown();
    //virtual void onUp();
  //  virtual void onChanged();
/*
    virtual void onLeftOut();
    virtual void onRightOut();
    virtual void onDownIn();
    virtual void onDownOut();
    virtual void onUpIn();
    virtual void onUpOut();
    virtual void onSwitchDown();
    virtual void onSwitchUp();
 */
};

#endif