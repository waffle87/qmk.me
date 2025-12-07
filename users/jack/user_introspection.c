// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

#ifdef TAP_DANCE_ENABLE
tap_dance_action_t tap_dance_actions[] = {
    [EM_DASH_MINS] = ACTION_TAP_DANCE_FN(em_dash_mins),
    [PLY_NXT_PRV] = ACTION_TAP_DANCE_FN(ply_nxt_prv),
};
#endif

#ifdef COMBO_ENABLE
const uint16_t PROGMEM enter_combo[] = {KC_J, KC_K, COMBO_END};
combo_t key_combos[] = {COMBO(enter_combo, KC_ENT)};
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER0] = {{KC_VOLU, KC_VOLD}, {KC_MNXT, KC_MPRV}},
    [LAYER1] = {{XRGB_SAI, XRGB_SAD}, {XRGB_HUI, XRGB_HUD}},
    [LAYER2] = {{_______, _______}, {_______, _______}},
    [LAYER3] = {{_______, _______}, {_______, _______}},
};
#endif
