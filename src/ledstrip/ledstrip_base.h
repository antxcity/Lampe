#ifndef __INC_ANTXCITY_LED_STRIP_BASE_H
#define __INC_ANTXCITY_LED_STRIP_BASE_H

#include <Arduino.h>
#include <FastLED.h>

class CLedStripBase {
    private:
        int _data_pin;
        int _num_leds;
        CRGB *_leds;

    public:
        CLedStripBase(int num_leds, int data_pin);
        ~CLedStripBase();

        inline int get_data_pin() { return _data_pin; };
        inline int get_num_leds() { return _num_leds; };
        inline CRGB *get_leds() { return _leds; };
        inline int get_default_brightness() { return 5; };
};

#endif