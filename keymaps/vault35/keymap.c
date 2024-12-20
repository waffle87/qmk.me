// Copyright 2024 jack_all@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack_all(
    ___BASE1___, XXXXXXX,
    ___BASE2___,
    ___BASE3___,
    UPDIR, KC_ESC, LWRSPC, _______, RSEBSP, C(S(KC_V)), PNP
  ),
  [_LOWER] = LAYOUT_jack_all(
    ___LOWER1___, XXXXXXX,
    ___LOWER2___,
    ___LOWER3___,
    _______, _______, _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_jack_all(
    ___RAISE1___, XXXXXXX,
    ___RAISE2___,
    ___RAISE3___,
    _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
