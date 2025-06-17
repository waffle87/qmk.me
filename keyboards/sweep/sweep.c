// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef QUANTUM_PAINTER_ENABLE
#include "qp.h"

static painter_device_t display;

void keyboard_post_init_kb(void) {
  display = qp_st7789_make_spi_device(LCD_DISPLAY_WIDTH, LCD_DISPLAY_HEIGHT,
                                      LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN,
                                      LCD_SPI_DIVISOR, 0);
  qp_init(display, QP_ROTATION_0);
  keyboard_post_init_user();
}

void suspend_power_down_kb(void) {
  qp_power(display, false);
  suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
  qp_power(display, true);
  suspend_wakeup_init_user();
}
#endif // QUANTUM_PAINTER_ENABLE
