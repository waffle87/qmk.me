// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

enum layers { _BASE, _LOWER, _RAISE };

enum tapdances { EM_DASH_MINS, PLY_NXT_PRV, CBRACKET, SBRACKET };

enum custom_keycodes {
  UPDIR = QK_USER,
  REMOVE,
  MS_JIGGLE,
  UC_NOMODE,
  UC_WIDE,
  UC_SCRIPT,
  UC_BLOCKS,
  UC_REGIONAL,
  UC_AUSSIE,
  UC_ZALGO,
  UC_SUPER
};

#define CMB(name, action, ...) name,
enum combos {
#include "combos.def"
};
#undef CMB

#ifdef UNICODE_COMMON_ENABLE
bool process_record_unicode(uint16_t keycode, keyrecord_t *record);
#endif

#ifdef RGB_MATRIX_ENABLE
void housekeeping_task_rgb_matrix(void);
void keyboard_post_init_rgb_matrix(void);
bool process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record);
#endif

#ifdef TAP_DANCE_ENABLE
void em_dash_mins(tap_dance_state_t *state, void *user_data);
void ply_nxt_prv(tap_dance_state_t *state, void *user_data);
#endif

#ifdef OLED_ENABLE
bool oled_task_keymap(void);
void oled_timer_reset(void);
void render_wpm_graph(void);
void render_felix_dog(void);
void render_layer_anim(void);
void render_layer_status(void);
void render_mod_status(void);
void render_wpm(void);
#endif

void keyboard_pre_init_keymap(void);
void keyboard_post_init_keymap(void);
void housekeeping_task_keymap(void);

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

#define ESCLWR LT(_LOWER, KC_ESC)
#define PSTRSE LT(_RAISE, KC_PSTE)
#define LWRSPC LT(_LOWER, KC_SPC)
#define RSEBSP LT(_RAISE, KC_BSPC)
#define PNP TD(PLY_NXT_PRV)
#define HRML(k1, k2, k3, k4) LALT_T(k1), LGUI_T(k2), LCTL_T(k3), LSFT_T(k4)
#define HRMR(k1, k2, k3, k4) RSFT_T(k1), RCTL_T(k2), RGUI_T(k3), RALT_T(k4)

// clang-format off
#define ___BASE1___ KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P
#define ___BASE2___ HRML(KC_A, KC_S, KC_D, KC_F), KC_G, KC_H, HRMR(KC_J, KC_K, KC_L, KC_SCLN)
#define ___BASE3___ KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define ___BASE4___ ESCLWR, KC_SPC, KC_BSPC, PSTRSE

#define ___LOWER1___ KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0
#define ___LOWER2___ HRML(KC_EXLM, KC_AT, KC_HASH, KC_DLR), KC_PERC, KC_CIRC, HRMR(KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN)
#define ___LOWER3___ KC_VOLD, KC_TAB, KC_CAPS, REMOVE, KC_GRV, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_VOLU
#define ___LOWER4___ _______, _______, SWTCH, PNP

#define ___RAISE1___ XRGB_TOG, XRGB_NXT,  XRGB_HUI, XRGB_SAI, XRGB_VAI, UC_NOMODE, UC_SCRIPT, UC_BLOCKS, UC_REGIONAL, QK_MAKE
#define ___RAISE2___ MS_JIGGLE, XRGB_PRV, XRGB_HUD, XRGB_SAD, XRGB_VAD, UC_WIDE, UC_AUSSIE, UC_ZALGO, UC_SUPER, QK_BOOT
#define ___RAISE3___ KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define ___RAISE4___ _______, UPDIR, _______, _______
// clang-format on

#define LAYOUT_jack_60_ts(...) LAYOUT_60_ansi_tsangan(__VA_ARGS__)
#define LAYOUT_jack_all(...) LAYOUT_all(__VA_ARGS__)
#define LAYOUT_jack(...) LAYOUT(__VA_ARGS__)
