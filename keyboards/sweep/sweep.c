// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include <quantum.h>

#ifdef QUANTUM_PAINTER_ENABLE
#include "lib/jetbrainsmono11.qff.h"
#include <qp.h>
#include <qp_surface.h>
static painter_device_t display;
static painter_font_handle_t font;
static uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(
    LS0XX_DISPLAY_WIDTH, LS0XX_DISPLAY_HEIGHT, 1)] = {0};

void keyboard_post_init_kb(void) {
  display = qp_ls0xx_device_t_make_spi_device(
      LS0XX_DISPLAY_WIDTH, LS0XX_DISPLAY_HEIGHT, LS0XX_CS_PIN, LCD_SPI_DIVISOR,
      0, framebuffer);
  qp_init(display, QP_ROTATION_0);
  font = qp_load_font_mem(font);
  if (font) {
    static const char *data = "foo bar baz";
    int16_t width = qp_textwidth(font, data);
    qp_drawtext(display, LS0XX_DISPLAY_WIDTH - width - 1,
                LS0XX_DISPLAY_HEIGHT - font->line_height - 1, font, data);
  }
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

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) { return rotation; }

bool oled_task_kb(void) {
  if (!oled_task_user())
    return false;
  oled_write(PSTR("foo bar baz"), false);
  return true;
}
#endif // OLED_ENABLE
