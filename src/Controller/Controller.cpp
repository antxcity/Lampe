#include "Controller.h"

#include "../Config/Config.h"
#include "../Oled/Oled.h"

Controller::Controller(Oled *oled, Config *config) 
: m_oled(oled), m_config(config)
{
    //configItems = config.getJoystickItems();
};
    
void Controller::onJoystickLeft() {
    if ( !m_displayActive ) {
        activateDisplay();
        return;
    }

    ConfigItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);

        ci_bool->m_value = false;
    }
    else if ( ci->getValueType().equalsIgnoreCase("Int") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        if (ci_int->m_value > ci_int->m_min_value)
            ci_int->m_value--;
    }
    _show();
};

void Controller::onJoystickRight() {
    if ( !m_displayActive ) {
        activateDisplay();
        return;
    }
    
    ConfigItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);
        ci_bool->m_value = true;
    }
    else if ( ci->getValueType().equalsIgnoreCase("Int") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        if (ci_int->m_value < ci_int->m_max_value)
            ci_int->m_value++;
    }
    _show();
};

void Controller::_show() {
    ConfigItem *ci = m_config->getJoystickConfigItem(m_currentConfigItem);
    if ( !ci ) 
        return;

    if ( ci->getValueType().equalsIgnoreCase("Bool") ) {
        ConfigItemBool *ci_bool = dynamic_cast<ConfigItemBool *>(ci);
        m_oled->showBool(ci_bool->m_title, ci_bool->m_value);
    }
    else if ( ci->getValueType().equalsIgnoreCase("Int") ) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        m_oled->showBar(ci_int->m_title, ci_int->m_value);
    }
    else {
        m_oled->showMessage("unknown item");
    }
};

void Controller::onJoystickUp() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

    if (m_currentConfigItem == 0)
        return;

    m_currentConfigItem--;

    _show();
};

void Controller::onJoystickDown() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

    if (m_currentConfigItem == m_config->getJoystickItemCount() - 1)
        return;

    m_currentConfigItem++;

    _show();
};

void Controller::onJoystickButton() {
    if (!m_displayActive) {
        activateDisplay();
        return;
    }

    m_oled->showMessage("button pressed");
    delay(100);
    activateDisplay();
};

void Controller::activateDisplay() {
    m_displayActive = true;
    m_oled->activate();

    _show();
}

void Controller::deactivateDisplay() {
    m_displayActive = false;
    m_oled->deactivate();
}
