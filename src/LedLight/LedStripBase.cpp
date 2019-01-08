#include "LedStripBase.h"

LedStripBase::LedStripBase(int num_leds, int data_pin)
    : _data_pin(data_pin), _num_leds(num_leds)
{
    _leds = new CRGB[_num_leds];
}

LedStripBase::~LedStripBase() {
    delete [] _leds;
}

void LedStripBase::fill_solid(const struct CRGB &color) {
    ::fill_solid(this->get_leds(), this->get_num_leds(), color);
}

void LedStripBase::setSingleLed(int index, const struct CRGB &color) {
    if (index < 0 || index >= _num_leds)
        return;

    for (int i = 0; i < _num_leds; i++) {
        _leds[i] = CRGB::Black;
    }

    _leds[index] = color;
}