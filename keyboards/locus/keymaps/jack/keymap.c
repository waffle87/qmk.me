// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    _______, ___BASE1___, _______,
    _______, ___BASE2___,
    _______, ___BASE3___,
    UPDIR, KC_ESC, LWRSPC, RSEBSP, C(S(KC_V)), PNP
  ),
  [_LOWER] = LAYOUT_jack(
    _______, ___LOWER1___, _______,
    _______, ___LOWER2___,
    _______, ___LOWER3___,
    _______, _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_jack(
    _______, ___RAISE1___, _______,
    _______, ___RAISE2___,
    _______, ___RAISE3___,
    _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
