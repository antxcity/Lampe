#include <FastLED.h>

#include "src/ledstrip/ledstrip_base.h"
#include "src/ledstrip/ledstrip.h"

#define LED_BUILTIN_ 1
#define JOY_X_PIN 27
#define JOY_Y_PIN 26
#define JOY_S_PIN 32

// #define NUM_LEDS 29
// #define DATA_PIN 5
#define BRIGHTNESS          5

bool xstate = false;

CLedStripBase *ledstrip1;

void setup() {
    pinMode(JOY_X_PIN, INPUT);
    pinMode(JOY_Y_PIN, INPUT);
    pinMode(JOY_S_PIN, INPUT);

    ledstrip1 = new CLedStrip<29, 5>;
    Serial.begin(9600);
}

void loop() {
    int x = analogRead(JOY_X_PIN);
    int y = analogRead(JOY_Y_PIN);
    int s = analogRead(JOY_S_PIN);
    Serial.print("X: " + String(x) + " - Y: " + String(y) + " - S: " + String(s) + "\n");
    delay(100);

    if (x > 4000) {
        if (!xstate) {
            xstate = true;
            setLeds(x);
        }
    }
    else if (x < 200) {
        if (xstate) {
            xstate = false;
            setLeds(x);
        }
    }
}

void setLeds(int x) {
    if (x < 200)
        fill_solid(ledstrip1->get_leds(), ledstrip1->get_num_leds(), CRGB::Black);
    else if (x > 4000)
        fill_solid(ledstrip1->get_leds(), ledstrip1->get_num_leds(), CRGB::Blue);

    FastLED.show();
}
