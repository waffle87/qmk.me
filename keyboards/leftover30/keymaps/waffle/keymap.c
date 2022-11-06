// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "waffle.h"
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
    KC_MUTE, KC_TRNS, KC_TRNS, RGB_MOD, RGB_TOG
  )
};
