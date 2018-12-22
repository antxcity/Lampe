#ifndef __INC_ANTXCITY_CONFIGITEMINT_H
#define __INC_ANTXCITY_CONFIGITEMINT_H

#include "ConfigItem.h"

class ConfigItemInt : public ConfigItem {
public:
    int m_value;
    int m_min_value = 0;
    int m_max_value = 255;

    ConfigItemInt(String title, int value);
    virtual String getValueType();
};

#endif