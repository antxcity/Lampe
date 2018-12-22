#include "ConfigItem.h"

ConfigItem::ConfigItem(String title) 
: m_title(title) {
}

String ConfigItem::getValueType() {
    return "undefined";
}