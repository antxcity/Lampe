#ifndef __INC_ANTXCITY_CONFIG_H
#define __INC_ANTXCITY_CONFIG_H

#include "../setup.h"
#include "ConfigItem.h"
#include "ConfigItemBool.h"
#include "ConfigItemInt.h"

class Config {
private:
    ConfigItem *joystick_config_items[JOYSTICK_ITEM_COUNT] = {
        new ConfigItemInt(this, "Helligkeit", 128),
        new ConfigItemBool(this, "Ja/Nein", true),
        new ConfigItemInt(this, "Farbton", 128),
        new ConfigItemVolume(this, "Lautstärke", 2, 0, 10)
    };
    bool m_changed = false;

public:
    int getJoystickItemCount();
    ConfigItem *getJoystickConfigItem(int index);
    ConfigItem *getJoystickItems();

    void setChanged() { m_changed = true; };
    void setUnchanged() { m_changed = false; };
    bool isChanged() { return m_changed; };
};

#endif