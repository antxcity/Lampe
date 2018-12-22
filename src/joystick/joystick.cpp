#include <Arduino.h>
#include "joystick.h"

void CSerialJoystickHandler::onLeftIn()     { Serial.println("Left in"); }
void CSerialJoystickHandler::onLeftOut()    { Serial.println("Left out"); }
void CSerialJoystickHandler::onRightIn()    { Serial.println("Right in"); }
void CSerialJoystickHandler::onRightOut()   { Serial.println("Right out"); }
void CSerialJoystickHandler::onDownIn()     { Serial.println("Down in"); }
void CSerialJoystickHandler::onDownOut()    { Serial.println("Down out"); }
void CSerialJoystickHandler::onUpIn()       { Serial.println("Up in"); }
void CSerialJoystickHandler::onUpOut()      { Serial.println("Up out"); }
void CSerialJoystickHandler::onSwitchDown() { Serial.println("Switch down"); }
void CSerialJoystickHandler::onSwitchUp()   { Serial.println("Switch up"); }
void CSerialJoystickHandler::onChanged()    { }


CJoystick::CJoystick(int x_pin, int y_pin, int switch_pin) 
    : m_x_pin(x_pin), 
      m_y_pin(y_pin), 
      m_switch_pin(switch_pin)
{
    pinMode(m_x_pin, INPUT);
    pinMode(m_y_pin, INPUT);
    pinMode(m_switch_pin, INPUT);    
    
    static CSerialJoystickHandler serial_joystick_handler = CSerialJoystickHandler();

    m_joystick_handler = &serial_joystick_handler; // initialize the defaul serial joystick handler

    m_x = (m_left_level_in + m_right_level_in) / 2;  // mid-position
    m_y = (m_down_level_in + m_up_level_in) / 2;     // mid-position    
}

void CJoystick::read() {
    if (handleXAxis() || handleYAxis() || handleSwitch())
        onChanged();
}

bool CJoystick::handleXAxis() {
    int x = analogRead(m_x_pin);

    bool changed = false;

    // do we enter the "right" area?
    if (x > m_right_level_in) {
        if (m_x <= m_right_level_out) {
            changed = true;
            onRightIn();
        }
    }

    // do we leave the "right" area?
    if (x <= m_right_level_out) {
        if (m_x > m_right_level_in) {
            changed = true;
            onRightOut();
        }
    }

    // do we enter the "left" area?
    if (x < m_left_level_in) {
        if (m_x >= m_left_level_out) {
            changed = true;
            onLeftIn();
        }
    }

    // do we leave the "right" area?
    if (x > m_left_level_out) {
        if (m_x <= m_left_level_in) {
            changed = true;
            onLeftOut();
        }
    }

    m_x = x;

    return changed;
}

bool CJoystick::handleYAxis() {
    int y = analogRead(m_y_pin);

    bool changed = false;

    // do we enter the "upper" area?
    if (y > m_up_level_in) {
        if (m_y <= m_up_level_out) {
            changed = true;
            onUpIn();
        }
    }

    // do we leave the "upper" area?
    if (y <= m_up_level_out) {
        if (m_y > m_up_level_in) {
            changed = true;
            onUpOut();
        }
    }

    // do we enter the "down" area?
    if (y < m_down_level_in) {
        if (m_y >= m_down_level_out) {
            changed = true;
            onDownIn();
        }
    }

    // do we leave the "down" area?
    if (y > m_down_level_out) {
        if (m_y <= m_down_level_in) {
            changed = true;
            onDownOut();
        }
    }

    m_y = y;

    return changed;
}

bool CJoystick::handleSwitch() {
    int s = analogRead(m_switch_pin);

    bool changed = false;

    if (s == 0) {
        if (m_s != 0) {
            changed = true;
            onSwitchDown();
        }
    }

    if (s != 0) {
        if (m_s == 0) {
            changed = true;
            onSwitchUp();
        }
    }

    m_s = s;

    return changed;
}

void CJoystick::print() {
    Serial.print("X: " + String(m_x) + " - Y: " + String(m_y) + " - S: " + String(m_s) + "\n");
}

void CJoystick::setJoyStickHandler(IJoystickHandler *joystick_handler) {
    m_joystick_handler = joystick_handler;
}

void CJoystick::onLeftIn() {
    if (m_joystick_handler)
        m_joystick_handler->onLeftIn();
}

void CJoystick::onLeftOut() {
    if (m_joystick_handler)
        m_joystick_handler->onLeftOut();
}

void CJoystick::onRightIn() {
    if (m_joystick_handler)
        m_joystick_handler->onRightIn();
}

void CJoystick::onRightOut() {
    if (m_joystick_handler)
        m_joystick_handler->onRightOut();
}

void CJoystick::onDownIn() {
    if (m_joystick_handler)
        m_joystick_handler->onDownIn();
}

void CJoystick::onDownOut() {
    if (m_joystick_handler)
        m_joystick_handler->onDownOut();
}

void CJoystick::onUpIn() {
    if (m_joystick_handler)
        m_joystick_handler->onUpIn();
}

void CJoystick::onUpOut() {
    if (m_joystick_handler)
        m_joystick_handler->onUpOut();
}

void CJoystick::onSwitchDown() {
    if (m_joystick_handler)
        m_joystick_handler->onSwitchDown();
}

void CJoystick::onSwitchUp() {
    if (m_joystick_handler)
        m_joystick_handler->onSwitchUp();
}

void CJoystick::onChanged() {
    if (m_joystick_handler)
        m_joystick_handler->onChanged();
}

