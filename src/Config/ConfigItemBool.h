#ifndef __INC_ANTXCITY_CONFIGITEMBOOL_H
#define __INC_ANTXCITY_CONFIGITEMBOOL_H

#include "ConfigJoystickItem.h"

class ConfigItemBool : public ConfigJoystickItem {
protected:
    bool m_value;

public:
    ConfigItemBool(Config *config, String title, bool value);

    virtual String getValueType() { return "Bool"; };
    void setValue(bool value);
    virtual bool getValue() { return m_value; };

    virtual String getDisplayString() { return m_value ? "Ja" : "Nein"; };

    virtual void incrementValue();
    virtual void decrementValue();
};

#endif