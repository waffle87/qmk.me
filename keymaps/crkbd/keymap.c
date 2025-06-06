// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack_3x6(
    XXXXXXX, ___BASE1___, XXXXXXX,
    XXXXXXX, ___BASE2___, XXXXXXX,
    XXXXXXX, ___BASE3___, XXXXXXX,
             ___BASE4___
  ),
  [_LOWER] = LAYOUT_jack_3x6(
    _______, ___LOWER1___, _______,
    _______, ___LOWER2___, _______,
    _______, ___LOWER3___, _______,
             ___LOWER4___
  ),
  [_RAISE] = LAYOUT_jack_3x6(
    _______, ___RAISE1___, _______,
    _______, ___RAISE2___, _______,
    _______, ___RAISE3___, _______,
             ___RAISE4___
  )
};
// clang-format on

void housekeeping_task_keymap(void) {
  if (last_input_activity_elapsed() > 300000) {
    const pin_t row_pins[] = MATRIX_ROW_PINS, col_pins[] = MATRIX_COL_PINS;
    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); ++i) {
      gpio_set_pin_output(col_pins[i]);
      gpio_write_pin_low(col_pins[i]);
    }
    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); ++i) {
      gpio_set_pin_input_high(row_pins[i]);
      palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
    }
    __WFI();
    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); ++i) {
      palDisableLineEvent(row_pins[i]);
      gpio_write_pin_high(row_pins[i]);
      gpio_set_pin_input_high(row_pins[i]);
    }
    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); ++i) {
      gpio_write_pin_high(col_pins[i]);
      gpio_set_pin_input_high(col_pins[i]);
    }
  }
}

#ifdef AUDIO_ENABLE
void keyboard_pre_init_user(void) { // thank you to @sigprof for this
  palSetLineMode(A5, PAL_MODE_INPUT_ANALOG);
  palSetLineMode(B1, PAL_MODE_INPUT_ANALOG);
}

void keyboard_post_init_keymap(void) {
  // enable OPAMP1 as A5 → B1 follower
  OPAMP3->CSR = OPAMP3_CSR_VMSEL_1 | OPAMP3_CSR_VMSEL_0 | OPAMP3_CSR_VPSEL_0 |
                OPAMP3_CSR_OPAMP3EN;
}
#endif // audio

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return is_keyboard_master() ? OLED_ROTATION_180 : OLED_ROTATION_270;
}

bool oled_task_keymap(void) {
  if (is_keyboard_master())
    layer_anim();
  else {
    layer_status();
    oled_set_cursor(0, 3);
    felix_dog();
    oled_set_cursor(0, 7);
    render_wpm();
    render_keylog();
    render_mod_status();
  }
  return false;
}
#endif // oled

#ifdef RGB_MATRIX_ENABLE
void matrix_init_user(void) {
  g_led_config = (led_config_t){
      {{15, 16, 17, 18, 19, 20},
       {14, 13, 12, 11, 10, 9},
       {3, 4, 5, 6, 7, 8},
       {NO_LED, NO_LED, NO_LED, 2, 1, 0},
       {47, 46, 45, 44, 43, 42},
       {36, 37, 38, 39, 40, 41},
       {35, 34, 33, 32, 31, 30},
       {NO_LED, NO_LED, NO_LED, 27, 28, 29}},
      {
          {95, 63},  {85, 39},  {85, 21},  {85, 4},   {68, 2},   {68, 19},
          {68, 37},  {80, 58},  {60, 55},  {50, 35},  {50, 13},  {50, 0},
          {33, 3},   {33, 20},  {33, 37},  {16, 42},  {16, 24},  {16, 7},
          {0, 7},    {0, 24},   {0, 41},   {85, 16},  {50, 13},  {16, 20},
          {16, 38},  {50, 48},  {85, 52},  {129, 63}, {139, 39}, {139, 21},
          {139, 4},  {156, 2},  {156, 19}, {156, 37}, {144, 58}, {164, 55},
          {174, 35}, {174, 13}, {174, 0},  {191, 3},  {191, 20}, {191, 37},
          {208, 42}, {208, 24}, {208, 7},  {224, 7},  {224, 24}, {224, 41},
          {139, 16}, {174, 13}, {208, 20}, {208, 38}, {174, 48}, {139, 52},
      },
      {1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4,
       4, 4, 4, 2, 2, 2, 2, 2, 2, 1, 1, 1, 4, 4, 4, 4, 4, 1,
       1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2, 2, 2, 2, 2, 2}};
}
#endif // rgb matrix
