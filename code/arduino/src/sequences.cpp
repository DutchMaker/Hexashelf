#include "sequences.h"
#include "colors.h"

unsigned long last_update = 0;
LightMode current_lightMode;
CRGB *leds_pointer;
config *config_pointer;

void handle_animation();
void handle_static();
void handle_test_animation();

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

  handle_test_animation();
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

void handle_onebyone()
{
}

void handle_test_animation()
{
  if (millis() - last_update > 250) {
    
    for (int i = 0; i < NUM_LEDS; i++) {
      leds_pointer[i] = CRGB(RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)], RANDOM_RGB_VALUES[random(0, NUM_RANDOM_RGB)]);
    }

    FastLED.show();

    last_update = millis();
  }
}