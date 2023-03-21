#include <EEPROM.h>

enum LightMode { Static, Animated };

typedef struct
{
  char version[3];
  uint8_t brightness;
  uint8_t animationSequence;
  uint8_t staticColor;
  LightMode lightMode;
} config;

config load_config();
void save_config(config *c);