// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle_3x6(
    KC_NO, ___BASE1___, KC_NO,
    KC_NO, ___BASE2___, KC_NO,
    KC_NO, ___BASE3___, KC_NO,
           ___BASE4___
  ),
  [_LOWER] = LAYOUT_waffle_3x6(
    KC_NO, ___LOWER1___, KC_NO,
    KC_NO, ___LOWER2___, KC_NO,
    KC_NO, ___LOWER3___, KC_NO,
           ___LOWER4___
  ),
  [_RAISE] = LAYOUT_waffle_3x6(
    KC_NO, ___RAISE1___, KC_NO,
    KC_NO, ___RAISE2___, KC_NO,
    KC_NO, ___RAISE3___, KC_NO,
           ___RAISE4___
  )
};
// clang-format on

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

bool oled_task_keymap(void) {
  layer_status();
  oled_set_cursor(0, 3);
  felix_dog();
  oled_set_cursor(0, 7);
  render_wpm();
  render_keylog();
  render_mod_status();
  return false;
}
#endif // OLED_ENABLE
