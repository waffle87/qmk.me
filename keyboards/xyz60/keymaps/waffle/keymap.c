// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "waffle.h"
#define ___NONE___                                                             \
  _______, _______, _______, _______, _______, _______, _______, _______,      \
      _______, _______, _______, _______, _______

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle_60_ts(
    _______, ___NONE___,
    _______, ___BASE1___, KC_BSPC, _______, PNP,
    _______, ___BASE2___, _______, _______,
    _______, ___BASE3___, _______,
    _______, _______,     KC_ESC,  LWRSPC, RSEPST, _______, _______
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
// clang-format on
