#include "config.h"

config DEFAULT_CONFIG = { "V1", 255, 0, 0, LightMode::Static };

config load_config()
{
    return DEFAULT_CONFIG;
}

void save_config(config *c)
{
}