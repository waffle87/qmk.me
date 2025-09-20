// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"
#include "painter.h"

painter_font_handle_t qp_font;

void keyboard_post_init_qp(void) {
  qp_font = qp_load_font_mem(font_JetBrainsMono_11);
}
