#include "main.h"

CRGB leds[NUM_LEDS];
config configuration;

void setup() 
{
  pinMode(PIN_BTN_ANIMATION, INPUT_PULLUP);
  pinMode(PIN_BTN_STATIC, INPUT_PULLUP);
  pinMode(PIN_BTN_BRIGHTN, INPUT_PULLUP);

  configuration = load_config();

  FastLED.addLeds<WS2811, PIN_LED, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);

  Serial.begin(9600);
}

void loop() 
{
  handle_input();
  handle_sequence(leds, &configuration);
}