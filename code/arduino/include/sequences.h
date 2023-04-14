#include <FastLED.h>
#include "config.h"

#define NUM_LEDS 14
#define NUM_ANIMATIONS 3

void next_animation();
void next_color();
void set_brightness();
void handle_sequence(CRGB *leds, config *configuration);