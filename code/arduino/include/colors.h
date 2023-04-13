#include <FastLED.h>

#define NUM_RANDOM_RGB    9
#define NUM_STATICCOLORS  38

uint8_t RANDOM_RGB_VALUES[NUM_RANDOM_RGB] = { 0, 32, 64, 96, 128, 160, 192, 224, 255 };

CRGB STATIC_COLORS[NUM_STATICCOLORS] = {
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