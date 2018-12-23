#ifndef __INC_ANTXCITY_LED_STRIP_BASE_H
#define __INC_ANTXCITY_LED_STRIP_BASE_H

#include <Arduino.h>
#include <FastLED.h>

class LedStripBase {
    private:
        int _data_pin;
        int _num_leds;
        bool _changed = true;
        CRGB *_leds;

    public:
        LedStripBase(int num_leds, int data_pin);
        ~LedStripBase();

        inline int get_data_pin() { return _data_pin; };
        inline int get_num_leds() { return _num_leds; };
        inline CRGB *get_leds() { return _leds; };
        inline int get_default_brightness() { return 2; };

        void fill_solid(const struct CRGB &color);
        void setSingleLed(int index, const struct CRGB &color);
        void show();
};

#endif