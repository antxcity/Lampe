#include <FastLED.h>

#define LED_BUILTIN_ 1
#define JOY_X_PIN 27
#define JOY_Y_PIN 26
#define JOY_S_PIN 32

#define NUM_LEDS 29
#define DATA_PIN 5
#define BRIGHTNESS          5

CRGB leds[NUM_LEDS];
bool xstate = false;

void setup() {
  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
  pinMode(JOY_S_PIN, INPUT);

  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(9600);
}

void loop() {
  int x = analogRead(JOY_X_PIN);
  int y = analogRead(JOY_Y_PIN);
  int s = analogRead(JOY_S_PIN);
  Serial.print("x: " + String(x) + " - Y: " + String(y) + " - S: " + String(s) + "\n");
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
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  else if (x > 4000)
    fill_solid(leds, NUM_LEDS, CRGB::White);
  
  FastLED.show();
}
