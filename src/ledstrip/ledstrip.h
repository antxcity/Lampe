#ifndef __INC_ANTXCITY_LED_STRIP_H
#define __INC_ANTXCITY_LED_STRIP_H

#include <Arduino.h>
#include "ledstrip_base.h"

template<int NUM_LEDS, int DATA_PIN>
class CLedStrip : public CLedStripBase
{
    public:
        CLedStrip();
};

template<int NUM_LEDS, int DATA_PIN>
CLedStrip<NUM_LEDS, DATA_PIN>::CLedStrip() : CLedStripBase(NUM_LEDS, DATA_PIN)
{
    pinMode(DATA_PIN, OUTPUT);
    FastLED.addLeds<WS2811, DATA_PIN, RGB>(get_leds(), NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(get_default_brightness());
}

#endif