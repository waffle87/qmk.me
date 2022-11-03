// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#include "combos.h"

#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
  user_state.cpu_temp = data[0];
  user_state.hour = data[1];
  user_state.min = data[2];
}
#endif

#if defined(SPLIT_KEYBOARD) && defined(OLED_ENABLE)
#include "transactions.h"
extern char keylog_str[5];
void keylogger_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
  if (initiator2target_buffer_size == 5)
    memcpy(&keylog_str, initiator2target_buffer, initiator2target_buffer_size);
}

__attribute__ ((weak)) void housekeeping_task_user(void) {
  if (is_keyboard_master()) {
    static uint32_t last_sync;
    bool needs_sync = false;
    static char tmp_keylog[5] = {0};
    if (memcmp(&keylog_str, &tmp_keylog, 5)) {
      needs_sync = true;
      memcpy(&tmp_keylog, &keylog_str, 5);
    }
    if (timer_elapsed32(last_sync) > 250)
      needs_sync = true;
    if (needs_sync) {
      if (transaction_rpc_send(RPC_ID_USER_KEYLOG_STR, 5, &keylog_str))
        last_sync = timer_read32();
    }
  }
}
#endif

void matrix_io_delay(void) {
  __asm__ volatile("nop\nnop\nnop\n");
}

__attribute__ ((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__ ((weak)) void keyboard_post_init_user(void) {
#if defined(SPLIT_KEYBOARD) && defined(OLED_ENABLE)
  transaction_register_rpc(RPC_ID_USER_KEYLOG_STR, keylogger_sync);
#endif
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
#ifdef CONSOLE_ENABLE
  debug_keyboard = true;
  debug_enable = true;
  debug_matrix = true;
  debug_mouse = true;
#endif
#ifdef AUTOCORRECT_ENABLE
  if (!autocorrect_is_enabled())
    autocorrect_enable();
#endif
}

#if !defined (ENCODER_MAP_ENABLE) && defined (ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch (get_highest_layer(layer_state)) {
      case _LOWER:
#if defined (RGBLIGHT_ENABLE) || defined (RGB_MATRIX_ENABLE)
        clockwise ? rgblight_increase_hue() : rgblight_decrease_hue();
#endif
        break;
      default:
        clockwise ? tap_code_delay(KC_VOLU, 20) : tap_code_delay(KC_VOLD, 20);
    }
  } else if (index == 1) {
    switch (get_highest_layer(layer_state)) {
      case _LOWER:
#if defined (RGBLIGHT_ENABLE) || defined (RGB_MATRIX_ENABLE)
        clockwise ? rgblight_increase_sat() : rgblight_decrease_sat();
#endif
      break;
      default:
        clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
    }
  }
  return false;
}
#endif

#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
uint8_t red = 255, green = 0, blue = 0;

void trackball_hue(void) {
  if (red != 255 && green != 255 && blue != 255) red = 255;
  if (red == 255 && green < 255 && blue == 0) green += 15;
  else if (green == 255 && blue == 0 && red > 0) red -= 15;
  else if (red == 0 && blue < 255 && green == 255 ) blue += 15;
  else if (blue == 255 && green > 0 && red == 0) green -= 15;
  else if (green == 0 && blue == 255 && red < 255) red += 15;
  else if (green == 0 && blue > 0 && red == 255) blue -= 15;
  pimoroni_trackball_set_rgbw(red, green, blue, 0);
}
#endif

#ifdef POINTING_DEVICE_ENABLE
static bool scrolling = false;
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LOWER:
      scrolling = true;
#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
      pimoroni_trackball_set_cpi(0.1);
#else
      pointing_device_set_cpi(64);
#endif
      break;
    default:
      if (scrolling) {
        scrolling = false;
#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
        pimoroni_trackball_set_cpi(1);
#else
        pointing_device_set_cpi(1024);
#endif
      }
      break;
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
