#include "ConfigItemBool.h"

#include "Config.h"

ConfigItemBool::ConfigItemBool(Config *config, String title, bool value)
: ConfigItem(config, title), m_value(value) {

}

void ConfigItemBool::setValue(bool value) { 
    if (m_value != value) {
        m_value = value; 
        getConfig()->setChanged();
    }
}
