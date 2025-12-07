// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack(
    _______, ___LAYER00___, _______,
    _______, ___LAYER01___,
    _______, ___LAYER02___,
    UPDIR, KC_ESC, LWRSPC, RSEBSP, C(S(KC_V)), PNP
  ),
  [LAYER1] = LAYOUT_jack(
    _______, ___LAYER10___, _______,
    _______, ___LAYER11___,
    _______, ___LAYER12___,
    _______, _______, _______, _______, _______, _______
  ),
  [LAYER3] = LAYOUT_jack(
    _______, ___LAYER30___, _______,
    _______, ___LAYER31___,
    _______, ___LAYER32___,
    _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
