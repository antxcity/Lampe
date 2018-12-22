#include "ConfigItemBool.h"

ConfigItemBool::ConfigItemBool(String title, bool value)
: ConfigItem(title), m_value(value) {

}

String ConfigItemBool::getValueType() {
    return "Bool";
}