#include <FastLED.h>
#include "config.h"

#define NUM_LEDS 13
#define NUM_ANIMATIONS 10

void next_animation();
void next_color();
void set_brightness();
void handle_sequence(CRGB *leds, config *configuration);