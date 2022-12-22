// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle_3x5(
    ___BASE1___,
    ___BASE2___,
    ___BASE3___,
    ___BASE4___
  ),
  [_LOWER] = LAYOUT_waffle_3x5(
    ___LOWER1___,
    ___LOWER2___,
    ___LOWER3___,
    ___LOWER4___
  ),
  [_RAISE] = LAYOUT_waffle_3x5(
    ___RAISE1___,
    ___RAISE2___,
    ___RAISE3___,
    ___RAISE4___
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return 0;
  else
   return 2;
  return rotation;
}

bool oled_task_keymap(void) {
  if (is_keyboard_master())
    layer_anim();
  else
    render_wpm();
  return false;
}
#endif
