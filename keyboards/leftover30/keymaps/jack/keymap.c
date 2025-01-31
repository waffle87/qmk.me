// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    ___BASE1___, KC_BSPC,
    ___BASE2___,
    ___BASE3___,
    KC_MPLY, XXXXXXX, LWRSPC, PSTRSE, XXXXXXX
  ),
  [_LOWER] = LAYOUT_jack(
    ___LOWER1___, _______,
    ___LOWER2___,
    ___LOWER3___,
    _______, _______, _______, _______, _______, 
  ),
  [_RAISE] = LAYOUT_jack(
    ___RAISE1___, _______,
    ___RAISE2___,
    ___RAISE3___,
    _______, _______, _______, _______, _______, 
  )
};
// clang-format on
