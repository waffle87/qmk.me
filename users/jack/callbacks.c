// Copyright 2026 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
__attribute__((weak)) void keyboard_post_init_keymap(void) {}
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
// clang-format on
