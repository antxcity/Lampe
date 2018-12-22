#include "lamp.h"

CLamp::CLamp() 
    : m_joystick(JOY_X_PIN, JOY_Y_PIN, JOY_S_PIN)
{
    m_ledstrips[0] = new CLedStrip<29, 5>;
    m_ledstrips[1] = new CLedStrip<29, 18>;

    m_joystick.setJoyStickHandler(this);
}

CLamp::~CLamp() {
    for (int i = 0; i < NUM_STRIPS; i++) {
        delete m_ledstrips[i];
        m_ledstrips[i] = NULL;
    }
}

void CLamp::loop() {
    m_joystick.read();
}

void CLamp::onLeftIn()     { m_ledstrips[0]->fill_solid(CRGB::Green); }
void CLamp::onLeftOut()    { m_ledstrips[0]->fill_solid(CRGB::Black); }
void CLamp::onRightIn()    { m_ledstrips[0]->fill_solid(CRGB::Red); }
void CLamp::onRightOut()   { m_ledstrips[0]->fill_solid(CRGB::Black); }
void CLamp::onDownIn()     { m_ledstrips[1]->fill_solid(CRGB::Blue); }
void CLamp::onDownOut()    { m_ledstrips[1]->fill_solid(CRGB::Black); }
void CLamp::onUpIn()       { m_ledstrips[1]->fill_solid(CRGB::White); }
void CLamp::onUpOut()      { m_ledstrips[1]->fill_solid(CRGB::Black); }
void CLamp::onSwitchDown() { m_ledstrips[0]->fill_solid(CRGB::Orange); m_ledstrips[1]->fill_solid(CRGB::Orange); }
void CLamp::onSwitchUp()   { m_ledstrips[0]->fill_solid(CRGB::Black); m_ledstrips[1]->fill_solid(CRGB::Black); }
void CLamp::onChanged()    { m_ledstrips[0]->show(); m_ledstrips[1]->show(); }
