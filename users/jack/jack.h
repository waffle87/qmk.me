// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

enum layers { LAYER0, LAYER1, LAYER2, LAYER3 };

enum tapdances { EM_DASH_MINS, PLY_NXT_PRV, CBRACKET, SBRACKET };

enum custom_keycodes { UPDIR = QK_USER, REMOVE };

#define CMB(name, action, ...) name,
enum combos {
#include "combos.def"
};
#undef CMB

#ifdef TAP_DANCE_ENABLE
void em_dash_mins(tap_dance_state_t *state, void *user_data);
void ply_nxt_prv(tap_dance_state_t *state, void *user_data);
#endif

void keyboard_pre_init_keymap(void);
void keyboard_post_init_keymap(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

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

#define ESCLWR LT(LAYER1, KC_ESC)
#define PSTRSE LT(LAYER3, KC_PSTE)
#define LWRSPC LT(LAYER1, KC_SPC)
#define RSEBSP LT(LAYER3, KC_BSPC)
#define PNP TD(PLY_NXT_PRV)
#define HRML(k1, k2, k3, k4) LALT_T(k1), LGUI_T(k2), LCTL_T(k3), LSFT_T(k4)
#define HRMR(k1, k2, k3, k4) RSFT_T(k1), RCTL_T(k2), RGUI_T(k3), RALT_T(k4)

// clang-format off
#define ___LAYER00___ KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P
#define ___LAYER01___ HRML(KC_A, KC_S, KC_D, KC_F), KC_G, KC_H, HRMR(KC_J, KC_K, KC_L, KC_SCLN)
#define ___LAYER02___ KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define ___LAYER03___ ESCLWR, KC_SPC, KC_BSPC, PSTRSE

// https://oxey.dev/sturdy/index.html
// #define ___LAYER00___ KC_V, KC_M, KC_L, KC_C, KC_P, KC_X, KC_F, KC_O, KC_U, KC_J
// #define ___LAYER01___ KC_S, KC_T, KC_R, KC_D, KC_Y, KC_DOT, KC_N, KC_A, KC_E, KC_I
// #define ___LAYER02___ KC_Z, KC_K, KC_Q, KC_G, KC_W, KC_B, KC_H, KC_QUOT, KC_SCLN, KC_COMM
// #define ___LAYER03___ _______, _______, _______, _______

// https://github.com/GalileoBlues/Gallium
// #define ___LAYER00___ KC_B, KC_L, KC_D, KC_C, KC_V KC_J, KC_Y, KC_O, KC_U, KC_COMM
// #define ___LAYER00___ KC_N, KC_R, KC_T, KC_S, KC_G, KC_P, KC_H, KC_A, KC_E, KC_I
// #define ___LAYER00___ KC_X, KC_Q, KC_M, KC_W, KC_Z, KC_K, KC_F, KC_QUOT, KC_SCLN, KC_DOT
// #define ___LAYER03___ _______, _______, _______, _______

#define ___LAYER10___ KC_GRV, KC_LABK, KC_RABK, KC_DQUO, KC_DOT, KC_AMPR, REMOVE, KC_LBRC, KC_RBRC, KC_PERC
#define ___LAYER11___ HRML(KC_EXLM, KC_MINS, KC_PLUS, KC_EQL), KC_HASH, KC_PIPE, HRMR(KC_COLN, KC_LPRN, KC_RPRN, KC_QUES)
#define ___LAYER12___ KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, UPDIR, KC_TILD, KC_DLR, KC_LCBR, KC_RCBR, KC_AT
#define ___LAYER13___ _______, _______, _______, _______

// #define ___LAYER10___ _______, KC_9, KC_8, KC_7, KC_TAB, _______, _______, _______, _______, _______
// #define ___LAYER11___ HRML(KC_VOLU, KC_3, KC_2, KC_1), KC_CAPS, KC_LEFT, HRMR(KC_DOWN, KC_UP, KC_RGHT, _______)
// #define ___LAYER12___ KC_VOLD, KC_6, KC_5, KC_4, _______, _______, _______, _______, _______, _______
// #define ___LAYER13___ _______, _______, _______, _______

#define ___LAYER30___ XRGB_TOG, XRGB_NXT,  XRGB_HUI, XRGB_SAI, XRGB_VAI, _______, _______, _______, _______, QK_MAKE
#define ___LAYER31___ _______, XRGB_PRV, XRGB_HUD, XRGB_SAD, XRGB_VAD, _______, _______, _______, _______, QK_BOOT
#define ___LAYER32___ KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define ___LAYER33___ _______, _______, _______, _______
// clang-format on

#define LAYOUT_jack_60_ts(...) LAYOUT_60_ansi_tsangan(__VA_ARGS__)
#define LAYOUT_jack_all(...) LAYOUT_all(__VA_ARGS__)
#define LAYOUT_jack(...) LAYOUT(__VA_ARGS__)
