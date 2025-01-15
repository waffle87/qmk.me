// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"
#define XX NO_LED

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    ___BASE1___,
    ___BASE2___,
    ___BASE3___,
    ESCLWR, KC_SPC, KC_BSPC, PSTRSE
  ),
  [_LOWER] = LAYOUT_jack(
    ___LOWER1___,
    ___LOWER2___,
    ___LOWER3___,
    _______, _______, _______, PNP
  ),
  [_RAISE] = LAYOUT_jack(
    ___RAISE1___,
    ___RAISE2___,
    ___RAISE3___,
    UPDIR, _______, _______, _______
  )
};

led_config_t g_led_config = {{
  {4,  3,  2,  1,  0 },
  {5,  6,  7,  8,  9 },
  {14, 13, 12, 11, 10},
  {XX, XX, XX, 15, 16},
  {17, 18, 19, 20, 21},
  {26, 25, 24, 23, 22},
  {27, 28, 29, 30, 31},
  {33, 32, XX, XX, XX}
}, {
  {72,7}, {54,4}, {36,0}, {18,4}, {0,13},
  {0,27}, {18,18},{36,14},{54,18},{72,21},
  {72,35},{54,32},{36,28},{18,32},{0,41},
                          {67,45},{90,62},
  {126,13},{144,4}, {162,0}, {180,4}, {198,7},
  {198,21},{180,18},{162,14},{144,18},{126,27},
  {126,41},{144,32},{162,28},{180,32},{198,35},
  {117,62},{135,45}
}, {
  4,4,4,4,4,
  4,4,4,4,4,
  4,4,4,4,4,
        4,4,
  4,4,4,4,4,
  4,4,4,4,4,
  4,4,4,4,4,
  4,4
}};
// clang-format on
