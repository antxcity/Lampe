#include "LedLight.h"

LedLight::LedLight() {
    m_ledstrips[0] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_1>;
    m_ledstrips[1] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_2>;
    m_ledstrips[2] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_3>;

    FastLED.setDither(DISABLE_DITHER);
    resetTimer();
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
                case 2:
                    applyFullLight(config);
                    break;
                case 3:
                    applyReadingLight(config);
                    break;
                case 4: // Rotlicht
                    applyRedLight(config);
                    break;
                case 5: // Blaulicht
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
        int lines = config->getConfigIntValue(CONFIG_ITEM_NAME_LINES);
        int shift_area = (num_leds - lines);
        int position = map(config->getConfigIntValue(CONFIG_ITEM_NAME_POSITION), 0, num_leds, 0, shift_area);
        int color_rotation = config->getConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION);
        int spectrum = config->getConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM);
        int brightness_gradients = 0; //config->getConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS_GRADIENT);
        int brightness_rotation = config->getConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS_ROTAION);
        // get strips config item 
        ConfigItemStrips *ci_strips = dynamic_cast<ConfigItemStrips *>(config->getJoystickConfigItem(CONFIG_ITEM_NAME_STRIPS));
        ConfigItemTimer *ci_timer = dynamic_cast<ConfigItemTimer *>(config->getJoystickConfigItem(CONFIG_ITEM_NAME_TIMER));
        int timeout_value = config->getConfigIntValue(CONFIG_ITEM_NAME_TIMER);

        uint32_t timed_color_shift = 0;
        uint32_t timed_brightness_shift = 255;

        if (color_rotation) 
            timed_color_shift = millis()/(1000/(color_rotation * color_rotation * color_rotation * color_rotation)) % 255;
        if (brightness_rotation) 
        {
            int d = 10000 / brightness_rotation^5;
            timed_brightness_shift = millis()%d;
            timed_brightness_shift = timed_brightness_shift > d/2 ? d-timed_brightness_shift : timed_brightness_shift;
            timed_brightness_shift = map(timed_brightness_shift, 0, d/2, 0, 255);
        }

        long elapsed_time = (millis() - m_last_action_time) / 1000;
        m_timeout = ci_timer->getTimeoutValue();

        // if we reached the timeout
        if (m_timeout > 0 && elapsed_time >= m_timeout) {
            if (m_last_elapsed_time != -1 ) {
                m_last_elapsed_time = -1;

                for ( int n = 0; n < num_leds; n++ ) {
                    for ( int strip_index = 0; strip_index < NUM_STRIPS; strip_index++ ) {
                        m_ledstrips[strip_index]->get_leds()[n] = CRGB::Black;
                    }
                }
                show();
            }
            m_time_left = 0;
        }
        else {
            long restzeitgrenze = 60;
            m_time_left = m_timeout;
            if (m_timeout > 0) {
                m_time_left = m_timeout - elapsed_time;
                restzeitgrenze = min(60, (20 * m_timeout) / 100); // 10 % des timeouts aber höchstens 1 minute
            }
            
            if ( m_last_elapsed_time != elapsed_time ) {
                m_last_elapsed_time = elapsed_time;
            }

            if ( config->isChanged() || brightness_rotation ||  color_rotation || m_time_left <= restzeitgrenze)
            {
                int fade_faktor = 255;
                // wenn restzeitgrenze unterschritten, dann nach dunkel faden
                if ( m_timeout >0 && m_time_left <= restzeitgrenze ) {
                    long praezise_restzeit = max(0, m_timeout * 1000 - (millis() - m_last_action_time));
                    fade_faktor = map(praezise_restzeit, 0, 1000*restzeitgrenze, 0, 255);
                }

                for ( int n = 0; n < num_leds; n++ ) {
                    CRGB color = CRGB::Black;

                    if (n >= position && n < position + lines) {
                        int color_gradient_offset = map(n - position, 0, lines, 0, spectrum * 5);
                        int brightness_gradient_offset = map(n - position, 0, lines, 0, brightness_gradients * 5);

                        int h = (hue + color_gradient_offset + timed_color_shift) % 255;
                        int s = saturation;
                        int v = (brightness); // + brightness_gradient_offset

                        //v = (v * brightness_gradient_offset) / 255;
                        v = (v * timed_brightness_shift) / 255;
                        v = (v * fade_faktor) / 255;

                        color = CHSV(h, s, v);
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
        if (config->isChanged()) {
            config->setUnchanged();
        }
    }
    catch (String error) {
        Serial.println("*** Error:" + error);
    }
}

void LedLight::applyLowLight(Config *config)
{
    try {
        config->setConfigIntValue(CONFIG_ITEM_NAME_TIMER, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS, 100);
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS_ROTAION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS_GRADIENT, 0);
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
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 72);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 147);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_TIMER, 0);
    }
    catch (String error)
    {
        Serial.println("*** Error:" + error);
    }
}

void LedLight::applyFullLight(Config *config)
{
    try {
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS, 255);
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 72);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_TIMER, 0);
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
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 95);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 255);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, m_ledstrips[0]->get_num_leds());
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_TIMER, 0);
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
        config->setConfigIntValue(CONFIG_ITEM_NAME_TIMER, 0);
    }
    catch (String error)
    {
        Serial.println("*** Error:" + error);
    }
}

void LedLight::applyReadingLight(Config *config)
{
    try {
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS, 255);
        config->setConfigIntValue(CONFIG_ITEM_NAME_HUE, 82);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SATURATION, 171);
        config->setConfigIntValue(CONFIG_ITEM_NAME_STRIPS, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_LINES, 8);
        config->setConfigIntValue(CONFIG_ITEM_NAME_POSITION, 29);
        config->setConfigIntValue(CONFIG_ITEM_NAME_COLOR_ROTATION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_BRIGHTNESS_ROTAION, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_SPECTRUM, 0);
        config->setConfigIntValue(CONFIG_ITEM_NAME_TIMER, 6);
    }
    catch (String error)
    {
        Serial.println("*** Error:" + error);
    }
}