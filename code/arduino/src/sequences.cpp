#include "sequences.h"
#include "colors.h"

unsigned long last_update = 0;
LightMode current_lightMode;
CRGB *leds_pointer;
config *config_pointer;

CRGB *animation_colors_1;
CRGB *animation_colors_3;
const uint8_t animation_3_num_colors = 20;
const uint8_t animation_3_num_colors_rangesize = 40;
bool animation_colors_1_setup_done = false;
bool animation_colors_3_setup_done = false;

uint16_t loop_counter = 0;

void handle_animation();
void handle_static();
void handle_animation_0();
void handle_animation_1();
void handle_animation_2();
void handle_animation_3();
void setup_animation_colors_1();
void setup_animation_colors_3();

void next_animation()
{
  if (config_pointer->lightMode != LightMode::Animated) {
    config_pointer->lightMode = LightMode::Animated;
  }
  else {
    if (config_pointer->animationSequence < NUM_ANIMATIONS - 1) {
      config_pointer->animationSequence++;
    }
    else {
      config_pointer->animationSequence = 0;
    }
  }

  save_config(config_pointer);
}

void next_color()
{
  if (config_pointer->lightMode != LightMode::Static) {
    config_pointer->lightMode = LightMode::Static;
  }
  else {
    if (config_pointer->staticColor < NUM_STATICCOLORS - 1) {
      config_pointer->staticColor++;
    }
    else {
      config_pointer->staticColor = 0;
    }
  }

  setup_animation_colors_1();
  save_config(config_pointer);
}

void set_brightness()
{
  if (config_pointer->brightness >= 16) {
    config_pointer->brightness -= 16;
  }
  else {
    config_pointer->brightness = 255;
  }

  FastLED.setBrightness(config_pointer->brightness);

  save_config(config_pointer);
}

void handle_sequence(CRGB *leds, config *configuration)
{
    leds_pointer = leds;
    config_pointer = configuration;
    
    handle_animation();
    handle_static();
}

void handle_animation()
{
  if (config_pointer->lightMode != LightMode::Animated) {
    return;
  }

  switch (config_pointer->animationSequence) {
    case 1:
      handle_animation_1();
      break;
    case 2:
      handle_animation_2();
      break;
    case 3:
      handle_animation_3();
      break;
    default:
      handle_animation_0();
      break;
  }
}

void handle_static()
{
  if (config_pointer->lightMode != LightMode::Static) {
    return;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds_pointer[i] = STATIC_COLORS[config_pointer->staticColor];
  }

  FastLED.show();
}

/***
 * ANIMATION SEQUENCES 
 **************************/

void handle_animation_0()
{
  // Random colors
  if (millis() - last_update > 250) {

    for (int i = 0; i < NUM_LEDS; i++) {
      leds_pointer[i] = CRGB(RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)]);
    }

    FastLED.show();

    last_update = millis();
  }
}

void handle_animation_1()
{
  if (!animation_colors_1_setup_done) {
    setup_animation_colors_1();
  }

  // Move configured static color across all leds.
  if (millis() - last_update > 200) {
    
    for (int i = 0; i < NUM_LEDS; i++) {
      uint16_t color_i = i + loop_counter;

      if (color_i >= NUM_LEDS) {
        color_i -= NUM_LEDS;
      }

      leds_pointer[i] = animation_colors_1[color_i];
    }

    if (loop_counter++ >= NUM_LEDS) {
      loop_counter = 0;
    }

    FastLED.show();

    last_update = millis();
  }
}

void handle_animation_2()
{
  // Gradually change color for all LEDs.
  if (millis() - last_update > 100) {
    float hue = (float)loop_counter / 360;
    CRGB color = hslToRgb(hue, 1, 0.5);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds_pointer[i] = color;
    }

    if (loop_counter++ >= 360) {
      loop_counter = 0;
    }

    FastLED.show();

    last_update = millis();
  }
}

void handle_animation_3()
{
  if (!animation_colors_3_setup_done) {
    setup_animation_colors_3();
  }

  // Move wave of colors over all LEDs while changing color
  if (millis() - last_update > 50) {

  }
}

void setup_animation_colors_1()
{
  animation_colors_1 = (CRGB *) malloc((NUM_LEDS + 1) * sizeof(CRGB));

  uint8_t rangeSize = 14;
  CRGB standard_color = CRGB(128, 128, 128);

  for (uint8_t i = 0; i < NUM_LEDS - rangeSize; i++) {
    animation_colors_1[i] = standard_color;
  }

  CRGB* range1 = fadeColors(standard_color, STATIC_COLORS[config_pointer->staticColor], (rangeSize / 2) - 1);
  CRGB* range2 = fadeColors(STATIC_COLORS[config_pointer->staticColor], standard_color, (rangeSize / 2) - 1);
  
  for (uint8_t i = 0; i < rangeSize / 2; i++) {
    animation_colors_1[NUM_LEDS - rangeSize + i] = range1[i];
    animation_colors_1[NUM_LEDS - (rangeSize / 2) + i] = range2[i];
  }

  animation_colors_1_setup_done = true;
}

void setup_animation_colors_3()
{
  // Serial.println("setup 3");
  // animation_3_num_colors = 2;
  // animation_colors_3 = (CRGB *) malloc((animation_3_num_colors * animation_3_num_colors_rangesize + 1) * sizeof(CRGB));

  // CRGB start = CRGB(RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)]);
  // CRGB prev;

  // uint16_t cindex = 0;

  // for (uint8_t i = 0; i < animation_3_num_colors; i++) {
  //   CRGB s;
  //   CRGB e = CRGB(RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)]);
  //   CRGB* range;
  //   uint8_t rangesize = animation_3_num_colors_rangesize;

  //   if (i == 0) {
  //     s = start;
  //     rangesize /= 2;
  //   }
  //   else if (i == animation_3_num_colors - 1) {
  //     e = start;
  //     rangesize /= 2;
  //   }
  //   else {
  //     s = prev;
  //   }

  //   range = fadeColors(s, e, rangesize);
  //   prev = e;

  //   for (uint8_t r = 0; r < rangesize; r++) {
  //     animation_colors_3[cindex++] = range[r];
  //   }
  // }

  // for (uint16_t i = 0; i < cindex - 1; i++) {
  //   print_rgb(animation_colors_3[i]);
  // }

  // animation_colors_3_setup_done = true;
}