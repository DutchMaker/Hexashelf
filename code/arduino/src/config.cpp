#include "config.h"

config DEFAULT_CONFIG = { 255, 0, 0, LightMode::Static };

config load_config()
{
    if (EEPROM.read(0) != 123) {
        return DEFAULT_CONFIG;
    }

    uint8_t brightness = EEPROM.read(1);
    uint8_t animationSequence = EEPROM.read(2);
    uint8_t staticColor = EEPROM.read(3);
    LightMode lightMode = (LightMode)EEPROM.read(4);

    return { brightness, animationSequence, staticColor, lightMode };
}

void save_config(config *c)
{
    EEPROM.write(0, 123);
    EEPROM.write(1, c->brightness);
    EEPROM.write(2, c->animationSequence);
    EEPROM.write(3, c->staticColor);
    EEPROM.write(4, c->lightMode);
}