#include <Arduino.h>
#include "Joystick.h"

void SerialJoystickHandler::onLeftIn()     { Serial.println("Left in"); }
void SerialJoystickHandler::onLeft()       { Serial.println("Left"); }
void SerialJoystickHandler::onLeftOut()    { Serial.println("Left out"); }
void SerialJoystickHandler::onRightIn()    { Serial.println("Right in"); }
void SerialJoystickHandler::onRight()      { Serial.println("Right"); }
void SerialJoystickHandler::onRightOut()   { Serial.println("Right out"); }
void SerialJoystickHandler::onDownIn()     { Serial.println("Down in"); }
void SerialJoystickHandler::onDown()       { Serial.println("Down"); }
void SerialJoystickHandler::onDownOut()    { Serial.println("Down out"); }
void SerialJoystickHandler::onUpIn()       { Serial.println("Up in"); }
void SerialJoystickHandler::onUp()         { Serial.println("Up"); }
void SerialJoystickHandler::onUpOut()      { Serial.println("Up out"); }
void SerialJoystickHandler::onSwitchDown() { Serial.println("Switch down"); }
void SerialJoystickHandler::onSwitchUp()   { Serial.println("Switch up"); }
void SerialJoystickHandler::onChanged()    { }


Joystick::Joystick(int x_pin, int y_pin, int switch_pin) 
    : m_x_pin(x_pin), 
      m_y_pin(y_pin), 
      m_switch_pin(switch_pin)
{
    pinMode(m_x_pin, INPUT);
    pinMode(m_y_pin, INPUT);
    pinMode(m_switch_pin, INPUT);    
    
    static SerialJoystickHandler serial_joystick_handler = SerialJoystickHandler();

    m_joystick_handler = &serial_joystick_handler; // initialize the defaul serial joystick handler

    m_x = (m_left_level_in + m_right_level_in) / 2;  // mid-position
    m_y = (m_down_level_in + m_up_level_in) / 2;     // mid-position    
}

void Joystick::read() {
    if (handleXAxis() || handleYAxis() || handleSwitch())
        onChanged();
}

bool Joystick::handleXAxis() {
    int x = analogRead(m_x_pin);

    bool changed = false;

    // do we enter the "right" area?
    if (x > m_right_level_in) {
        if (m_x <= m_right_level_out) {
            changed = true;
            onRightIn();
        }
        onRight();
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
        onLeft();
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

bool Joystick::handleYAxis() {
    int y = analogRead(m_y_pin);

    bool changed = false;

    // do we enter the "upper" area?
    if (y > m_up_level_in) {
        if (m_y <= m_up_level_out) {
            changed = true;
            onDownIn();
        }
        onDown();
    }

    // do we leave the "upper" area?
    if (y <= m_up_level_out) {
        if (m_y > m_up_level_in) {
            changed = true;
            onDownOut();
        }
    }

    // do we enter the "down" area?
    if (y < m_down_level_in) {
        if (m_y >= m_down_level_out) {
            changed = true;
            onUpIn();
        }
        onUp();
    }

    // do we leave the "down" area?
    if (y > m_down_level_out) {
        if (m_y <= m_down_level_in) {
            changed = true;
            onUpOut();
        }
    }

    m_y = y;

    return changed;
}

bool Joystick::handleSwitch() {
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

void Joystick::print() {
    Serial.print("X: " + String(m_x) + " - Y: " + String(m_y) + " - S: " + String(m_s) + "\n");
}

void Joystick::setJoyStickHandler(IJoystickHandler *joystick_handler) {
    m_joystick_handler = joystick_handler;
}

void Joystick::onLeftIn() {
    if (m_joystick_handler)
        m_joystick_handler->onLeftIn();
}

void Joystick::onLeft() {
    if (m_joystick_handler)
        m_joystick_handler->onLeft();
}

void Joystick::onLeftOut() {
    if (m_joystick_handler)
        m_joystick_handler->onLeftOut();
}

void Joystick::onRightIn() {
    if (m_joystick_handler)
        m_joystick_handler->onRightIn();
}

void Joystick::onRight() {
    if (m_joystick_handler)
        m_joystick_handler->onRight();
}

void Joystick::onRightOut() {
    if (m_joystick_handler)
        m_joystick_handler->onRightOut();
}

void Joystick::onDownIn() {
    if (m_joystick_handler)
        m_joystick_handler->onDownIn();
}

void Joystick::onDown() {
    if (m_joystick_handler)
        m_joystick_handler->onDown();
}

void Joystick::onDownOut() {
    if (m_joystick_handler)
        m_joystick_handler->onDownOut();
}

void Joystick::onUpIn() {
    if (m_joystick_handler)
        m_joystick_handler->onUpIn();
}

void Joystick::onUp() {
    if (m_joystick_handler)
        m_joystick_handler->onUp();
}

void Joystick::onUpOut() {
    if (m_joystick_handler)
        m_joystick_handler->onUpOut();
}

void Joystick::onSwitchDown() {
    if (m_joystick_handler)
        m_joystick_handler->onSwitchDown();
}

void Joystick::onSwitchUp() {
    if (m_joystick_handler)
        m_joystick_handler->onSwitchUp();
}

void Joystick::onChanged() {
    if (m_joystick_handler)
        m_joystick_handler->onChanged();
}

