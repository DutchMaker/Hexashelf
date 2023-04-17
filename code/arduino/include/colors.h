#ifndef colors_h
#define colors_h

#include <FastLED.h>
#include "constants.h"

extern CRGB STATIC_COLORS[NUM_STATIC_COLORS];

CRGB* fadeColors(CRGB color, CRGB target_color, uint8_t steps);
CRGB fadeColor(CRGB color, CRGB target_color, uint8_t range_size, uint8_t step);
CRGB hslToRgb(float h, float s, float l);
float hue2rgb(float p, float q, float t);

void print_rgb(CRGB color);

#endif