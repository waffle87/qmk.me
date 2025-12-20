// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
#undef LAYOUT
#define LAYOUT(                                             \
k0G, k0F, k0E, k0D, k0C,           k4C, k4D, k4E, k4F, k4G, \
k1G, k1F, k1E, k1D, k1C,           k5C, k5D, k5E, k5F, k5G, \
k2G, k2F, k2E, k2D, k2C,           k6C, k6D, k6E, k6F, k6G, \
          k3F, k3D, k3C, k3B, k7B, k7C, k7D, k7F            \
) {                                                         \
  {XXX, k0C, k0D, k0E, k0F, k0G,},                          \
  {XXX, k1C, k1D, k1E, k1F, k1G,},                          \
  {XXX, k2C, k2D, k2E, k2F, k2G,},                          \
  {k3B, k3C, k3D, XXX, k3F, XXX,},                          \
  {XXX, k4C, k4D, k4E, k4F, k4G,},                          \
  {XXX, k5C, k5D, k5E, k5F, k5G,},                          \
  {XXX, k6C, k6D, k6E, k6F, k6G,},                          \
  {k7B, k7C, k7D, XXX, k7F, XXX,}                           \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack(
    ___LAYER00___,
    ___LAYER01___,
    ___LAYER02___,
    XXXXXXX, XXXXXX, ___LAYER03___, XXXXXXX, XXXXXXX
  ),
  [LAYER1] = LAYOUT_jack(
    ___LAYER10___,
    ___LAYER11___,
    ___LAYER12___,
    _______, _______, ___LAYER13___, _______, _______
  ),
  [LAYER2] = LAYOUT_jack(
    ___LAYER20___,
    ___LAYER21___,
    ___LAYER22___,
    _______, _______, ___LAYER23___, _______, _______
  ),
  [LAYER3] = LAYOUT_jack(
    ___LAYER30___,
    ___LAYER31___,
    ___LAYER32___,
    _______, _______, ___LAYER33___, _______, _______
  )
};
// clang-format on

#ifdef OLED_ENABLE
uint32_t oled_timer = 0;

void oled_timer_reset(void) { oled_timer = timer_read32(); }

void oled_wpm_graph(void) {
  static uint8_t height = OLED_DISPLAY_HEIGHT - 1, vert_count = 0,
                 max_wpm = 160;
  extern uint8_t oled_buffer[OLED_MATRIX_SIZE];
  extern OLED_BLOCK_TYPE oled_dirty;
  static uint16_t graph_timer = 0;
  if (timer_elapsed(graph_timer) > 100) {
    height = 63 - ((get_current_wpm() / (float)max_wpm) * 63);
    for (uint8_t i = 0; i <= 1; i++)
      oled_write_pixel(3, height + i, true);
    if (vert_count == 3) {
      vert_count = 0;
      while (height <= 63) {
        oled_write_pixel(3, height, true);
        height++;
      }
    } else {
      for (uint8_t i = 63; i > height; i--)
        if (!(i % 3))
          oled_write_pixel(3, i, true);
      vert_count++;
    }
    for (uint16_t y = 0; y < 8; y++) {
      for (uint16_t x = 124; x > 0; x--) {
        uint16_t i = y * OLED_DISPLAY_WIDTH + x;
        oled_buffer[i] = oled_buffer[i - 1];
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (i / OLED_BLOCK_SIZE));
      }
    }
    graph_timer = timer_read();
  }
}

void oled_wpm(void) {
  oled_write(PSTR("WPM: "), false);
  oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    if (timer_elapsed32(oled_timer) > THREE_MIN) {
      oled_off();
      return false;
    } else
      oled_on();
  }
  if (is_keyboard_left()) {
    oled_wpm_graph();
    oled_wpm();
  }
  return false;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed)
    oled_timer_reset();
  return true;
}
#endif

#ifdef POINTING_DEVICE_ENABLE
static bool scrolling = false;
layer_state_t layer_state_set_keymap(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case LAYER1:
    scrolling = true;
    pointing_device_set_cpi(64);
    break;
  default:
    if (scrolling) {
      scrolling = false;
      pointing_device_set_cpi(1024);
    }
  }
  return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (scrolling) {
    mouse_report.h = mouse_report.x;
    mouse_report.v = -mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;
  }
  return mouse_report;
}
#endif
