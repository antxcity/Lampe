#include "ledstrip_base.h"

CLedStripBase::CLedStripBase(int num_leds, int data_pin)
    : _num_leds(num_leds), _data_pin(data_pin)
{
    _leds = new CRGB[_num_leds];
}

CLedStripBase::~CLedStripBase() {
    delete [] _leds;
}