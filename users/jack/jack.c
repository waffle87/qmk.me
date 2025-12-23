// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

void keyboard_post_init_user(void) {
#ifdef AUTOCORRECT_ENABLE
  if (!autocorrect_is_enabled())
    autocorrect_enable();
#endif
  keyboard_post_init_keymap();
}

#ifdef OS_DETECTION_ENABLE
typedef struct {
  bool swap_ctl_gui;
  uint8_t unicode_input_mode;
} os_detection_config;

bool process_detected_host_os_user(os_variant_t detected_os) {
  os_detection_config os_config = {.swap_ctl_gui = true,
                                   .unicode_input_mode = UNICODE_MODE_MACOS};
  if (detected_os == OS_LINUX)
    os_config = (os_detection_config){.swap_ctl_gui = false,
                                      .unicode_input_mode = UNICODE_MODE_LINUX};
  keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui =
      os_config.swap_ctl_gui;
  eeconfig_update_keymap(&keymap_config);
#ifdef UNICODE_COMMON_ENABLE
  set_unicode_input_mode(os_config.unicode_input_mode);
#endif
  return true;
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, LAYER1, LAYER2, LAYER3);
  state = layer_state_set_keymap(state);
  return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case ESC_L1:
  case REP_L2:
  case SPC_L1:
  case BSPC_L2:
    return TAPPING_TERM - 40;
  case TD(PLY_NXT_PRV):
    return TAPPING_TERM + 60;
  default:
    return TAPPING_TERM;
  }
}

#ifdef TAP_DANCE_ENABLE
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

tap_dance_action_t tap_dance_actions[] = {
    [PLY_NXT_PRV] = ACTION_TAP_DANCE_FN(ply_nxt_prv),
};
#endif

#ifdef COMBO_ENABLE
const uint16_t PROGMEM enter_combo[] = {RSFT_T(KC_J), RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM unds_combo[] = {LCTL_T(KC_D), LSFT_T(KC_F), COMBO_END};

combo_t key_combos[] = {
    COMBO(enter_combo, KC_ENT),
    COMBO(unds_combo, KC_UNDS),
};
#endif

#ifdef KEY_OVERRIDE_ENABLE
const key_override_t volume_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_VOLU, KC_VOLD);

const key_override_t *key_overrides[] = {&volume_key_override};
#endif

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record,
                            uint8_t *remembered_mods) {
  if (keycode == REP_L2)
    return false;
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_keymap(keycode, record))
    return false;
  switch (keycode) {
  case KC_MINS:
#ifdef UNICODE_COMMON_ENABLE
    if (get_mods() & MOD_MASK_SHIFT) {
      if (record->event.pressed)
        register_unicode(0x2014);
      return false;
    }
#endif
    break;
  case UPDIR:
    if (record->event.pressed)
      SEND_STRING("../");
    break;
  case REMOVE:
    if (record->event.pressed) {
      SEND_STRING("```suggestion\n```");
      tap_code(KC_UP);
      tap_code(KC_UP);
      tap_code(KC_ENT);
      tap_code(KC_UP);
    }
    break;
  case USRNME:
    if (record->event.pressed)
      SEND_STRING("jack@pngu.org");
    break;
  case GEQ:
    if (record->event.pressed)
      SEND_STRING(">=");
    break;
  case LEQ:
    if (record->event.pressed)
      SEND_STRING("<=");
    break;
  case RECALL:
    if (record->event.pressed)
      SEND_STRING("$_");
    break;
  case REP_L2:
    if (record->tap.count) {
      repeat_key_invoke(&record->event);
      return false;
    }
    break;
    INTERCEPT_MOD_TAP(LSFT_T, RECALL)
    INTERCEPT_MOD_TAP(LALT_T, KC_EXLM)
    INTERCEPT_MOD_TAP(LGUI_T, KC_ASTR)
    INTERCEPT_MOD_TAP(RSFT_T, KC_LPRN)
    INTERCEPT_MOD_TAP(RCTL_T, KC_RPRN)
    INTERCEPT_MOD_TAP(RALT_T, KC_DQUO)
  }
  return true;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER0] = {{KC_VOLU, KC_VOLD}, {KC_MNXT, KC_MPRV}},
    [LAYER1] = {{XRGB_SAI, XRGB_SAD}, {XRGB_HUI, XRGB_HUD}},
    [LAYER2] = {{_______, _______}, {_______, _______}},
    [LAYER3] = {{_______, _______}, {_______, _______}},
};
#endif
