#include "Config.h"
// #include "ConfigItem.h"

/*
Config::Config(String title) 
{
}
*/

ConfigJoystickItem *Config::getJoystickItems() {
    return joystick_config_items[0];
}

int Config::getJoystickItemCount() 
{
    return JOYSTICK_ITEM_COUNT;
}

ConfigJoystickItem *Config::getJoystickConfigItem(int index) 
{
    if ( index < 0 || index >= getJoystickItemCount() )
        return 0;
    return joystick_config_items[index];
}

ConfigJoystickItem *Config::getJoystickConfigItem(String name, bool xc_on_not_found) 
{
    for ( int i = 0; i < getJoystickItemCount(); i++ ) {
        if (joystick_config_items[i]->getTitle().equals(name))
            return joystick_config_items[i];
    }
    if (xc_on_not_found)
        throw String("Config item to get not found:") + name;
    return 0;
}

int Config::getConfigIntValue(String name) {
    ConfigItemInt *ci = dynamic_cast<ConfigItemInt *>(getJoystickConfigItem(name));
    return ci->getValue();
}

void Config::setConfigIntValue(String name, int value) {
    ConfigItemInt *ci = dynamic_cast<ConfigItemInt *>(getJoystickConfigItem(name));
    ci->setValue(value);
}
