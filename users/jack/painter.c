// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"
#include "painter.h"

painter_font_handle_t qp_font;
uint32_t display_timer = 0;

void keyboard_post_init_qp(void) {
  qp_font = qp_load_font_mem(font_JetBrainsMono_11);
}

void display_timer_reset(void) { display_timer = timer_read32(); }

void housekeeping_task_qp(void) {
  qp_power(display, timer_elapsed32(display_timer) > 180000);
}
