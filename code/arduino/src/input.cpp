#include "input.h"

bool btn_down = false;

void handle_input()
{
  if (digitalRead(PIN_BTN_ANIMATION) == LOW) {
    if (!btn_down) {
      next_animation();
    }
    btn_down = true;
  }
  else if (digitalRead(PIN_BTN_STATIC) == LOW) {
    if (!btn_down) {
      next_color();
    }
    btn_down = true;
  }
  else if (digitalRead(PIN_BTN_BRIGHTN) == LOW) {
    if (!btn_down) {
      set_brightness();
    }
    btn_down = true;
  }
  else if (btn_down) {
    btn_down = false;
  }
}
