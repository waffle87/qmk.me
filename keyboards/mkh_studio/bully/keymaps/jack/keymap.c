// Copyright 2026 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack_sp(
    XXXXXXX, ___LAYER00___, KC_BSPC, KC_BSPC,
    XXXXXXX, ___LAYER01___, XXXXXXX,
    XXXXXXX, ___LAYER02___, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_ESC, SPC_L1, BSPC_L2, QK_REP, XXXXXXX, XXXXXXX
  ),
  [LAYER1] = LAYOUT_jack_sp(
    _______, ___LAYER10___, _______, _______,
    _______, ___LAYER11___, _______,
    _______, ___LAYER12___, _______,
    _______, _______, ___LAYER13___, _______, _______
  ),
  [LAYER2] = LAYOUT_jack_sp(
    _______, ___LAYER20___, _______, _______,
    _______, ___LAYER21___, _______,
    _______, ___LAYER22___, _______,
    _______, _______, ___LAYER23___, _______, _______
  ),
  [LAYER3] = LAYOUT_jack_sp(
    _______, ___LAYER30___, _______, _______,
    _______, ___LAYER31___, _______,
    _______, ___LAYER32___, _______,
    _______, _______, ___LAYER33___, _______, _______
  )
};
// clang-format on
