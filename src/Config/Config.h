#ifndef __INC_ANTXCITY_CONFIG_H
#define __INC_ANTXCITY_CONFIG_H

#include "../setup.h"
#include "ConfigJoystickItem.h"
#include "ConfigItemBool.h"
#include "ConfigItemInt.h"
#include "LampConfigItem/LampConfigItem.h"

class Config {
private:
    ConfigJoystickItem *joystick_config_items[JOYSTICK_ITEM_COUNT] = {
        new ConfigItemPresets(this),        // Vorgaben
        new ConfigItemTimer(this),          // Automatik
        new ConfigItemBrightness(this),     // Helligkeit (DEFAULT)
        new ConfigItemHue(this),            // Farbton
        new ConfigItemSaturation(this),     // Sättigung
        new ConfigItemStrips(this),         // wich strip
        new ConfigItemLines(this),          // Leds per Strip
        new ConfigItemPosition(this),       // Verschiebung
        new ConfigItemColorRotation(this),  // Farbrotation
        new ConfigItemSpectrum(this),       // Farbverlauf
        new ConfigItemBrightnessRotation(this),  // Farbrotation
        new ConfigItemBrightnessGradient(this),     // Helligkeitsverlauf
        new ConfigItemInfo(this)            // Informationen
    };
    ConfigItem *m_changed = 0;

public:
    int getJoystickItemCount();
    ConfigJoystickItem *getJoystickConfigItem(int index);
    ConfigJoystickItem *getJoystickConfigItem(String name, bool xc_on_not_found = true);
    ConfigJoystickItem *getJoystickItems();

    int getConfigIntValue(String title);
    void setConfigIntValue(String title, int value);


    void setChanged(ConfigItem *configitem) { m_changed = configitem; };
    void setUnchanged() { m_changed = 0; };
    bool isChanged() { return m_changed ? true : false; };
    ConfigItem *getChangedItem() { return m_changed; };
};


#endif