// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#define ___NONE___ _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle_60_ts(
    KC_DEL,  ___NONE___,
    _______, ___BASE1___, _______, _______, PNP,
    LINKS,   ___BASE2___, KC_BSPC, _______,
    _______, ___BASE3___, _______,
    KC_VOLD, _______,     KC_ESC,  LWRSPC, PSTRSE, _______, KC_VOLU
  ),
  [_LOWER] = LAYOUT_waffle_60_ts(
    _______, ___NONE___,
    _______, ___LOWER1___, _______, _______, _______,
    _______, ___LOWER2___, _______, _______,
    _______, ___LOWER3___, _______,
    _______, _______,      _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_waffle_60_ts(
    _______, ___NONE___,
    _______, ___RAISE1___, _______, _______, _______,
    _______, ___RAISE2___, _______, _______,
    _______, ___RAISE3___, _______,
    _______, _______,      _______, _______, _______, _______, _______
  )
};
