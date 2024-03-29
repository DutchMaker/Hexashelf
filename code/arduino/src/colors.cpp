#include <math.h>
#include "colors.h"

CRGB STATIC_COLORS[NUM_STATIC_COLORS] = {
  CRGB(255, 0, 0),
  CRGB(255, 128, 0),
  CRGB(255, 255, 0),
  CRGB(128, 255, 0),
  CRGB(0, 255, 0),
  CRGB(0, 255, 128),
  CRGB(0, 255, 255),
  CRGB(0, 128, 255),
  CRGB(0, 0, 255),
  CRGB(127, 0, 255),
  CRGB(255, 0, 255),
  CRGB(255, 0, 127),
  CRGB(255, 255, 255),
  CRGB(191, 191, 191),
  CRGB(128, 128, 128),
  CRGB(255, 255, 204),
  CRGB(255, 255, 102),
  CRGB(255, 255, 51)
};

CRGB interpolateColor(CRGB color1, CRGB color2, float ratio)
{
    float r = color1.r + (color2.r - color1.r) * ratio;
    float g = color1.g + (color2.g - color1.g) * ratio;
    float b = color1.b + (color2.b - color1.b) * ratio;

    return CRGB((uint8_t)round(r), (uint8_t)round(g), (uint8_t)round(b));
}

CRGB* fadeColors(CRGB color, CRGB target_color, uint8_t steps)
{
    CRGB *fadedColors = (CRGB *) malloc((steps + 1) * sizeof(CRGB));

    for (int j = 0; j <= steps; j++) {
        fadedColors[j] = fadeColor(color, target_color, steps, j);
    }

    return fadedColors;
}

CRGB fadeColor(CRGB color, CRGB target_color, uint8_t range_size, uint8_t step)
{
    float stepSize = 1 / (float)(range_size + 1);
    float ratio = step * stepSize;

    return interpolateColor(color, target_color, ratio);
}

float hue2rgb(float p, float q, float t) 
{
    if (t < 0) {
        t += 1;
    }
    if (t > 1) {
        t -= 1;
    }
    if (t < 1.0 / 6.0) {
        return p + (q - p) * 6 * t;
    }
    if (t < 1.0 / 2.0) {
        return q;
    }
    if (t < 2.0 / 3.0) {
        return p + (q - p) * (2.0 / 3.0 - t) * 6;
    }

    return p;
}

CRGB hslToRgb(float h, float s, float l) 
{
    CRGB rgb;

    if (s == 0) {
        rgb.r = rgb.g = rgb.b = l * 255;
    } 
    else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;

        rgb.r = round(hue2rgb(p, q, h + 1.0 / 3.0) * 255);
        rgb.g = round(hue2rgb(p, q, h) * 255);
        rgb.b = round(hue2rgb(p, q, h - 1.0 / 3.0) * 255);
    }

    return rgb;
}

void print_rgb(CRGB color) 
{
  Serial.print(color.r);
  Serial.print(",");
  Serial.print(color.g);
  Serial.print(",");
  Serial.print(color.b);
  Serial.println("");
}