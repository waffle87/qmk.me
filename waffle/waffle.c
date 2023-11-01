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

void housekeeping_task_user(void) {
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
  housekeeping_task_keymap();
}
#endif

void keyboard_post_init_user(void) {
#if defined(SPLIT_KEYBOARD) && defined(OLED_ENABLE)
  transaction_register_rpc(RPC_ID_USER_KEYLOG_STR, keylogger_sync);
#endif
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_enable_noeeprom();
  rgb_matrix_sethsv_noeeprom(HSV_CYAN);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
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
  keyboard_post_init_keymap();
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE]  = {{ KC_VOLU, KC_VOLD }, { KC_MNXT, KC_MPRV }},
  [_LOWER] = {{ RGB_SAI, RGB_SAD }, { RGB_HUI, RGB_HUD }},
  [_RAISE] = {{ C(KC_LEFT), C(KC_RGHT) }, { C(S(KC_TAB)), C(KC_TAB) }}
};
#endif

#ifdef POINTING_DEVICE_DRIVER_pimoroni_trackball
uint8_t red = 255, green = 0, blue = 0;

void trackball_hue(void) {
  if (red != 255 && green != 255 && blue != 255) red    = 255;
  if (red == 255 && green < 255 && !blue)        green += 15;
  else if (green == 255 && !blue && red)         red   -= 15;
  else if (!red && blue < 255 && green == 255)   blue  += 15;
  else if (blue == 255 && green && !red)         green -= 15;
  else if (!green && blue == 255 && red < 255)   red   += 15;
  else if (!green && blue && red == 255)         blue  -= 15;
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
