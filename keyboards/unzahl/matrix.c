// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "matrix.h"
#include <string.h>
#include "spi_master.h"
#include "debug.h"

static int matrix_size = MATRIX_ROWS * sizeof(matrix_row_t);
matrix_row_t old_matrix[MATRIX_ROWS];
pin_t matrix_row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static bool shift_reg_spi_locked = false;

void sem_lock(bool value) { shift_reg_spi_locked = value; }

bool sem_locked(void) { return shift_reg_spi_locked; }

void shift_reg_spi_stop(void) {
  spi_stop();
  sem_lock(false);
}

bool shift_reg_spi_start(void) {
  if (!spi_start(SHIFT_REG_CS_PIN, false, 0, SHIFT_REG_SPI_DIVISOR)) {
    dprintf("74HC595: Failed to start SPI\n");
    shift_reg_spi_stop();
    return false;
  }
  sem_lock(true);
  return true;
}

void shift_reg_spi_send_byte(uint8_t data) {
  shift_reg_spi_start();
  gpio_write_pin_low(SHIFT_REG_CS_PIN);
  matrix_io_delay();
  spi_write(data);
  matrix_io_delay();
  gpio_write_pin_high(SHIFT_REG_CS_PIN);
  shift_reg_spi_stop();
}

void clear_columns(void) {
  uint8_t value = 0b0000000;
  shift_reg_spi_send_byte(value);
}

void set_column(int shift) {
  uint8_t shift_byte = ((uint8_t)1 << shift);
  dprintf("74HC595: byte %d sent\n", shift_byte);
  shift_reg_spi_send_byte(shift_byte);
}

void matrix_init_custom(void) {
  spi_init();
  for (uint8_t i = 0; i < MATRIX_ROWS; i++)
    gpio_set_pin_input_low(matrix_row_pins[i]);
  gpio_write_pin_high(SHIFT_REG_CS_PIN);
  gpio_set_pin_output(SHIFT_REG_CS_PIN);
  clear_columns();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  if (sem_locked())
    return false;
  bool matrix_changed = false;
  memset(current_matrix, 0, matrix_size);
  for (uint8_t i = 0; i < MATRIX_COLS; i++) {
    dprintf("74HC595: Column %d\n", i);
    set_column(i);
    matrix_io_delay();
    for (uint8_t j = 0; j < MATRIX_ROWS; j++)
      current_matrix[j] |= ((gpio_read_pin(matrix_row_pins[j]) ? 1 : 0) << i);
  }
  matrix_changed = memcmp(current_matrix, old_matrix, matrix_size) != 0;
  memcpy(old_matrix, current_matrix, matrix_size);
  if (matrix_changed)
    matrix_print();
  clear_columns();
  matrix_io_delay();
  return matrix_changed;
}
