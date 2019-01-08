#include "ConfigItem.h"

ConfigItem::ConfigItem(Config *config, String title) 
: m_config(config),
  m_title(title) 
{
}

String ConfigItem::getValueType() {
    return "undefined";
}

Config *ConfigItem::getConfig() { 
    return m_config; 
};