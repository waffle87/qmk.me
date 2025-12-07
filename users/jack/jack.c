// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void keyboard_post_init_user(void) {
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

#ifdef OLED_ENABLE
uint32_t oled_timer = 0;

void oled_timer_reset(void) { oled_timer = timer_read32(); }

__attribute__((weak)) bool oled_task_keymap(void) { return true; }
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    if (timer_elapsed32(oled_timer) > THREE_MIN) {
      oled_off();
      return false;
    } else
      oled_on();
  }
  oled_task_keymap();
  return false;
}
#endif
