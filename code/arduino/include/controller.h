#ifndef controller_h
#define controller_h

#include <FastLED.h>
#include "config.h"

void next_animation();
void next_color();
void set_brightness();
void handle_sequence(CRGB *leds, config *configuration);

#endif