// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

#define INTERCEPT_MOD_TAP(mod, keycode)                                        \
  case mod(keycode):                                                           \
    if (record->tap.count && record->event.pressed) {                          \
      tap_code16(keycode);                                                     \
      return false;                                                            \
    }                                                                          \
    break;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LWRSPC:
  case ESCLWR:
  case RSEBSP:
    return TAPPING_TERM - 40;
  case TD(EM_DASH_MINS):
  case TD(PLY_NXT_PRV):
  case TD(CBRACKET):
  case TD(SBRACKET):
    return TAPPING_TERM + 60;
  default:
    return TAPPING_TERM;
  }
}

#ifdef TAP_DANCE_ENABLE
void td_reset(tap_dance_state_t *state, void *user_data) {
  clear_keyboard();
  layer_clear();
}

void em_dash_mins(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 3:
#ifdef UNICODE_COMMON_ENABLE
    register_unicode(0x2014); // —
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

void raise_paste(tap_dance_state_t *state, void *user_data) {
  if (state->pressed && !state->interrupted)
    layer_on(_RAISE);
  else if (state->count == 1)
    tap_code16(C(S(KC_V)));
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef UNICODE_COMMON_ENABLE
  if (!process_record_unicode(keycode, record))
    return false;
#endif
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    oled_timer_reset();
    add_keylog(keycode, record);
  }
#endif
#ifdef MOUSE_JIGGLE_ENABLE
  if (record->event.pressed) {
    static deferred_token token = INVALID_DEFERRED_TOKEN;
    static report_mouse_t report = {0};
    if (token) {
      cancel_deferred_exec(token);
      token = INVALID_DEFERRED_TOKEN;
      report = (report_mouse_t){};
      host_mouse_send(&report);
    } else if (keycode == M_JIGGLE) {
      uint32_t jiggle_callback(uint32_t trigger_time, void *cb_arg) {
        static const int8_t deltas[32] = {
            0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
            0, 1,  2,  2,  3,  3,  4,  4,  4,  4,  3,  3,  2,  2,  1,  0};
        static uint8_t phase = 0;
        report.x = deltas[phase];
        report.y = deltas[(phase + 8) & 31];
        phase = (phase + 1) & 31;
        host_mouse_send(&report);
        return 16;
      }
      token = defer_exec(1, jiggle_callback, NULL);
    }
  }
#endif
  switch (keycode) {
  case UPDIR:
    if (record->event.pressed)
      tap_string(PSTR("../"));
    break;
  case REMOVE:
    if (record->event.pressed) {
      tap_string(PSTR("```suggestion\n```"));
      tap_code(KC_UP);
      tap_code(KC_UP);
      tap_code(KC_ENT);
      tap_code(KC_UP);
    }
    break;
  case OS_SWAP:
    if (record->event.pressed) {
      keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
      keymap_config.swap_rctl_rgui = !keymap_config.swap_rctl_rgui;
      eeconfig_update_keymap(&keymap_config);
      unicode_input_mode_step();
    }
    break;
    INTERCEPT_MOD_TAP(LALT_T, KC_EXLM)
    INTERCEPT_MOD_TAP(LGUI_T, KC_AT)
    INTERCEPT_MOD_TAP(LCTL_T, KC_HASH)
    INTERCEPT_MOD_TAP(LSFT_T, KC_DLR)
    INTERCEPT_MOD_TAP(RSFT_T, KC_AMPR)
    INTERCEPT_MOD_TAP(RCTL_T, KC_ASTR)
    INTERCEPT_MOD_TAP(RGUI_T, KC_LPRN)
    INTERCEPT_MOD_TAP(RALT_T, KC_RPRN)
  }
  return true;
}
