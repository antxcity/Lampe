#include "ConfigItemInt.h"

ConfigItemInt::ConfigItemInt(Config *config, String title, int value, int min_value, int max_value)
    : ConfigItem(config, title), 
      m_value(value), 
      m_min_value(min_value), 
      m_max_value(max_value)
{
    // todo: sanitize value 0..255
}

ConfigItemVolume::ConfigItemVolume(Config *config, String title, int value, int min_value, int max_value) 
    : ConfigItemInt(config, title, value, min_value, max_value)
{

}
