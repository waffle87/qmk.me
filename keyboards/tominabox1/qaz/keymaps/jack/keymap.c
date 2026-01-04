// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack_sp(
    ___LAYER00___,
    ___LAYER01___,
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,
    _______, _______, KC_ESC, SPC_L1, BSPC_L2, QK_REP, _______, _______
  ),
  [LAYER1] = LAYOUT_jack_sp(
    ___LAYER10___,
    ___LAYER11___,
    KC_VOLU, TD(PLY_NXT_PRV), _______, _______, _______, _______, _______, _______, KC_SLSH,
    _______, _______, ___LAYER13___, _______, _______
  ),
  [LAYER2] = LAYOUT_jack_sp(
    ___LAYER20___,
    ___LAYER21___,
    KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, KC_AT, KC_COLN, _______, _______,
    _______, _______, ___LAYER23___, _______, _______
  ),
  [LAYER3] = LAYOUT_jack_sp(
    ___LAYER30___,
    ___LAYER31___,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
    _______, _______, ___LAYER33___, _______, _______
  )
};
// clang-format on
