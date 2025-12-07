// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)};

typedef void (*init_fn)(void);
extern init_fn __preinit_array_base__;
extern init_fn __preinit_array_end__;

void keyboard_pre_init_user(void) {
  for (init_fn *func = &__preinit_array_base__; func < &__preinit_array_end__;
       func++)
    (*func)();
}
