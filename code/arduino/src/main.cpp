#include "main.h"

#define PIN_LED           2
#define PIN_BTN_BRIGHTN   3
#define PIN_BTN_STATIC    4
#define PIN_BTN_ANIMATION 5

CRGB leds[NUM_LEDS];
config configuration;

bool btn_down = false;

void setup() 
{
  pinMode(PIN_BTN_ANIMATION, INPUT_PULLUP);
  pinMode(PIN_BTN_STATIC, INPUT_PULLUP);
  pinMode(PIN_BTN_BRIGHTN, INPUT_PULLUP);

  configuration = load_config();

  FastLED.addLeds<WS2811, PIN_LED, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);

  Serial.begin(9600);
}

void loop() 
{
  handle_input();
  handle_sequence(leds, &configuration);
}

void handle_input()
{
  if (digitalRead(PIN_BTN_ANIMATION) == LOW) {
    if (!btn_down) {
      Serial.println("PIN_BTN_ANIMATION");
      next_animation();

      Serial.println(configuration.lightMode);
      Serial.println(configuration.animationSequence);
    }
    btn_down = true;
  }
  else if (digitalRead(PIN_BTN_STATIC) == LOW) {
    if (!btn_down) {
      Serial.println("PIN_BTN_STATIC");
      next_color();

      Serial.println(configuration.lightMode);
      Serial.println(configuration.staticColor);
    }
    btn_down = true;
  }
  else if (digitalRead(PIN_BTN_BRIGHTN) == LOW) {
    if (!btn_down) {
      Serial.println("PIN_BTN_BRIGHTN");
      set_brightness();

      Serial.println(configuration.brightness);
    }
    btn_down = true;
  }
  else if (btn_down) {
    btn_down = false;
  }
}
