// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "qp.h"
#include "qp_surface.h"
#include "ls0xx.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)};

static painter_device_t display;
static uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(
    LS0XX_WIDTH, LS0XX_HEIGHT, 1)] = {0};

void keyboard_post_init_user(void) {
  display =
      qp_ls0xx_device_t_make_spi_device(LS0XX_WIDTH, LS0XX_HEIGHT, LS0XX_CS_PIN,
                                        LS0XX_SPI_DIVISOR, 0, framebuffer);
  qp_init(display, QP_ROTATION_0);
}

void housekeeping_task_user(void) {
  static uint32_t last_draw = 0;
  if (timer_elapsed32(last_draw) > 33) {
    last_draw = timer_read32();
    for (int i = 0; i < LS0XX_HEIGHT - 1; i += 8)
      qp_rect(display, 0, i, 7, i + 7, 255, 255, 255, true);
    qp_flush(display);
  }
}
