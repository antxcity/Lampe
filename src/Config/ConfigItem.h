#ifndef __INC_ANTXCITY_CONFIGITEM_H
#define __INC_ANTXCITY_CONFIGITEM_H

#include <Arduino.h>

class ConfigItem {

public:
    String m_title;

    ConfigItem(String title);
    virtual String getValueType();
};

#endif