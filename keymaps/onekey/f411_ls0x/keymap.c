// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "qp.h"
#include "qp_surface.h"
#include "3270_11.qff.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)};

static painter_font_handle_t font;
static painter_device_t display;
static uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(
    LS0XX_WIDTH, LS0XX_HEIGHT, 1)] = {0};

void keyboard_post_init_user(void) {
  display =
      qp_ls0xx_device_t_make_spi_device(LS0XX_WIDTH, LS0XX_HEIGHT, LS0XX_CS_PIN,
                                        LS0XX_SPI_DIVISOR, 0, framebuffer);
  font = qp_load_font_mem(font_3270_11);
  qp_init(display, QP_ROTATION_0);
  qp_drawtext(display, 0, 0, font, "foo bar baz");
}
