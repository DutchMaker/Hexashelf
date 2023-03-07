#include "main.h"

#define LED_PIN           7
#define NUM_LEDS          3
#define NUM_STATICCOLORS  38
#define NUM_RANDOM_RGB    9

CRGB leds[NUM_LEDS];

enum LightMode { Static, Random, Animated };

LightMode lightMode = LightMode::Static;
uint8_t brightness = 255;
uint8_t animationSequence = 0;
uint8_t staticColor = 0;

uint8_t random_rgb_values[NUM_RANDOM_RGB] = { 0, 32, 64, 96, 128, 160, 192, 224, 255 };

CRGB staticColors[NUM_STATICCOLORS] = {
  CRGB(255, 0,    0),
  CRGB(0,   255,  0),
  CRGB(0,   0,    255),
  CRGB(255, 255,  255),
  CRGB(0,   255,  255),
  CRGB(255, 0,    255),
  CRGB(255, 255,    0),
  CRGB(128,   0,    0),
  CRGB(0,   128,    0),
  CRGB(0,   0,    128),
  CRGB(128, 128,  128),
  CRGB(0,   128,  128),
  CRGB(128,   0,  128),
  CRGB(128, 128,    0),
  CRGB(255,   0,  128),
  CRGB(255, 128,    0),
  CRGB(128,   0,  255),
  CRGB(128, 255,    0),
  CRGB(255, 128,  128),
  CRGB(128, 128,  255),
  CRGB(128, 255,  128),
  CRGB(0,   255,  128),
  CRGB(0,   128,  255),
  CRGB(255, 128,    0),
  CRGB(64,  0,    255),
  CRGB(255, 64,   128),
  CRGB(255, 128,   64),
  CRGB(64,  64,    64),
  CRGB(64,  0,     64),
  CRGB(64,  64,     0),
  CRGB(0,   64,    64),
  CRGB(128, 64,     0),
  CRGB(0,   128,   64),
  CRGB(128, 255,   64),
  CRGB(128, 0,     64),
  CRGB(64,  128,    0),
  CRGB(64,  0,    128),
  CRGB(0,   64,   128),
};


void setup() 
{
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
}

void loop() 
{
  // Static colors
  /*
  for (int i = 0; i < NUM_STATICCOLORS; i++) {
    show_all_crgb(staticColors[i]);
    delay(500);
  }
  */

  // Random colors
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(random_rgb_values[random(0, NUM_RANDOM_RGB)], random_rgb_values[random(0, NUM_RANDOM_RGB)], random_rgb_values[random(0, NUM_RANDOM_RGB)]);
  }

  FastLED.show();
  delay(250);

  //FastLED.setBrightness(brightness);

  //show_all(255, 255, 255);


  //test_leds();
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

void show_all_crgb(CRGB rgb) 
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = rgb;
  }

  FastLED.show();
}
