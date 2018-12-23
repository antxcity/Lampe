#ifndef __INC_ANTXCITY_CONFIGITEMBOOL_H
#define __INC_ANTXCITY_CONFIGITEMBOOL_H

#include "ConfigItem.h"

class ConfigItemBool : public ConfigItem {
private:
    bool m_value;

public:

    ConfigItemBool(Config *config, String title, bool value);

    virtual String getValueType() { return "Bool"; };
    void setValue(bool value);
    bool getValue() { return m_value; };
};

#endif