// Copyright 2026 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)};

void c1_main(void) {
  chSysWaitSystemState(ch_sys_running);
  chInstanceObjectInit(&ch1, &ch_core1_cfg);
  chSysUnlock();
  while (true) {
    uprintf("core 1 active\n");
    wait_ms(100);
  }
}
