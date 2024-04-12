// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    ___BASE1___, PNP,
    ___BASE2___,
    ___BASE3___,
    KC_VOLD, KC_ESC, LWRSPC, RSEBSP, C(S(KC_V)), KC_VOLU
  ),
  [_LOWER] = LAYOUT_waffle(
    ___LOWER1___, _______,
    ___LOWER2___,
    ___LOWER3___,
    _______, TABLE1, _______, _______, TABLE2, _______
  ),
  [_RAISE] = LAYOUT_waffle(
    ___RAISE1___, _______,
    ___RAISE2___,
    ___RAISE3___,
    _______, _______, _______, _______, _______, _______
  )
};
