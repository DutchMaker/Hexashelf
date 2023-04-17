#ifndef config_h
#define config_h

#include <EEPROM.h>

enum LightMode { Static, Animated };

typedef struct
{
  uint8_t brightness;
  uint8_t animation_sequence;
  uint8_t static_color;
  LightMode light_mode;
} config;

config load_config();
void save_config(config *c);

#endif