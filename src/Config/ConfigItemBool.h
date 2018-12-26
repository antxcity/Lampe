#ifndef __INC_ANTXCITY_CONFIGITEMBOOL_H
#define __INC_ANTXCITY_CONFIGITEMBOOL_H

#include "ConfigJoystickItem.h"

class ConfigItemBool : public ConfigJoystickItem {
private:
    bool m_value;

public:
    ConfigItemBool(Config *config, String title, bool value);

    virtual String getValueType() { return "Bool"; };
    void setValue(bool value);
    bool getValue() { return m_value; };

    virtual void incrementValue();
    virtual void decrementValue();
};

#endif