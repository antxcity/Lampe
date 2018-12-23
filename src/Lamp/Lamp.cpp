#include "Lamp.h"

Lamp::Lamp() 
    : m_joystick(JOY_X_PIN, JOY_Y_PIN, JOY_S_PIN)
{
    m_ledstrips[0] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_1>;
    m_ledstrips[1] = new LedStrip<NUM_LEDS_PER_STRIP, DATAPIN_LEDSTRIP_2>;

    m_joystick.setJoyStickHandler(this);

    m_oled = new Oled(OLED_INTERFACE, OLED_SCL_PIN, OLED_SDA_PIN, GEOMETRY_128_32);
    m_config = new Config;
    m_controller = new Controller(m_oled, m_config);

}

Lamp::~Lamp() {
    for (int i = 0; i < NUM_STRIPS; i++) {
        delete m_ledstrips[i];
        m_ledstrips[i] = NULL;
    }
}

void Lamp::loop() {
    m_joystick.read();
}

void Lamp::onLeftIn()     { m_ledstrips[0]->fill_solid(CRGB::Green); m_controller->onJoystickLeft(); }
void Lamp::onLeftOut()    { m_ledstrips[0]->fill_solid(CRGB::Black); }
void Lamp::onRightIn()    { m_ledstrips[0]->fill_solid(CRGB::Red); m_controller->onJoystickRight(); }
void Lamp::onRightOut()   { m_ledstrips[0]->fill_solid(CRGB::Black); }
void Lamp::onDownIn()     { m_ledstrips[1]->fill_solid(CRGB::Blue); m_controller->onJoystickDown(); }
void Lamp::onDownOut()    { m_ledstrips[1]->fill_solid(CRGB::Black); }
void Lamp::onUpIn()       { m_ledstrips[1]->fill_solid(CRGB::White); m_controller->onJoystickUp(); }
void Lamp::onUpOut()      { m_ledstrips[1]->fill_solid(CRGB::Black); }
void Lamp::onSwitchDown() { m_ledstrips[0]->fill_solid(CRGB::Orange); m_ledstrips[1]->fill_solid(CRGB::Orange); }
void Lamp::onSwitchUp()   { m_ledstrips[0]->fill_solid(CRGB::Black); m_ledstrips[1]->fill_solid(CRGB::Black); m_controller->onJoystickButton(); }
void Lamp::onChanged()    { m_ledstrips[0]->show(); m_ledstrips[1]->show(); }
