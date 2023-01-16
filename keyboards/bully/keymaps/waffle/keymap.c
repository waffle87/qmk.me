// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    KC_NO, ___BASE1___, PNP,
    KC_NO, ___BASE2___, KC_BSPC,
    KC_NO, ___BASE3___, KC_NO,
    KC_VOLD, UPDIR, KC_ESC, LWRSPC, C(S(KC_V)), MO(_RAISE), KC_VOLU
  ),
  [_LOWER] = LAYOUT_waffle(
    _______, ___LOWER1___, _______,
    _______, ___LOWER2___, _______,
    _______, ___LOWER3___, _______,
    _______, _______, _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_waffle(
    _______, ___RAISE1___, _______,
    _______, ___RAISE2___, _______,
    _______, ___RAISE3___, _______,
    _______, _______, _______, _______, _______, _______, _______
  )
};