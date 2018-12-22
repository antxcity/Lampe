#include "Config.h"
// #include "ConfigItem.h"

/*
Config::Config(String title) 
{
}
*/

ConfigItem *Config::getJoystickItems() {
    return joystick_config_items;
}

int Config::getJoystickItemCount() 
{
    return sizeof(joystick_config_items);
}

ConfigItem *Config::getJoystickConfigItem(int index) 
{
    if ( index < 0 || index > getJoystickItemCount()-1 )
        return 0;
    return &joystick_config_items[index];
}
