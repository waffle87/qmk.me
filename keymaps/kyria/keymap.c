// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_stack_of_waffles(
    KC_NO, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,
    KC_NO, HRML(KC_A, KC_S, KC_D, KC_F), KC_G,
    KC_NO, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, LINKS, KC_NO,
                  KC_NO, UPDIR, ESCLWR,   KC_SPC,   KC_NO,

                    KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_NO,
                    KC_H, HRMR(KC_J, KC_K, KC_L, KC_SCLN), KC_NO,
    KC_NO, KC_MPLY, KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_NO,
    KC_NO, KC_BSPC, PSTRSE, PNP, KC_NO
  ),

  [_LOWER] = LAYOUT_stack_of_waffles(
    _______, KC_1,    KC_2 ,  KC_3,     KC_4,     KC_5,
    _______, HRML(KC_EXLM, KC_AT, KC_HASH, KC_DLR),  KC_PERC,
    _______, _______, KC_TAB, KC_CAPS,  KC_TILD,  KC_GRV,  _______, _______,
                              _______,  _______,  _______, H_S,     _______,

                      KC_6,    KC_7,     KC_8,     KC_9,     DEG0,     _______,
                      KC_CIRC, HRMR(KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN), _______,
    _______, _______, KC_LEFT, KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,
    _______, STAR,    _______, _______, _______
  ),

  [_RAISE] = LAYOUT_stack_of_waffles(
    _______, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,
    _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
    _______, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,  RWORD,   _______,
                               _______, _______, _______, _______, _______,

                      KC_NOMODE, KC_SCRIPT, KC_BLOCKS, KC_REGIONAL, QK_MAKE, _______,
                      KC_WIDE,   KC_AUSSIE, KC_ZALGO,  KC_SUPER,    QK_BOOT, _______,
    _______, _______, KC_F6,     KC_F7,     KC_F8,     KC_F9,       KC_F10,  _______,
    _______, _______, _______,   _______,   _______
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
  [_BASE]  = { { KC_VOLU, KC_VOLD }, { KC_MNXT, KC_MPRV } },
  [_LOWER] = { { RGB_SAI, RGB_SAD }, { RGB_HUI, RGB_HUD } },
  [_RAISE] = { { KC_LEFT, C(KC_RGHT) }, { C(S(KC_TAB)), C(KC_TAB) } }
};
#endif

#ifdef OLED_ENABLE
bool oled_task_keymap(void) {
  if (is_keyboard_left()) {
    wpm_graph();
    render_wpm();
  }
  return false;
}
#endif

#ifdef RGBLIGHT_ENABLE
void suspend_power_down_user(void) { rgblight_disable(); }
void suspend_wakeup_init_user(void) { rgblight_enable(); }
#endif
