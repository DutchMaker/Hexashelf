#include "main.h"

#define LED_PIN     7
#define NUM_LEDS    3

CRGB leds[NUM_LEDS];

void setup() 
{
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
}

void loop() 
{
  test_leds();
}

void test_leds()
{
  for (uint8_t i = 0; i < 255; i++) {
    show_all(i, 0, 0);
  }

  for (uint8_t i = 0; i < 255; i++) {
    show_all(255, i, 0);
  }

  for (uint8_t i = 0; i < 255; i++) {
    show_all(255, 255, i);
  }

  for (uint8_t i = 255; i > 0; i--) {
    show_all(255, i, 255);
  }

  for (uint8_t i = 255; i > 0; i--) {
    show_all(i, 0, 255);
  }

  for (uint8_t i = 0; i < 255; i++) {
    show_all(0, i, 255);
  }

  for (uint8_t i = 255; i > 0; i--) {
    show_all(0, 255, i);
  }

  for (uint8_t i = 255; i > 0; i--) {
    for (uint8_t j = 0; j > 255; j++) {
      show_all(j, i, 0);
    }
  }

  for (uint8_t i = 255; i > 0; i--) {
    //leds[0]= CRGB(i, 0, 0);
    show_all(i, 0, 0);
  }
}

void show_all(uint8_t r, uint8_t g, uint8_t b) 
  {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i]= CRGB(r, g, b);
  }

  FastLED.show();
}
