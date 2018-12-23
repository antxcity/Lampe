#ifndef __INC_ANTXCITY_CONFIGITEM_H
#define __INC_ANTXCITY_CONFIGITEM_H

#include <Arduino.h>
// #include "Config.h"

class Config;

class ConfigItem {
private:
    Config *m_config;

public:
    String m_title;

    ConfigItem(Config *config, String title);
    virtual String getValueType();
    Config *getConfig();
};

#endif