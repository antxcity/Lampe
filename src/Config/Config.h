#ifndef __INC_ANTXCITY_CONFIG_H
#define __INC_ANTXCITY_CONFIG_H

#include "../setup.h"
#include "ConfigJoystickItem.h"
#include "ConfigItemBool.h"
#include "ConfigItemInt.h"

class Config {
private:
    ConfigJoystickItem *joystick_config_items[JOYSTICK_ITEM_COUNT] = {
        new ConfigItemPresets(this),
        new ConfigItemValue(this),
        new ConfigItemSaturation(this),
        new ConfigItemHue(this),
        new ConfigItemStrips(this),
        new ConfigItemLines(this),
        new ConfigItemPosition(this),
        new ConfigItemColorRotation(this),
        new ConfigItemSpectrum(this),
        new ConfigItemEffects(this),
        new ConfigItemInfo(this),
    };
    bool m_changed = false;

public:
    int getJoystickItemCount();
    ConfigJoystickItem *getJoystickConfigItem(int index);
    ConfigJoystickItem *getJoystickItems();

    void setChanged() { m_changed = true; };
    void setUnchanged() { m_changed = false; };
    bool isChanged() { return m_changed; };
};


#endif