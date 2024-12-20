// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"
#ifdef RANDWORD
#include "dict.h"
uint16_t word = 0;
#endif

#define INTERCEPT_MOD_TAP(mod, keycode)                                        \
  case mod(keycode):                                                           \
    if (record->tap.count && record->event.pressed) {                          \
      tap_code16(keycode);                                                     \
      return false;                                                            \
    }                                                                          \
    break;

static uint8_t select_word_state = NONE;

bool process_select_word(uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_LSFT || keycode == KC_RSFT)
    return true;
  if (keycode == SELWORD && record->event.pressed) {
    const bool shifted = get_mods() & MOD_MASK_SHIFT;
    if (!shifted) {
      set_mods(MOD_BIT(KC_LCTL));
      if (select_word_state == NONE) {
        send_keyboard_report();
        tap_code(KC_RGHT);
        tap_code(KC_LEFT);
      }
      register_mods(MOD_BIT(KC_LSFT));
      register_code(KC_RGHT);
      select_word_state = WORD;
    } else {
      if (select_word_state == NONE) {
        clear_mods();
        send_keyboard_report();
        tap_code(KC_HOME);
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_END);
        set_mods(get_mods());
        select_word_state = FIRST_LINE;
      } else {
        register_code(KC_DOWN);
        select_word_state = LINE;
      }
    }
    return false;
  }
  switch (select_word_state) {
  case WORD:
    unregister_code(KC_RGHT);
    unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LCTL));
    select_word_state = SELECTED;
    break;
  case FIRST_LINE:
    select_word_state = SELECTED;
    break;
  case LINE:
    unregister_code(KC_DOWN);
    select_word_state = SELECTED;
    break;
  case SELECTED:
    if (keycode == KC_ESC) {
      tap_code(KC_RGHT);
      select_word_state = NONE;
      return false;
    }
  default:
    select_word_state = NONE;
  }
  return true;
}

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef UNICODE_COMMON_ENABLE
  if (!process_record_unicode(keycode, record))
    return false;
#endif
  if (!process_select_word(keycode, record))
    return false;
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
      SEND_STRING("../");
    break;
  case NUKE:
    if (record->event.pressed) {
      tap_code16(C(KC_A));
      SEND_STRING("\b```suggestion\n```");
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
  case RWORD:
#ifdef RANDWORD
    word = rand() % NUM_WORDS;
    if (record->event.pressed) {
      send_string(dict[word]);
      tap_code(KC_SPC);
    }
#endif
    break;
  }
  return true;
}
