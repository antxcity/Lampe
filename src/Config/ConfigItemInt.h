#ifndef __INC_ANTXCITY_CONFIGITEMINT_H
#define __INC_ANTXCITY_CONFIGITEMINT_H

#include "ConfigJoystickItem.h"

class ConfigItemInt : public ConfigJoystickItem {
protected:
    int m_value;
    int m_min_value = 0;
    int m_max_value = 255;
    int m_steps = 1;

public:
    ConfigItemInt(Config *config, String title, int value, int min_value = 0, int max_value = 255, int steps = 1);
    
    virtual String getValueType() { return "Int"; };
    virtual void setValue(int value);
    virtual int getValue() { return m_value; };

    virtual String getDisplayString() { return String(m_value); };

    void setMinValue(int min_value);
    int getMinValue() { return m_min_value; };

    void setMaxValue(int max_value);
    int getMaxValue() { return m_max_value; };

    void setStepValue(int steps);
    int getStepValue() { return m_steps; };

    virtual void incrementValue();
    virtual void decrementValue();

};

class ConfigItemVolume : public ConfigItemInt {
public:
    ConfigItemVolume(Config *config, String title, int value, int min_value = 0, int max_value = 255);
    virtual String getValueType() { return "Volume"; };
};

#endif