#include "Lamp.h"

Lamp::Lamp() 
{
    m_config = new Config;

    m_oled = new Oled(OLED_INTERFACE, OLED_SCL_PIN, OLED_SDA_PIN, GEOMETRY_128_32);
    m_oled->showMessage("Hallo Monika!");

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
    if (m_ledLight.idleSince() >= 20)  
        deactivateDisplay();

    //Serial.println(String("Timeout: ") + String(m_ledLight.getTimeOut()) + "Time left: " + m_ledLight.getCurrentTimeLeft());
}

void Lamp::onJoystickLeft() {
    activateDisplay();

    m_config->getJoystickConfigItem(m_currentConfigItem)->decrementValue();

    _show();
};

void Lamp::onJoystickRight() {
    activateDisplay();

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
    else if ( ci->getTitle().equalsIgnoreCase(CONFIG_ITEM_NAME_POSITION)) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showSlider(ci_int->getTitle(), ci_int->getValue(), ci_int->getMinValue(), ci_int->getMaxValue(), m_config->getConfigIntValue(CONFIG_ITEM_NAME_LINES));
    }
    else if ( ci->getValueType().equalsIgnoreCase("IntSlider")) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showSlider(ci_int->getTitle(), ci_int->getValue(), ci_int->getMinValue(), ci_int->getMaxValue(), 2);
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
};

void Lamp::onJoystickUp() {
    activateDisplay();
    
    if (m_currentConfigItem == 0)
        return;

    m_currentConfigItem--;
    m_ledLight.resetTimer();
    m_config->setChanged(m_config->getJoystickConfigItem(m_currentConfigItem));

    _show();
};

void Lamp::onJoystickDown() {
    activateDisplay();

    if (m_currentConfigItem >= m_config->getJoystickItemCount() - 1)
        return;

    m_currentConfigItem++;
    m_ledLight.resetTimer();    
    m_config->setChanged(m_config->getJoystickConfigItem(m_currentConfigItem));

    _show();
};

void Lamp::onJoystickButton() {
    m_ledLight.resetTimer();
    m_config->setChanged(m_config->getJoystickConfigItem(m_currentConfigItem));
    _show();
    activateDisplay();
};

void Lamp::activateDisplay() {
    if (!m_oled->isActive())
        m_oled->activate();
}

void Lamp::deactivateDisplay() {
    if (m_oled->isActive())
        m_oled->deactivate();
}
