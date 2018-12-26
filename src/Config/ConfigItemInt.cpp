#include "ConfigItemInt.h"

#include "Config.h"

ConfigItemInt::ConfigItemInt(
    Config *config, 
    String title, 
    int value, 
    int min_value, 
    int max_value, 
    int steps
)
    : ConfigJoystickItem(config, title), 
      m_value(value), 
      m_min_value(min_value), 
      m_max_value(max_value),
      m_steps(steps)
{
    // todo: sanitize value 0..255
}

ConfigItemVolume::ConfigItemVolume(Config *config, String title, int value, int min_value, int max_value) 
    : ConfigItemInt(config, title, value, min_value, max_value)
{

}

void ConfigItemInt::setValue(int value) {
    // Serial.println("ConfigItemInt::setValue(int " + getTitle() + " : " + String(value) + ")");

    if (m_value != value) {
        m_value = value; 
        getConfig()->setChanged(this);
    }    
}

void ConfigItemInt::incrementValue() {
    setValue(m_value + m_steps > m_max_value ? m_max_value : m_value + m_steps);
}

void ConfigItemInt::decrementValue() {
    setValue(m_value - m_steps < m_min_value ? m_min_value : m_value - m_steps);
}