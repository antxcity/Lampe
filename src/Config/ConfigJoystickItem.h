#ifndef __INC_ANTXCITY_CONFIG_JOYSTICKITEM_H
#define __INC_ANTXCITY_CONFIG_JOYSTICKITEM_H

#include "ConfigItem.h"

class ConfigJoystickItem : public ConfigItem {
public:
    ConfigJoystickItem(Config *config, String title) 
        : ConfigItem(config, title) {};

    virtual void incrementValue() {};
    virtual void decrementValue() {};
};


#endif