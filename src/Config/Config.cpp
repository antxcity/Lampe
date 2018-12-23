#include "Config.h"
// #include "ConfigItem.h"

/*
Config::Config(String title) 
{
}
*/

ConfigItem *Config::getJoystickItems() {
    return joystick_config_items[0];
}

int Config::getJoystickItemCount() 
{
    return JOYSTICK_ITEM_COUNT;
}

ConfigItem *Config::getJoystickConfigItem(int index) 
{
    if ( index < 0 || index >= getJoystickItemCount() )
        return 0;
    return joystick_config_items[index];
}
