// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack_all(
    ___LAYER00___, XXXXXXX,
    ___LAYER01___,
    ___LAYER02___,
    UPDIR, KC_ESC, LWRSPC, XXXXXXX, RSEBSP, C(S(KC_V)), PNP
  ),
  [LAYER1] = LAYOUT_jack_all(
    ___LAYER10___, _______,
    ___LAYER11___,
    ___LAYER12___,
    _______, _______, _______, _______, SWTCH, _______, _______
  ),
  [LAYER3] = LAYOUT_jack_all(
    ___LAYER30___, _______,
    ___LAYER31___,
    ___LAYER32___,
    _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
