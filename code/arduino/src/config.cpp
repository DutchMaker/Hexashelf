#include "config.h"

config DEFAULT_CONFIG = { 255, 0, 0, LightMode::Static };

config load_config()
{
    if (EEPROM.read(0) != 123) {
        return DEFAULT_CONFIG;
    }

    uint8_t brightness = EEPROM.read(1);
    uint8_t animation_sequence = EEPROM.read(2);
    uint8_t static_color = EEPROM.read(3);
    LightMode light_mode = (LightMode)EEPROM.read(4);

    return { brightness, animation_sequence, static_color, light_mode };
}

void save_config(config *c)
{
    EEPROM.write(0, 123);
    EEPROM.write(1, c->brightness);
    EEPROM.write(2, c->animation_sequence);
    EEPROM.write(3, c->static_color);
    EEPROM.write(4, c->light_mode);
}