#include "controller.h"
#include "colors.h"

unsigned long last_update = 0;
LightMode current_light_mode;
CRGB *leds_pointer;
config *config_pointer;

CRGB *animation_colors;
uint16_t animation_loop = 0;
uint8_t animation_state = 0;
uint8_t animation_setup = 0;

void handle_animation();
void handle_static();
void handle_animation_0();
void handle_animation_1();
void handle_animation_2();
void handle_animation_3();
void handle_animation_4();
void setup_animation_1();
void setup_animation_4();

void next_animation()
{
  if (config_pointer->light_mode != LightMode::Animated) {
    config_pointer->light_mode = LightMode::Animated;
  }
  else {
    if (config_pointer->animation_sequence < NUM_ANIMATIONS - 1) {
      config_pointer->animation_sequence++;
    }
    else {
      config_pointer->animation_sequence = 0;
    }
  }

  save_config(config_pointer);
}

void next_color()
{
  if (config_pointer->light_mode != LightMode::Static) {
    config_pointer->light_mode = LightMode::Static;
  }
  else {
    if (config_pointer->static_color < NUM_STATIC_COLORS - 1) {
      config_pointer->static_color++;
    }
    else {
      config_pointer->static_color = 0;
    }
  }

  animation_setup = 0;

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
  if (config_pointer->light_mode != LightMode::Animated) {
    return;
  }

  switch (config_pointer->animation_sequence) {
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
  if (config_pointer->light_mode != LightMode::Static) {
    return;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds_pointer[i] = STATIC_COLORS[config_pointer->static_color];
  }

  FastLED.show();
}

void handle_animation_0()
{
  // Random colors
  if (millis() - last_update > 250) {

    for (int i = 0; i < NUM_LEDS; i++) {
      leds_pointer[i] = CRGB(random(0, 256), random(0, 256), random(0, 256));
    }

    FastLED.show();

    last_update = millis();
  }
}

void handle_animation_1()
{
  if (animation_setup != 1) {
    setup_animation_1();
  }

  // Move configured static color across all leds.
  if (millis() - last_update > 200) {
    
    for (int i = 0; i < NUM_LEDS; i++) {
      uint16_t color_i = i + animation_loop;

      if (color_i >= NUM_LEDS) {
        color_i -= NUM_LEDS;
      }

      leds_pointer[i] = animation_colors[color_i];
    }

    if (animation_loop++ >= NUM_LEDS) {
      animation_loop = 0;
    }

    FastLED.show();

    last_update = millis();
  }
}

void handle_animation_2()
{
  // Gradually change color for all LEDs.
  if (millis() - last_update > 100) {
    float hue = (float)animation_loop / 360;
    CRGB color = hslToRgb(hue, 1, 0.5);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds_pointer[i] = color;
    }

    if (animation_loop++ >= 360) {
      animation_loop = 0;
    }

    FastLED.show();

    last_update = millis();
  }
}

void handle_animation_3()
{
  // Gradually change color from one begin LED to end LED.
  if (millis() - last_update > 100) {

    for (int i = 0; i < NUM_LEDS; i++) {
      float hue = (float)(i + animation_loop) / 360;
      CRGB color = hslToRgb(hue, 1, 0.5);
      leds_pointer[i] = color;
    }

    if (animation_loop++ >= 360 - NUM_LEDS) {
      animation_loop = 0;
    }

    FastLED.show();

    last_update = millis();
  }
}

void handle_animation_4()
{
  // if (!animation_colors_3_setup_done) {
  //   setup_animation_colors_3();
  // }

  // // Move wave of colors over all LEDs while changing color
  // if (millis() - last_update > 50) {

  // }
}

void setup_animation_1()
{
  if (animation_colors != NULL) {
    free(animation_colors);
  }

  animation_colors = (CRGB *) malloc((NUM_LEDS + 1) * sizeof(CRGB));

  uint8_t range_size = 14;
  CRGB standard_color = CRGB(128, 128, 128);

  for (uint8_t i = 0; i < NUM_LEDS - range_size; i++) {
    animation_colors[i] = standard_color;
  }

  CRGB* range1 = fadeColors(standard_color, STATIC_COLORS[config_pointer->static_color], (range_size / 2) - 1);
  CRGB* range2 = fadeColors(STATIC_COLORS[config_pointer->static_color], standard_color, (range_size / 2) - 1);
  
  for (uint8_t i = 0; i < range_size / 2; i++) {
    animation_colors[NUM_LEDS - range_size + i] = range1[i];
    animation_colors[NUM_LEDS - (range_size / 2) + i] = range2[i];
  }

  animation_setup = 1;
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