// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    XXXXXXX, ___BASE1___, KC_BSPC, KC_BSPC,
    REMOVE,  ___BASE2___, PNP,
    XXXXXXX, ___BASE3___, XXXXXXX,
    KC_VOLD, UPDIR, KC_ESC, _______, LT(_LOWER, KC_SPC), _______, PSTRSE, XXXXXXX, KC_VOLU
  ),
  [_LOWER] = LAYOUT_jack(
    _______, ___LOWER1___, _______, _______,
    _______, ___LOWER2___, _______,
    _______, ___LOWER3___, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_jack(
    _______, ___RAISE1___, _______, _______,
    _______, ___RAISE2___, _______,
    _______, ___RAISE3___, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
