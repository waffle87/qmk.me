// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack(
    XXXXXXX, ___LAYER00___, KC_BSPC, KC_BSPC,
    REMOVE,  ___LAYER01___, PNP,
    XXXXXXX, ___LAYER02___, XXXXXXX,
    KC_VOLD, UPDIR, KC_ESC, XXXXXXX, LWRSPC, XXXXXXX, PSTRSE, XXXXXXX, KC_VOLU
  ),
  [LAYER1] = LAYOUT_jack(
    _______, ___LAYER10___, _______, _______,
    _______, ___LAYER11___, _______,
    _______, ___LAYER12___, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [LAYER3] = LAYOUT_jack(
    _______, ___LAYER30___, _______, _______,
    _______, ___LAYER31___, _______,
    _______, ___LAYER32___, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
