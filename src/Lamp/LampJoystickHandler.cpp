#include "LampJoystickHandler.h"

LampJoystickHandler::LampJoystickHandler(Lamp *lamp) 
: m_lamp(lamp) 
{
    m_lamp->getJoystick()->setJoyStickHandler(this);

}

void LampJoystickHandler::initDelay() {
    m_first_hit_time = millis();
    m_last_hit_time = millis();    
}

void LampJoystickHandler::stopDelay() {
    m_first_hit_time = 0;
    m_last_hit_time = 0;
}

bool LampJoystickHandler::isDelayDone() {
    if (millis() - m_first_hit_time < m_delay)
        return false;

    if (millis() - m_last_hit_time  < m_rate)
        return false;

    m_last_hit_time = millis();

    return true;
}

void LampJoystickHandler::onLeftIn() { 
    initDelay();
    m_lamp->onJoystickLeft(); 
}

void LampJoystickHandler::onLeftOut() { 
    stopDelay();
}

void LampJoystickHandler::onLeft() { 
    if (!isDelayDone())
        return;

    m_lamp->onJoystickLeft(); 
}

void LampJoystickHandler::onRightIn() { 
    initDelay();
    m_lamp->onJoystickRight(); 
}

void LampJoystickHandler::onRight() { 
    if (!isDelayDone())
        return;

    m_lamp->onJoystickRight(); 
}

void LampJoystickHandler::onRightOut() { 
    stopDelay();
}

void LampJoystickHandler::onDownIn() { 
    m_lamp->onJoystickDown(); 
}

void LampJoystickHandler::onUpIn() { 
    m_lamp->onJoystickUp(); 
}

/*
void LampJoystickHandler::onChanged() { 
    m_ledstrips[0]->show(); m_ledstrips[1]->show(); 
}
*/
