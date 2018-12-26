#include "Lamp.h"

Lamp::Lamp() 
{
    m_config = new Config;

    m_oled = new Oled(OLED_INTERFACE, OLED_SCL_PIN, OLED_SDA_PIN, GEOMETRY_128_32);
    m_oled->showMessage("Welcome!");

    m_joystick = new Joystick(JOY_X_PIN, JOY_Y_PIN, JOY_S_PIN);
    m_joystickHandler = new LampJoystickHandler(this);
}

Lamp::~Lamp() {
    delete m_joystickHandler;
    delete m_joystick;
    
    delete m_oled;

    delete m_config;
}

Joystick *Lamp::getJoystick() 
{
    return m_joystick;
}

void Lamp::loop() {
    m_joystick->read();
}

void Lamp::onJoystickLeft() {
    if ( !m_displayActive ) {
        activateDisplay();
        return;
    }

    Serial.println("left");

    m_config->getJoystickConfigItem(m_currentConfigItem)->decrementValue();

    _show();
};

void Lamp::onJoystickRight() {
    if ( !m_displayActive ) {
        activateDisplay();
        return;
    }

    Serial.println("right");
    
    m_config->getJoystickConfigItem(m_currentConfigItem)->incrementValue();

    _show();
};

void Lamp::_show() {
    ConfigJoystickItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);
        m_oled->showBool(ci_bool->m_title, ci_bool->getValue());
    }
    else if ( ci->getValueType().equalsIgnoreCase("Int") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        Serial.println("adfasfd");
        m_oled->showBar(ci_int->m_title, ci_int->getValue(), ci_int->getMinValue(), ci_int->getMaxValue());
    }
    else if ( ci->getValueType().equalsIgnoreCase("Volume") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showVolumeBar(ci_int->m_title, ci_int->getValue(), ci_int->getMinValue(), ci_int->getMaxValue());
    }
    else {
        m_oled->showMessage("unknown item");
    }

    if (m_config->isChanged()) {
        m_ledLight.applyConfig(m_config);
        m_config->setUnchanged();
    }
};

void Lamp::onJoystickUp() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

    Serial.println("up");


    if (m_currentConfigItem == 0)
        return;

    m_currentConfigItem--;

    _show();
};

void Lamp::onJoystickDown() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }
    Serial.println("down");

    if (m_currentConfigItem == m_config->getJoystickItemCount() - 1)
        return;

    m_currentConfigItem++;

    _show();
};

void Lamp::onJoystickButton() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

    m_oled->showMessage("button pressed");
    delay(100);
    activateDisplay();
};

void Lamp::activateDisplay() {
    m_displayActive = true;
    m_oled->activate();

    _show();
}

void Lamp::deactivateDisplay() {
    m_displayActive = false;
    m_oled->deactivate();
}
