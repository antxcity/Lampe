#include "ConfigItemInt.h"

ConfigItemInt::ConfigItemInt(String title, int value, int min_value, int max_value)
    : ConfigItem(title), 
      m_value(value), 
      m_min_value(min_value), 
      m_max_value(max_value)
{
    // todo: sanitize value 0..255
}

ConfigItemVolume::ConfigItemVolume(String title, int value, int min_value, int max_value) 
    : ConfigItemInt(title, value, min_value, max_value)
{

}
