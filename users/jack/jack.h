// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

enum layers { LAYER0, LAYER1, LAYER2, LAYER3 };

enum tapdances { PLY_NXT_PRV };

enum custom_keycodes { UPDIR = QK_USER, REMOVE, USRNME, GEQ, LEQ, RECALL };

void keyboard_post_init_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define INTERCEPT_MOD_TAP(mod, keycode)                                        \
  case mod(keycode):                                                           \
    if (record->tap.count && record->event.pressed) {                          \
      tap_code16(keycode);                                                     \
      return false;                                                            \
    }                                                                          \
    break;

#ifdef RGB_MATRIX_ENABLE
#define XRGB_TOG RM_TOGG
#define XRGB_NXT RM_NEXT
#define XRGB_PRV RM_PREV
#define XRGB_HUI RM_HUEU
#define XRGB_HUD RM_HUED
#define XRGB_SAI RM_SATU
#define XRGB_SAD RM_SATD
#define XRGB_VAI RM_VALU
#define XRGB_VAD RM_VALD
#elif RGBLIGHT_ENABLE
#define XRGB_TOG UG_TOGG
#define XRGB_NXT UG_NEXT
#define XRGB_PRV UG_PREV
#define XRGB_HUI UG_HUEU
#define XRGB_HUD UG_HUED
#define XRGB_SAI UG_SATU
#define XRGB_SAD UG_SATD
#define XRGB_VAI UG_VALU
#define XRGB_VAD UG_VALD
#else
#define XRGB_TOG _______
#define XRGB_NXT _______
#define XRGB_PRV _______
#define XRGB_HUI _______
#define XRGB_HUD _______
#define XRGB_SAI _______
#define XRGB_SAD _______
#define XRGB_VAI _______
#define XRGB_VAD _______
#endif

#define ESC_L1 LT(LAYER1, KC_ESC)
#define REP_L2 LT(LAYER2, KC_NO)
#define SPC_L1 LT(LAYER1, KC_SPC)
#define BSPC_L2 LT(LAYER2, KC_BSPC)
#define HRML(k1, k2, k3, k4) LALT_T(k1), LGUI_T(k2), LCTL_T(k3), LSFT_T(k4)
#define HRMR(k1, k2, k3, k4) RSFT_T(k1), RCTL_T(k2), RGUI_T(k3), RALT_T(k4)

// clang-format off
#define ___LAYER00___ KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P
#define ___LAYER01___ HRML(KC_A, KC_S, KC_D, KC_F), KC_G, KC_H, HRMR(KC_J, KC_K, KC_L, KC_SCLN)
#define ___LAYER02___ KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define ___LAYER03___ ESC_L1, KC_SPC, KC_BSPC, REP_L2

#define ___LAYER10___ KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0
#define ___LAYER11___ HRML(_______, _______, _______, RECALL), KC_TAB, KC_LEFT, HRMR(KC_DOWN, KC_UP, KC_RGHT, KC_CAPS)
#define ___LAYER12___ KC_VOLU, TD(PLY_NXT_PRV), REMOVE, UPDIR, USRNME, _______, _______, _______, _______, _______
#define ___LAYER13___ _______, _______, _______, _______

#define ___LAYER20___ KC_GRV, LEQ, GEQ, KC_MINS, KC_PIPE, KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR, KC_BSLS
#define ___LAYER21___ HRML(KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL), KC_AMPR, KC_HASH, HRMR(KC_LPRN, KC_RPRN, KC_QUOT, KC_DQUO)
#define ___LAYER22___ KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, KC_AT, KC_COLN, _______, _______, _______
#define ___LAYER23___ _______, _______, _______, _______

#define ___LAYER30___ XRGB_NXT,  XRGB_HUI, XRGB_SAI, XRGB_VAI, XRGB_TOG, _______, _______, _______, _______, QK_MAKE
#define ___LAYER31___ XRGB_PRV, XRGB_HUD, XRGB_SAD, XRGB_VAD, _______, _______, _______, _______, _______, QK_BOOT
#define ___LAYER32___ KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define ___LAYER33___ _______, _______, _______, _______
// clang-format on

#define LAYOUT_jack_60_ts(...) LAYOUT_60_ansi_tsangan(__VA_ARGS__)
#define LAYOUT_jack_all(...) LAYOUT_all(__VA_ARGS__)
#define LAYOUT_jack(...) LAYOUT(__VA_ARGS__)
