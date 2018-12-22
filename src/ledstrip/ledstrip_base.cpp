#include "ledstrip_base.h"

CLedStripBase::CLedStripBase(int num_leds, int data_pin)
    : _data_pin(data_pin), _num_leds(num_leds)
{
    _leds = new CRGB[_num_leds];
}

CLedStripBase::~CLedStripBase() {
    delete [] _leds;
}

void CLedStripBase::fill_solid(const struct CRGB &color) {
    ::fill_solid(this->get_leds(), this->get_num_leds(), color);
}

void CLedStripBase::show() {
    FastLED.show();
}