// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack_sp(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
    HRML(KC_A, KC_S, KC_D, KC_F), KC_G, KC_H, HRMR(KC_J, KC_K, KC_L, KC_SCLN),
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,
    UPDIR, XXXXXXX, KC_ESC, LWRSPC, RSEBSP, C(S(KC_V)), XXXXXXX, PNP
  ),
  [_LOWER] = LAYOUT_jack_sp(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
    HRML(KC_EXLM, KC_AT, KC_HASH, KC_DLR), KC_PERC, KC_CIRC, HRMR(KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN),
    KC_TAB, KC_CAPS, REMOVE, KC_GRV, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SLSH,
    _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_jack_sp(
    XRGB_TOG, XRGB_NXT,  XRGB_HUI, XRGB_SAI, XRGB_VAI, UC_NOMODE, UC_SCRIPT, UC_BLOCKS, UC_REGIONAL, QK_MAKE,
    M_JIGGLE, XRGB_PRV, XRGB_HUD, XRGB_SAD, XRGB_VAD, UC_WIDE, UC_AUSSIE, UC_ZALGO, UC_SUPER, QK_BOOT,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
    _______, _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
