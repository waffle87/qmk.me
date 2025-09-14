// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack_all(
    ___BASE1___, PNP,
    ___BASE2___,
    ___BASE3___,
    KC_VOLD, KC_ESC, XXXXXXX, LWRSPC, XXXXXXX, RSEBSP, XXXXXXX, C(S(KC_V)), KC_VOLU
  ),
  [_LOWER] = LAYOUT_jack_all(
    ___LOWER1___, _______,
    ___LOWER2___,
    ___LOWER3___,
    _______, _______, _______, _______, _______, SWTCH, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_jack_all(
    ___RAISE1___, _______,
    ___RAISE2___,
    ___RAISE3___,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
