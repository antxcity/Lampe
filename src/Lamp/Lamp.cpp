#include "Lamp.h"

Lamp::Lamp() 
{
    m_config = new Config;

    m_oled = new Oled(OLED_INTERFACE, OLED_SCL_PIN, OLED_SDA_PIN, GEOMETRY_128_32);
    m_oled->showMessage("Welcome!");

    m_joystick = new Joystick(JOY_X_PIN, JOY_Y_PIN, JOY_S_PIN);
    m_joystickHandler = new LampJoystickHandler(this);
    m_ledLight.applyLowLight(m_config);
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
    m_ledLight.applyConfig(m_config);
    if (m_ledLight.getTimeOut() > 0)
        m_oled->showTimerBar(m_ledLight.getCurrentTimeLeft(), m_ledLight.getTimeOut());

    m_oled->showUpDownIndicator(m_currentConfigItem > 0, m_currentConfigItem < JOYSTICK_ITEM_COUNT-1);
    //Serial.println(String("Timeout: ") + String(m_ledLight.getTimeOut()) + "Time left: " + m_ledLight.getCurrentTimeLeft());
}

void Lamp::onJoystickLeft() {
    if ( !m_displayActive ) {
        activateDisplay();
        return;
    }

    m_config->getJoystickConfigItem(m_currentConfigItem)->decrementValue();

    _show();
};

void Lamp::onJoystickRight() {
    if ( !m_displayActive ) {
        activateDisplay();
        return;
    }

    m_config->getJoystickConfigItem(m_currentConfigItem)->incrementValue();

    _show();
};

void Lamp::_show() {
    ConfigJoystickItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);
        m_oled->showBool(ci_bool->getTitle(), ci_bool->getValue());
    }
    else if ( ci->getValueType().equalsIgnoreCase("String") ) {
        m_oled->showString(ci->getTitle(), ci->getDisplayString());
    }
    else if ( ci->getValueType().equalsIgnoreCase("Int") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showBar(ci_int->getTitle(), ci_int->getValue(), ci_int->getMinValue(), ci_int->getMaxValue());
    }
    else if ( ci->getValueType().equalsIgnoreCase("Volume") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showVolumeBar(ci_int->getTitle(), ci_int->getValue(), ci_int->getMinValue(), ci_int->getMaxValue());
    }
    else {
        m_oled->showMessage("unknown item");
    }

    m_ledLight.applyConfig(m_config);
    if (m_config->isChanged()) {
        m_config->setUnchanged();
    }
};

void Lamp::onJoystickUp() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

    if (m_currentConfigItem == 0)
        return;

    m_currentConfigItem--;
    m_ledLight.resetTimer();

    _show();
};

void Lamp::onJoystickDown() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

    if (m_currentConfigItem == m_config->getJoystickItemCount() - 1)
        return;

    m_currentConfigItem++;
    m_ledLight.resetTimer();    

    _show();
};

void Lamp::onJoystickButton() {
    m_ledLight.resetTimer();
    m_config->setChanged(m_config->getJoystickConfigItem(m_currentConfigItem));
    _show();
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

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
