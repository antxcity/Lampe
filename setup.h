#ifndef INC_ANTXCITY_SETUP_H
#define INC_ANTXCITY_SETUP_H

#define LED_BUILTIN_ 1

// Joystick
#define JOY_X_PIN 27
#define JOY_Y_PIN 26
#define JOY_S_PIN 32
#define JOYSTICK_DELAY 500
#define JOYSTICK_RATE  10

// Oled
#define OLED_INTERFACE 0x3c
#define OLED_SCL_PIN 22
#define OLED_SDA_PIN 21


// LED Strip
#define NUM_STRIPS  3
#define NUM_LEDS_PER_STRIP 29
#define DATAPIN_LEDSTRIP_1 5
#define DATAPIN_LEDSTRIP_3 18
#define DATAPIN_LEDSTRIP_2 17
#define BRIGHTNESS  255

// Config
#define JOYSTICK_ITEM_COUNT 14

#define CONFIG_ITEM_NAME_PRESETS                "Vorgaben"
#define CONFIG_ITEM_NAME_TIMER                  "Abschalttimer"
#define CONFIG_ITEM_NAME_BRIGHTNESS             "Helligkeit"
#define CONFIG_ITEM_NAME_HUE                    "Farbton"
#define CONFIG_ITEM_NAME_SATURATION             "Sättigung"
#define CONFIG_ITEM_NAME_STRIPS                 "LED Streifen"
#define CONFIG_ITEM_NAME_COLOR_ROTATION         "Farbwechsel"
#define CONFIG_ITEM_NAME_BRIGHTNESS_ROTAION     "Helligkeitswechs."
#define CONFIG_ITEM_NAME_LINES                  "Zeilen" 
#define CONFIG_ITEM_NAME_POSITION               "Position"
#define CONFIG_ITEM_NAME_SPECTRUM               "Farbverlauf"
#define CONFIG_ITEM_NAME_BRIGHTNESS_GRADIENT    "Helligkeitsverlauf"
#define CONFIG_ITEM_NAME_INFORMATION            "Information"

#endif