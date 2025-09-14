// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    ___BASE1___, 
    ___BASE2___,
    ___BASE3___, 
    _______, ___BASE4___, _______
  ),
  [_LOWER] = LAYOUT_jack(
    ___LOWER1___,
    ___LOWER2___,
    ___LOWER3___,
    _______, ___LOWER4___, _______
  ),
  [_RAISE] = LAYOUT_jack(
    ___RAISE1___,
    ___RAISE2___,
    ___RAISE3___,
    _______, ___RAISE4___, _______
  )
};
// clang-format on
