#ifndef __INC_ANTXCITY_CONFIGITEMBOOL_H
#define __INC_ANTXCITY_CONFIGITEMBOOL_H

#include "ConfigItem.h"

class ConfigItemBool : public ConfigItem {
public:
    bool m_value;

    ConfigItemBool(String title, bool value);

    virtual String getValueType() { return "Bool"; };
};

#endif