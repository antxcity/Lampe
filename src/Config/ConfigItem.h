#ifndef __INC_ANTXCITY_CONFIGITEM_H
#define __INC_ANTXCITY_CONFIGITEM_H

#include <Arduino.h>
// #include "Config.h"

class Config;

class ConfigItem {
private:
    Config *m_config;
    String m_title;

public:

    ConfigItem(Config *config, String title);
    String getTitle() { return m_title; };
    virtual String getValueType();
    virtual String getDisplayString() { return ""; };
    
    Config *getConfig();
};

#endif