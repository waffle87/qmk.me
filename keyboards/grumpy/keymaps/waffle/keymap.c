// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
          KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,
    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
  )
};
