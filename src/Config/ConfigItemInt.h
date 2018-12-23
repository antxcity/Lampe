#ifndef __INC_ANTXCITY_CONFIGITEMINT_H
#define __INC_ANTXCITY_CONFIGITEMINT_H

#include "ConfigItem.h"

class ConfigItemInt : public ConfigItem {
public:
    int m_value;
    int m_min_value = 0;
    int m_max_value = 255;

    ConfigItemInt(Config *config, String title, int value, int min_value = 0, int max_value = 255);
    virtual String getValueType() { return "Int"; };
};

class ConfigItemVolume : public ConfigItemInt {
public:
    ConfigItemVolume(Config *config, String title, int value, int min_value = 0, int max_value = 255);
    virtual String getValueType() { return "Volume"; };
};

#endif