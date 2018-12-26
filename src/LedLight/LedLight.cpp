#include "LedLight.h"

LedLight::LedLight() {
    m_ledstrips[0] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_1>;
    m_ledstrips[1] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_2>;
    m_ledstrips[2] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_3>;

    FastLED.setDither(DISABLE_DITHER);
    m_last_action_time = millis();
    m_last_elapsed_time = 0;
}

LedLight::~LedLight() {
    for (int i = 0; i < NUM_STRIPS; i++) {
        delete m_ledstrips[i];
        m_ledstrips[i] = NULL;
    }
}

void LedLight::show() {
    FastLED.show();
}

void LedLight::resetTimer() {
    m_last_action_time = millis();
}

void LedLight::applyConfig(Config *config) {

    try {
        // if presets config has changed:
        ConfigItem *configItem = config->getChangedItem();   
        if (configItem && configItem->getTitle().equalsIgnoreCase(CONFIG_ITEM_NAME_PRESETS)) {
            ConfigItemPresets *ci_int = dynamic_cast<ConfigItemPresets *>(configItem);

            switch (ci_int->getValue()) {
                case 1: // Tageslicht
                    applyDayLight(config);
                    break;
                case 2: // Rotlicht
                    applyRedLight(config);
                    break;
                case 3: // Blaulicht
                    applyBlueLight(config);
                    break;
            }
        }

        if (config->isChanged()) {
            resetTimer();
        }

        int num_leds = m_ledstrips[0]->get_num_leds();

        int brightness = config->getConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS);
        int hue = config->getConfigIntValue(CONFIG_ITEM_NAME_HUE);
        int saturation = config->getConfigIntValue(CONFIG_ITEM_NAME_SATURATION);
        int lines = config->getConfigIntValue(CONFIG_ITEM_NAME_LINES) + 1;
        int shift_area = (num_leds - lines);
        int position = map(config->getConfigIntValue(CONFIG_ITEM_NAME_POSITION), 0, num_leds, 0, shift_area + 1);
        int rotation_speed = config->getConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION);
        int spectrum = config->getConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM);
        // get strips config item 
        ConfigItemStrips *ci_strips = dynamic_cast<ConfigItemStrips *>(config->getJoystickConfigItem(CONFIG_ITEM_NAME_STRIPS));
        if ( !ci_strips) return;

        uint32_t timed_color_shift = 0;

        if (rotation_speed) 
            timed_color_shift = millis()/(1000/(rotation_speed * rotation_speed * rotation_speed * rotation_speed)) % 255;

        long elapsed_time = (millis() - m_last_action_time) / 1000;
        int timeout_value = 1; // dummy - must be configurable
        long timeout = timeout_value > 0 ? m_timeouts[timeout_value - 1] : 10000000 + elapsed_time;


        // if we reached the timeout
        if (elapsed_time >= timeout) {
            if ( m_last_elapsed_time != -1 ) {
                m_last_elapsed_time = -1;

                for ( int n = 0; n < num_leds; n++ ) {
                    for ( int strip_index = 0; strip_index < NUM_STRIPS; strip_index++ ) {
                        m_ledstrips[strip_index]->get_leds()[n] = CRGB::Black;
                    }
                }
                show();
            }
        }
        else {
            long restzeit = timeout - elapsed_time;
            long restzeitgrenze = min(60, (20 * timeout) / 100); // 10 % des timeouts aber höchstens 1 minute

            if ( m_last_elapsed_time != elapsed_time ) {
                m_last_elapsed_time = elapsed_time;
            }

            if ( config->isChanged() || rotation_speed || restzeit <= restzeitgrenze)
            {
                int fade_faktor = 255;
                // wenn restzeitgrenze unterschritten, dann nach dunkel faden
                if ( restzeit <= restzeitgrenze ) {
                    long praezise_restzeit = max(0, timeout * 1000 - (millis() - m_last_action_time));
                    fade_faktor = map(praezise_restzeit, 0, 1000*restzeitgrenze, 0, 255);
                    //Serial.println("praezise restzeit: " + String(praezise_restzeit) + " -> fade: " + String(fade_faktor) + " Restzeitgrenze: " + String(restzeitgrenze));
                }

                Serial.println("-----------------");
                for ( int n = 0; n < num_leds; n++ ) {
                    CRGB color = CRGB::Black;

                    if (n >= position && n < position + lines) {
                        int ma = map(n - position, 0, lines, 0, spectrum*5);
                        Serial.println("ma: " + String(ma));
                        color = CHSV((hue + ma + timed_color_shift) % 255, saturation, brightness * fade_faktor / 255);
                    }

                    for ( int strip_index = 0; strip_index < NUM_STRIPS; strip_index++ ) {
                        if ( !ci_strips->isStripActive(strip_index) ) {
                            m_ledstrips[strip_index]->get_leds()[n] = CRGB::Black;
                            continue;
                        }

                        m_ledstrips[strip_index]->get_leds()[n] = color;
                    }
                }
                show();
            }
        }
    }
    catch (String error) {
        Serial.println("*** Error:" + error);
    }
}

void LedLight::applyLowLight(Config *config)
{
    try {
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS, 100);
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 255);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 5);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
    }
    catch (String error)
    {
        Serial.println("*** Error:" + error);
    }
}

void LedLight::applyDayLight(Config *config)
{
    try {
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS, 100);
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 45);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 255);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
    }
    catch (String error)
    {
        Serial.println("*** Error:" + error);
    }
}

void LedLight::applyRedLight(Config *config)
{
    try {
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS, 100);
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 255);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
    }
    catch (String error)
    {
        Serial.println("*** Error:" + error);
    }
}

void LedLight::applyBlueLight(Config *config)
{
    try {
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS, 100);
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 171);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 255);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
    }
    catch (String error)
    {
        Serial.println("*** Error:" + error);
    }
}