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

/*
    switch (ci->getValueType()) {
        case "Bool":
            ConfigItemBool *ci_bool = <dynamic_cast ConfigItemBool *>(ci);

            ci_bool->m_value = !ci_bool->m_value);
            m_oled.showBool(ci_bool->m_title, ci_bool->value);
            break;
        case "Int":
            ConfigItemInt *ci_int = <dynamic_cast ConfigItemInt *>(ci);
            if (ci_int->m_value > ci_int->m_min_value)
                ci_int->m_value--;
            m_oled.showBar(ci.m_title, ci_int->m_value);
            break;
        default:
            break;
    }
    */
};
/*
void Controller::onJoystickRight() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        ci.value = !ci.value);
        oled.showBool(ci.title, ci.value);
        // no write back to config yet
    }
    else if (ci.type = config::configItemTypes.INT) {
        if (ci.value < ci.maxValue) {
            ci.value++;
            oled.showBar(ci.title, ci.value);
            // no write back to config yet
        }
    }
};

void Controller::onJoystickUp() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    if (currentConfigItem == 0)
        return;

    currentConfigItem--;
    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        oled.showBool(ci.title, ci.value);
    }
    else if (ci.type = config::configItemTypes.INT) {
        oled.showBar(ci.title, ci.value);
    }
};

void Controller::onJoystickDown() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    if (currentConfigItem == configItems.count - 1)
        return;

    currentConfigItem++;
    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        oled.showBool(ci.title, ci.value);
    }
    else if (ci.type = config::configItemTypes.INT) {
        oled.showBar(ci.title, ci.value);
    }
    else {
        oled.showMessage("unknown item");
    }
};

void Controller::onJoystickButton() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    oled.showError("button pressed");
    delay(2000);
    activateDisplay();
};

void Controller::activateDisplay() {
    displayActive = true;
    oled.activate();

    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        oled.showBool(ci.title, ci.value);
    }
    else if (ci.type = config::configItemTypes.INT) {
        oled.showBar(ci.title, ci.value);
    }
}

void Controller::deactivateDisplay() {
    displayActive = false;
    oled.deactivate();
}
*/