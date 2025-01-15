// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_jack(
    XXXXXXX,      KC_Q, KC_W, KC_E, KC_R,  KC_T,                                      KC_Y,      KC_U,  KC_I,    KC_O,   KC_P,     XXXXXXX,
    XXXXXXX, HRML(KC_A, KC_S, KC_D, KC_F), KC_G,                                      KC_H, HRMR(KC_J,  KC_K,    KC_L,   KC_SCLN), XXXXXXX,
    XXXXXXX,      KC_Z, KC_X, KC_C, KC_V,  KC_B, KC_SPC, XXXXXXX,      XXXXXXX, KC_BSPC, KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH,  XXXXXXX,
                      XXXXXXX,  UPDIR,  ESCLWR,  KC_SPC, XXXXXXX,      XXXXXXX, KC_BSPC, PSTRSE, PNP, XXXXXXX
  ),

  [_LOWER] = LAYOUT_jack(
    _______,      KC_1,    KC_2 ,  KC_3,    KC_4,    KC_5,                                             KC_6,         KC_7,    KC_8,    KC_9,    KC_0,     _______,
    _______, HRML(KC_EXLM, KC_AT,  KC_HASH, KC_DLR), KC_PERC,                                          KC_CIRC, HRMR(KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN), _______,
    _______,      KC_VOLD, KC_TAB, KC_CAPS, REMOVE,  KC_GRV,  _______, _______,      _______, _______, KC_LEFT,      KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU,  _______,
                                   _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_jack(
    _______, RGB_TOG,  RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,                                         UC_NOMODE, UC_SCRIPT, UC_BLOCKS, UC_REGIONAL, QK_MAKE, _______,
    _______, M_JIGGLE, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,                                         KC_WIDE,   KC_AUSSIE, KC_ZALGO,  KC_SUPER,    QK_BOOT, _______,
    _______, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,  _______, _______,      _______, _______, KC_F6,     KC_F7,     KC_F8,     KC_F9,       KC_F10,  _______,
                                _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
  )
};
// clang-format on

#ifdef OLED_ENABLE
bool oled_task_keymap(void) {
  if (is_keyboard_left()) {
    wpm_graph();
    render_wpm();
  }
  return false;
}
#endif

#ifdef POINTING_DEVICE_ENABLE
static bool scrolling = false;
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case _LOWER:
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
