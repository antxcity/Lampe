#ifndef __INC_ANTXCITY_CONFIG_H
#define __INC_ANTXCITY_CONFIG_H

#include "../setup.h"
#include "ConfigItem.h"
#include "ConfigItemBool.h"
#include "ConfigItemInt.h"

class Config {
private:
    ConfigItem joystick_config_items[JOYSTICK_ITEM_COUNT] = {
        ConfigItemInt("Helligikeit", 128),
        ConfigItemBool("Ja/Nein", true),
        ConfigItemInt("Farbton", 128)
    };

public:
    int getJoystickItemCount();
    ConfigItem *getJoystickConfigItem(int index);
    ConfigItem *getJoystickItems();
};

#endif