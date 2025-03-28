// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum macros { DAY = QK_USER, CLEAR };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    DAY,    KC_Q,  KC_W,   KC_E, KC_R, KC_T,
    CLEAR,  KC_A,  KC_S,   KC_D, KC_F, KC_G,
    XXXXXXX,  KC_Z,  KC_X,   KC_C, KC_V, KC_B,
    KC_ESC, MO(1), KC_SPC, XXXXXXX
  ),
  [1] = LAYOUT(
    XXXXXXX, KC_1,    KC_2,  KC_3,  KC_4,  KC_5,
    XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, _______, XXXXXXX, XXXXXXX
  )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case DAY:
    if (record->event.pressed) {
      tap_code(KC_SLSH);
      wait_ms(500);
      SEND_STRING("time set day" SS_TAP(X_ENT));
    }
    break;
  case CLEAR:
    if (record->event.pressed) {
      tap_code(KC_SLSH);
      wait_ms(500);
      SEND_STRING("weather clear" SS_TAP(X_ENT));
    }
    break;
  }
  return true;
}
