#include <FastLED.h>

#define NUM_RANDOM_RGB    9
#define NUM_STATICCOLORS  38

extern uint8_t RANDOM_RGB_VALUES[NUM_RANDOM_RGB];
extern CRGB STATIC_COLORS[NUM_STATICCOLORS];

CRGB* fadeColors(CRGB color, CRGB targetColor, uint8_t steps);
CRGB fadeColor(CRGB color, CRGB targetColor, uint8_t rangeSize, uint8_t step);
void print_rgb(CRGB color);

CRGB hslToRgb(float h, float s, float l);
float hue2rgb(float p, float q, float t);