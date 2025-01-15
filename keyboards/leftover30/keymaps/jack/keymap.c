// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    ___BASE1___, KC_BSPC,
    ___BASE2___,
    ___BASE3___,
    KC_MPLY, XXXXXXX, LWRSPC, C(S(KC_V)), XXXXXXX
  ),
  [_LOWER] = LAYOUT_jack(
    ___LOWER1___, KC_DEL,
    ___LOWER2___,
    ___LOWER3___,
    KC_MUTE, _______, _______, RGB_MOD, RGB_TOG
  )
};
// clang-format on
