// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "waffle.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    ___BASE1___, KC_BSPC,
    ___BASE2___,
    ___BASE3___,
    KC_MPLY, KC_NO, LWRSPC, C(S(KC_V)), RWORD
  ),
  [_LOWER] = LAYOUT_waffle(
    ___LOWER1___, KC_DEL,
    ___LOWER2___,
    ___LOWER3___,
    KC_MUTE, _______, _______, RGB_MOD, RGB_TOG
  )
};
// clang-format on
