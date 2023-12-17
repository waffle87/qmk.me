// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
#include "secrets.h"
#ifdef RANDWORD
#include "dict.h"
uint16_t word = 0;
#endif

#define INTERCEPT_MOD_TAP(mod, keycode)             \
case mod(keycode):                                  \
  if (record->tap.count && record->event.pressed) { \
    tap_code16(keycode);                            \
    return false;                                   \
  }                                                 \
  break;                                            \

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LWRSPC:
    case ESCLWR:
    case RSEBSP:
      return TAPPING_TERM - 40;
    case TD(QMK_LINKS):
    case TD(EM_DASH_MINS):
    case TD(PLY_NXT_PRV):
    case TD(CURLY_BRACKET):
    case TD(SQR_BRACKET):
    case TD(BSLS_PIPE):
    case TD(QUOT_DQUO):
      return TAPPING_TERM + 60;
    default:
      return TAPPING_TERM;
  }
}

void td_reset(tap_dance_state_t *state, void *user_data) {
  clear_keyboard();
  layer_clear();
}

void qmk_links(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(C(KC_T));
    send_string(qmkstr);
    tap_code(KC_ENT);
  } else {
    tap_code16(C(KC_T));
    send_string(confstr);
    tap_code(KC_ENT);
  }
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

tap_dance_action_t tap_dance_actions[] = {
  [QMK_LINKS] = ACTION_TAP_DANCE_FN(qmk_links),
  [EM_DASH_MINS] = ACTION_TAP_DANCE_FN(em_dash_mins),
  [PLY_NXT_PRV] = ACTION_TAP_DANCE_FN(ply_nxt_prv),
  [RAISE_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, raise_paste, td_reset),
  [CURLY_BRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [SQR_BRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [BSLS_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
  [QUOT_DQUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef UNICODE_COMMON_ENABLE
  if (!process_record_unicode(keycode, record))
    return false;
#endif
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    oled_timer_reset();
    add_keylog(keycode);
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
    case REMOVE:
      if (record->event.pressed)
        SEND_STRING("This file should be removed.");
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
