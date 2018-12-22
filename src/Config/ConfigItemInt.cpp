#include "ConfigItemInt.h"

ConfigItemInt::ConfigItemInt(String title, int value)
: ConfigItem(title), m_value(value)
{
    // todo: sanitize value 0..255
}

String ConfigItemInt::getValueType() {
    return "Int";
}