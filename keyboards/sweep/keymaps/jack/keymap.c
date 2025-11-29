// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    ___BASE1___,
    ___BASE2___,
    ___BASE3___,
    ___BASE4___
  ),
  [_LOWER] = LAYOUT_jack(
    ___LOWER1___,
    ___LOWER2___,
    ___LOWER3___,
    ___LOWER4___
  ),
  [_RAISE] = LAYOUT_jack(
    ___RAISE1___,
    ___RAISE2___,
    ___RAISE3___,
    ___RAISE4___
  )
};
// clang-format on

#ifdef QUANTUM_PAINTER_ENABLE
#include "analog.h"

static painter_device_t display;

void keyboard_post_init_keymap() {
  display = qp_st7789_make_spi_device(LCD_DISPLAY_WIDTH, LCD_DISPLAY_HEIGHT,
                                      LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN,
                                      LCD_SPI_DIVISOR, 0);
  qp_init(display, QP_ROTATION_0);
}

void housekeeping_task_keymap(void) {
  static uint32_t last_read = 0;
  static int16_t current_reads[NUM_ADC_READS] = {0};
  static int16_t voltage_reads[NUM_ADC_READS] = {0};
  static uint8_t offset = 0;
  if (timer_elapsed32(last_read) >= 1) {
    int16_t current = analogReadPin(ADC_CURRENT_PIN);
    int16_t voltage = analogReadPin(ADC_VOLTAGE_PIN);
    int16_t current_ma =
        (int16_t)(((3300 * (int32_t)current) / ADC_SATURATION));
    int16_t voltage_mv =
        (int16_t)((2 * (3300 * (int32_t)voltage)) / ADC_SATURATION);
    if (!last_read)
      for (uint8_t i = 0; i < NUM_ADC_READS; ++i) {
        current_reads[i] = current_ma;
        voltage_reads[i] = voltage_mv;
      }
    current_reads[offset] = current_ma;
    voltage_reads[offset] = voltage_mv;
    offset = (offset + 1) % NUM_ADC_READS;
    static uint16_t counter = 0;
    counter = (counter + 1) % 2500;
    if (!counter)
      dprintf("Current: %dmA\tVoltage: %dmV\n", (int)current_ma,
              (int)voltage_mv);
    last_read = timer_read32();
  }
  static uint32_t last_draw = 0;
  if (timer_elapsed32(last_draw) >= 250) {
    int32_t total_current_ma = 0;
    int32_t total_voltage_mv = 0;
    for (uint8_t i = 0; i < NUM_ADC_READS; ++i) {
      total_current_ma += current_reads[i];
      total_voltage_mv += voltage_reads[i];
    }
    int16_t avg_current_ma = (int16_t)(total_current_ma / NUM_ADC_READS);
    int16_t avg_voltage_mv = (int16_t)(total_voltage_mv / NUM_ADC_READS);
    char data[32] = {};
    sprintf(data, "Current: %dmA", avg_current_ma);
    qp_drawtext(display, 0, LCD_DISPLAY_WIDTH - qp_font->line_height * 2,
                qp_font, data);
    sprintf(data, "Voltage: %dmV", avg_voltage_mv);
    qp_drawtext(display, 0, LCD_DISPLAY_WIDTH - qp_font->line_height, qp_font,
                data);
    qp_flush(display);
    last_draw = timer_read32();
  }
}

void suspend_power_down_user(void) { qp_power(display, false); }

void suspend_wakeup_init_user(void) { qp_power(display, true); }
#endif
