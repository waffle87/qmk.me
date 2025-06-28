// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

#ifdef TAP_DANCE_ENABLE
tap_dance_action_t tap_dance_actions[] = {
    [EM_DASH_MINS] = ACTION_TAP_DANCE_FN(em_dash_mins),
    [PLY_NXT_PRV] = ACTION_TAP_DANCE_FN(ply_nxt_prv),
    [PASTE_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, raise_paste, td_reset),
    [CBRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [SBRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
};
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {{KC_VOLU, KC_VOLD}, {KC_MNXT, KC_MPRV}},
    [_LOWER] = {{XRGB_SAI, XRGB_SAD}, {XRGB_HUI, XRGB_HUD}},
    [_RAISE] = {{C(KC_LEFT), C(KC_RGHT)}, {C(S(KC_TAB)), C(KC_TAB)}}};
#endif

#ifdef COMBO_ENABLE
#define CMB(name, action, ...)                                                 \
  uint16_t const name##_combo[] PROGMEM = {__VA_ARGS__, COMBO_END};
#include "combos.def"
#undef CMB

#define CMB(name, action, ...) [name] = COMBO(name##_combo, action),
combo_t key_combos[] = {
#include "combos.def"
};
#undef CMB
#endif
