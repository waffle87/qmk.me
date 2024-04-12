// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_ortho_1x1(KC_A)
};

void c1_main(void) {
  chSysWaitSystemState(ch_sys_running);
  chInstanceObjectInit(&ch1, &ch_core1_cfg);
  chSysUnlock();
  while (true) {
    chThdSleepMilliseconds(50);
    uprintf("core 1 up\n");
  }
}
