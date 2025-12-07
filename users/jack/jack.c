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

__attribute__((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
  return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, LAYER1, LAYER2, LAYER3);
  state = layer_state_set_keymap(state);
  return state;
}

#define INTERCEPT_MOD_TAP(mod, keycode)                                        \
  case mod(keycode):                                                           \
    if (record->tap.count && record->event.pressed) {                          \
      tap_code16(keycode);                                                     \
      return false;                                                            \
    }                                                                          \
    break;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case ESC_L1:
  case REP_L2:
  case SPC_L1:
  case BSPC_L2:
    return TAPPING_TERM - 40;
  case TD(EM_DASH_MINS):
  case TD(PLY_NXT_PRV):
    return TAPPING_TERM + 60;
  default:
    return TAPPING_TERM;
  }
}

#ifdef TAP_DANCE_ENABLE
void em_dash_mins(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 3:
#ifdef UNICODE_COMMON_ENABLE
    register_unicode(0x2014);
#endif
    break;
  case 2:
    tap_code(KC_MINS), tap_code(KC_MINS);
    break;
  default:
    tap_code(KC_MINS);
  }
}

void ply_nxt_prv(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    tap_code(KC_MPLY);
    break;
  case 2:
    tap_code(KC_MNXT);
    break;
  case 3:
    tap_code(KC_MPRV);
    break;
  }
}
#endif
__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_keymap(keycode, record))
    return false;
  switch (keycode) {
  case UPDIR:
    if (record->event.pressed)
      SEND_STRING("../");
    break;
  case REMOVE:
    if (record->event.pressed) {
      SEND_STRING("```suggestion\n```");
      tap_code(KC_UP);
      tap_code(KC_UP);
      tap_code(KC_ENT);
      tap_code(KC_UP);
    }
    break;
  }
  return true;
}
