// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

#if defined(SPLIT_KEYBOARD) && defined(OLED_ENABLE)
#include "transactions.h"
extern char keylog_str[KEYLOG_LEN + 1];
void keylogger_sync(uint8_t initiator2target_buffer_size,
                    const void *initiator2target_buffer,
                    uint8_t target2initiator_buffer_size,
                    void *target2initiator_buffer) {
  if (initiator2target_buffer_size == 5)
    memcpy(&keylog_str, initiator2target_buffer, initiator2target_buffer_size);
}
#endif

__attribute__((weak)) void housekeeping_task_keymap(void) {}
void housekeeping_task_user(void) {
#if defined(SPLIT_KEYBOARD) && defined(OLED_ENABLE)
  if (is_keyboard_master()) {
    static uint32_t last_sync;
    bool needs_sync = false;
    static char tmp_keylog[5] = {0};
    if (memcmp(&keylog_str, &tmp_keylog, sizeof(tmp_keylog))) {
      needs_sync = true;
      memcpy(&tmp_keylog, &keylog_str, sizeof(tmp_keylog));
    }
    if (timer_elapsed32(last_sync) > 250)
      needs_sync = true;
    if (needs_sync)
      if (transaction_rpc_send(RPC_ID_USER_KEYLOG_STR, sizeof(tmp_keylog),
                               &keylog_str))
        last_sync = timer_read32();
  }
#endif
  housekeeping_task_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}
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
#ifdef AUTOCORRECT_ENABLE
  if (!autocorrect_is_enabled())
    autocorrect_enable();
#endif
  keyboard_post_init_keymap();
}

#ifdef OS_DETECTION_ENABLE
typedef struct {
  bool swap_ctl_gui;
  uint8_t unicode_input_mode;
} os_detection_config;

bool process_detected_host_os_user(os_variant_t detected_os) {
  os_detection_config os_config = {.swap_ctl_gui = true,
                                   .unicode_input_mode = UNICODE_MODE_MACOS};
  if (detected_os == OS_LINUX)
    os_config = (os_detection_config){.swap_ctl_gui = false,
                                      .unicode_input_mode = UNICODE_MODE_LINUX};
  keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui =
      os_config.swap_ctl_gui;
  eeconfig_update_keymap(&keymap_config);
#ifdef UNICODE_COMMON_ENABLE
  set_unicode_input_mode(os_config.unicode_input_mode);
#endif
  return true;
}
#endif

#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) { return keycode; }
uint8_t mod_config(uint8_t mod) { return mod; }
#endif

#ifdef RP2040_MATH_IN_ROM
typedef void (*init_fn)(void);
extern init_fn __preinit_array_base__;
extern init_fn __preinit_array_end__;
#endif

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}
void keyboard_pre_init_user(void) {
#ifdef RP2040_MATH_IN_ROM
  for (init_fn *func = &__preinit_array_base__; func < &__preinit_array_end__;
       func++)
    (*func)();
#endif
  keyboard_pre_init_keymap();
}
