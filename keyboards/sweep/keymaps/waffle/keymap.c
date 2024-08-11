// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    ___BASE1___,
    ___BASE2___,
    ___BASE3___,
    ESCLWR, KC_SPC, KC_BSPC, PSTRSE
  ),
  [_LOWER] = LAYOUT_waffle(
    ___LOWER1___,
    ___LOWER2___,
    ___LOWER3___,
    KC_NO, KC_NO, NUKE, PNP
  ),
  [_RAISE] = LAYOUT_waffle(
    ___RAISE1___,
    ___RAISE2___,
    ___RAISE3___,
    UPDIR, RWORD, KC_NO, KC_NO
  )
};
// clang-format on
