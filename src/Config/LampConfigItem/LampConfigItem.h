#ifndef __INC_ANTXCITY_LAMPCONFIGITEM_H
#define __INC_ANTXCITY_LAMPCONFIGITEM_H

#include "../ConfigItemInt.h"
#include "../../../setup.h"

class ConfigItemPresets : public ConfigItemInt
{
public:
    ConfigItemPresets(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_PRESETS, 0, 0, 3) {};

    virtual void setValue(int value);
    virtual String getValueType() { return "String"; };

    virtual String getDisplayString();
};

class ConfigItemTimer : public ConfigItemInt
{
private:    
    static const int __string_count = 7;
    const String m_infoStrings[__string_count] = {
        "Aus (Dauerlicht)",
        "10 Sekunden",
        "1 Minute",
        "5 Minuten",
        "15 Minuten",
        "30 Minuten",
        "60 Minuten"
    };
    int m_timeouts[__string_count] = { -1, 10, 1*60, 5*60, 15*60, 30*60, 60*60 };

public:
    ConfigItemTimer(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_TIMER, 0, 0, __string_count - 1) {};

    virtual String getValueType() { return "String"; };
    virtual String getDisplayString() { return m_infoStrings[ getValue() % __string_count ]; };
    
    int getTimeoutValue() { return m_timeouts[getValue()]; };
};

class ConfigItemBrightness : public ConfigItemInt
{
public:
    ConfigItemBrightness(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_BRIGHTNESS, 10, 0, 255) {};

};

class ConfigItemHue : public ConfigItemInt
{
public:
    ConfigItemHue(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_HUE, 10, 0, 255) {};

};

class ConfigItemSaturation : public ConfigItemInt
{
public:
    ConfigItemSaturation(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_SATURATION, 10, 0, 255) {};

};

class ConfigItemStrips : public ConfigItemInt
{
public:
    ConfigItemStrips(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_STRIPS, 0, 0, 2) {};

    virtual String getValueType() { return "String"; };
    virtual String getDisplayString();

    int mapToStripMask();
    bool isStripActive(int strip_index);
};

class ConfigItemLines : public ConfigItemInt
{
public:
    ConfigItemLines(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_LINES, 0, 0, NUM_LEDS_PER_STRIP) {};
};

class ConfigItemPosition : public ConfigItemInt
{
public:
    ConfigItemPosition(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_POSITION, 0, 0, NUM_LEDS_PER_STRIP) {};
};

class ConfigItemColorRotation : public ConfigItemInt
{
public:
    ConfigItemColorRotation(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_COLOR_ROTATION, 0, 0, 5) {};

    virtual String getValueType() { return "String"; };
    virtual String getDisplayString();
};

class ConfigItemBrightnessRotation : public ConfigItemInt
{
private:
    static const int __string_count = 7;
    const String m_infoStrings[__string_count] = {
        "keine / Stillstand",
        "sehr langsam",
        "langsam",
        "mittel",
        "schnell",
        "sehr schnell",
        "keine / Stillstand",
    };

public:
    ConfigItemBrightnessRotation(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_BRIGHTNESS_ROTAION, 0, 0, __string_count - 1) {};

    virtual String getValueType() { return "String"; };
    virtual String getDisplayString() { return m_infoStrings[ getValue() % __string_count ]; };
};

class ConfigItemSpectrum : public ConfigItemInt
{
public:
    ConfigItemSpectrum(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_SPECTRUM, 0, 0, 255) {};

};

class ConfigItemBrightnessGradient : public ConfigItemInt
{
public:
    ConfigItemBrightnessGradient(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_BRIGHTNESS_GRADIENT, 0, 0, 255) {};
};
      
class ConfigItemInfo : public ConfigItemInt
{
private:
    static const int __string_count = 5;
    const String m_infoStrings[__string_count] = {
        "LED-Lampe für Mutti",
        "aus Eiche",
        "zu Weihnachten 2018",
        "von Andre und Christian",
        "und Findus"
    };

public:
    ConfigItemInfo(Config *config)
    : ConfigItemInt(config, CONFIG_ITEM_NAME_INFORMATION, 0, 0, __string_count - 1) {};

    virtual String getValueType() { return "String"; };
    virtual String getDisplayString() { return m_infoStrings[ getValue() % __string_count ]; };
};

#endif