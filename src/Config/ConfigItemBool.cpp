#include "ConfigItemBool.h"

#include "Config.h"

ConfigItemBool::ConfigItemBool(Config *config, String title, bool value)
: ConfigJoystickItem(config, title), m_value(value) {

}

void ConfigItemBool::setValue(bool value) { 
    if (m_value != value) {
        m_value = value; 
        getConfig()->setChanged();
    }
}

void ConfigItemBool::incrementValue() {
    setValue(true);
}

void ConfigItemBool::decrementValue() {
    setValue(false);
}