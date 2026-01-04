// Copyright 2026 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack_all(
    ___LAYER00___, XXXXXXX,
    ___LAYER01___,
    ___LAYER02___,
    XXXXXXX, KC_ESC, XXXXXXX, SPC_L1, XXXXXXX, BSPC_L2, XXXXXXX, QK_REP, XXXXXXX
  ),
  [LAYER1] = LAYOUT_jack_all(
    ___LAYER10___, _______,
    ___LAYER11___,
    ___LAYER12___,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [LAYER2] = LAYOUT_jack_all(
    ___LAYER20___, _______,
    ___LAYER21___,
    ___LAYER22___,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [LAYER3] = LAYOUT_jack_all(
    ___LAYER30___, _______,
    ___LAYER31___,
    ___LAYER32___,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
