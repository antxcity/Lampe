#include "Lamp.h"

Lamp::Lamp() 
{
    m_config = new Config;

    m_ledstrips[0] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_1>;
    m_ledstrips[1] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_2>;
    m_ledstrips[2] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_3>;

    m_oled = new Oled(OLED_INTERFACE, OLED_SCL_PIN, OLED_SDA_PIN, GEOMETRY_128_32);
    m_oled->showMessage("Welcome!");

    m_joystick = new Joystick(JOY_X_PIN, JOY_Y_PIN, JOY_S_PIN);
    m_joystick_handler = new LampJoystickHandler(this);
}

Lamp::~Lamp() {
    delete m_joystick_handler;
    delete m_joystick;
    
    delete m_oled;

    for (int i = 0; i < NUM_STRIPS; i++) {
        delete m_ledstrips[i];
        m_ledstrips[i] = NULL;
    }

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

    ConfigItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);

        ci_bool->setValue(false);
    }
    else if ( 
            ci->getValueType().equalsIgnoreCase("Int") 
         || ci->getValueType().equalsIgnoreCase("Volume")
    ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        if (ci_int->m_value > ci_int->m_min_value)
            ci_int->m_value--;
    }
    _show();
};

void Lamp::onJoystickRight() {
    if ( !m_displayActive ) {
        activateDisplay();
        return;
    }
    
    ConfigItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);
        ci_bool->setValue(true);
    }
    else if ( 
                ci->getValueType().equalsIgnoreCase("Int") 
            || ci->getValueType().equalsIgnoreCase("Volume")
        ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        if (ci_int->m_value < ci_int->m_max_value)
            ci_int->m_value++;
    }
    _show();
};

void Lamp::_show() {
    ConfigItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);
        m_oled->showBool(ci_bool->m_title, ci_bool->getValue());
    }
    else if ( ci->getValueType().equalsIgnoreCase("Int") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showBar(ci_int->m_title, ci_int->m_value, ci_int->m_min_value, ci_int->m_max_value);
    }
    else if ( ci->getValueType().equalsIgnoreCase("Volume") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showVolumeBar(ci_int->m_title, ci_int->m_value, ci_int->m_min_value, ci_int->m_max_value);
    }
    else {
        m_oled->showMessage("unknown item");
    }

    if (m_config->isChanged()) {
        if (ci = m_config->getJoystickConfigItem(HELLIGKEIT_CONFIG_ITEM_INDEX)) {
            ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
            int hell_index = map(ci_int->m_value, ci_int->m_min_value, ci_int->m_max_value, 0, m_ledstrips[0]->get_num_leds() - 1);
            m_ledstrips[0]->setSingleLed(hell_index, CRGB::Blue);
            m_ledstrips[0]->show();
        }
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
