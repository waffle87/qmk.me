// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "lib/oled.h"
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

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  for (uint8_t i = led_min; i <= led_max; i++)
    if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW)
      rgb_matrix_set_color(i, RGB_OFF);
  return false;
}
#endif // RGB_MATRIX_ENABLE

#ifdef OLED_ENABLE
bool oled_task_keymap(void) {
  render_layer_state();
  return false;
}
#endif // OLED_ENABLE
