// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#include "oled.h"
#endif

#ifdef RAW_ENABLE
#pragma message "check other device's vid/pid!"
typedef struct user_config {
  uint8_t cpu_temp;
  uint8_t hour;
  uint8_t min;
} user_state;
#endif

enum layers { _BASE, _LOWER, _RAISE, _ADJUST };

enum tapdances {
  QMK_LINKS,
  EM_DASH_MINS,
  PLY_NXT_PRV,
  RAISE_PASTE,
  CURLY_BRACKET,
  SQR_BRACKET,
  BSLS_PIPE,
  QUOT_DQUO
};

enum custom_keycodes {
  UPDIR = QK_USER,
  NUKE,
  REMOVE,
  TABLE1,
  TABLE2,
  KC_NOMODE,
  KC_WIDE,
  KC_SCRIPT,
  KC_BLOCKS,
  KC_REGIONAL,
  KC_AUSSIE,
  KC_ZALGO,
  KC_SUPER,
  RWORD
};

#ifdef UNICODE_COMMON_ENABLE
bool process_record_unicode(uint16_t keycode, keyrecord_t *record);

enum unicode_mode {
  NOMODE,
  WIDE,
  SCRIPT,
  BLOCKS,
  REGIONAL,
  AUSSIE,
  ZALGO,
  SUPER
};
#endif

#define LINKS TD(QMK_LINKS)
#define PNP TD(PLY_NXT_PRV)
#define RSEPST TD(RAISE_PASTE)
#define ESCLWR LT(_LOWER, KC_ESC)
#define LWRSPC LT(_LOWER, KC_SPC)
#define RSEBSP LT(_RAISE, KC_BSPC)
#define HRML(k1, k2, k3, k4) LALT_T(k1), LGUI_T(k2), LCTL_T(k3), LSFT_T(k4)
#define HRMR(k1, k2, k3, k4) RSFT_T(k1), RCTL_T(k2), RGUI_T(k3), RALT_T(k4)

#define ___BASE1___ KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P
#define ___BASE2___                                                            \
  HRML(KC_A, KC_S, KC_D, KC_F), KC_G, KC_H, HRMR(KC_J, KC_K, KC_L, KC_SCLN)
#define ___BASE3___                                                            \
  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define ___BASE4___ UPDIR, ESCLWR, KC_SPC, KC_BSPC, RSEPST, PNP

#define ___LOWER1___ KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0
#define ___LOWER2___                                                           \
  HRML(KC_EXLM, KC_AT, KC_HASH, KC_DLR), KC_PERC, KC_CIRC,                     \
      HRMR(KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN)
#define ___LOWER3___                                                           \
  KC_VOLD, KC_TAB, KC_CAPS, KC_TILD, KC_GRV, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, \
      KC_VOLU
#define ___LOWER4___ _______, _______, _______, _______, _______, _______

#define ___RAISE1___                                                           \
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NOMODE, KC_SCRIPT,           \
      KC_BLOCKS, KC_REGIONAL, QK_MAKE
#define ___RAISE2___                                                           \
  CK_TOGG, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_WIDE, KC_AUSSIE, KC_ZALGO,  \
      KC_SUPER, QK_BOOT
#define ___RAISE3___                                                           \
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define ___RAISE4___ _______, _______, _______, _______, _______, _______

#define LAYOUT_waffle_60_ts(...) LAYOUT_60_ansi_tsangan(__VA_ARGS__)
#define LAYOUT_stack_of_waffles(...) LAYOUT_stack(__VA_ARGS__)
#define LAYOUT_waffle_3x6(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_waffle_3x5(...) LAYOUT_split_3x5_3(__VA_ARGS__)
#define LAYOUT_waffle(...) LAYOUT(__VA_ARGS__)
