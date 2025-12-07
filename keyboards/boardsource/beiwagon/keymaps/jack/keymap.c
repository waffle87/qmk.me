// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack(
    LUMINO,  G(KC_Q),  G(KC_R),
    KC_VOLD,  PNP,      KC_VOLU,
    REMOVE,   XRGB_HUI, XRGB_NXT,
    XRGB_TOG, XRGB_HUD, TG(LAYER1)
  ),
  [LAYER1] = LAYOUT_jack(
    QK_BOOT, EE_CLR,  QK_MAKE,
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______
  )
};
// clang-format on

void keyboard_post_init_keymap(void) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; ++i)
    if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW)
      g_led_config.flags[i] &= ~LED_FLAG_UNDERGLOW;
}
