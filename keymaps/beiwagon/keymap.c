// Copyright 2025 jack_all@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    G(KC_F),  G(KC_T),  G(KC_R),
    KC_VOLD,  PNP,      KC_VOLU,
    REMOVE,   XRGB_HUI, XRGB_NXT,
    XRGB_TOG, XRGB_HUD, TG(_LOWER)
  ),
  [_LOWER] = LAYOUT_jack(
    QK_MAKE, _______, _______,
    QK_BOOT, _______, _______,
    EE_CLR,  _______, _______,
    _______, _______, _______
  )
};
// clang-format on
