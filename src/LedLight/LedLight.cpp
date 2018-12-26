#include "LedLight.h"

LedLight::LedLight() {
    m_ledstrips[0] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_1>;
    m_ledstrips[1] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_2>;
    m_ledstrips[2] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_3>;
}

LedLight::~LedLight() {
    for (int i = 0; i < NUM_STRIPS; i++) {
        delete m_ledstrips[i];
        m_ledstrips[i] = NULL;
    }
}

void LedLight::applyConfig(Config *config) {
    if (ConfigJoystickItem *ci = config->getJoystickConfigItem(HELLIGKEIT_CONFIG_ITEM_INDEX)) {
        ConfigItemInt *ci_int = dynamic_cast<ConfigItemInt *>(ci);
        int hell_index = map(ci_int->getValue(), ci_int->getMinValue(), ci_int->getMaxValue(), 0, m_ledstrips[0]->get_num_leds() - 1);
        m_ledstrips[0]->setSingleLed(hell_index, CRGB::Blue);
        m_ledstrips[0]->show();
    }
}