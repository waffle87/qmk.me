// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

tap_dance_action_t tap_dance_actions[] = {
    [EM_DASH_MINS] = ACTION_TAP_DANCE_FN(em_dash_mins),
    [PLY_NXT_PRV] = ACTION_TAP_DANCE_FN(ply_nxt_prv),
    [PASTE_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, raise_paste, td_reset),
    [CBRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [SBRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
};

#define CMB(name, action, ...) name,
enum combos {
#include "combos.def"
};
#undef CMB

#define CMB(name, action, ...)                                                 \
  uint16_t const name##_combo[] PROGMEM = {__VA_ARGS__, COMBO_END};
#include "combos.def"
#undef CMB

#define CMB(name, action, ...) [name] = COMBO(name##_combo, action),
combo_t key_combos[] = {
#include "combos.def"
};
#undef CMB

#if defined(SPLIT_KEYBOARD) && defined(OLED_ENABLE)
#include "transactions.h"
extern char keylog_str[KEYLOG_LEN + 1];
void keylogger_sync(uint8_t initiator2target_buffer_size,
                    const void *initiator2target_buffer,
                    uint8_t target2initiator_buffer_size,
                    void *target2initiator_buffer) {
  if (initiator2target_buffer_size == 5)
    memcpy(&keylog_str, initiator2target_buffer, initiator2target_buffer_size);
}

void housekeeping_task_user(void) {
  if (is_keyboard_master()) {
    static uint32_t last_sync;
    bool needs_sync = false;
    static char tmp_keylog[5] = {0};
    if (memcmp(&keylog_str, &tmp_keylog, 5)) {
      needs_sync = true;
      memcpy(&tmp_keylog, &keylog_str, 5);
    }
    if (timer_elapsed32(last_sync) > 250)
      needs_sync = true;
    if (needs_sync)
      if (transaction_rpc_send(RPC_ID_USER_KEYLOG_STR, 5, &keylog_str))
        last_sync = timer_read32();
  }
}
#endif

void keyboard_post_init_user(void) {
#if defined(SPLIT_KEYBOARD) && defined(OLED_ENABLE)
  transaction_register_rpc(RPC_ID_USER_KEYLOG_STR, keylogger_sync);
#endif
#ifdef CUSTOM_TAP_CODE_ENABLE
  tap_code_buffer_init();
#endif
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#elif RGB_MATRIX_ENABLE
  rgb_matrix_enable_noeeprom();
  rgb_matrix_sethsv_noeeprom(HSV_CYAN);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
#ifdef AUTOCORRECT_ENABLE
  if (!autocorrect_is_enabled())
    autocorrect_enable();
#endif
}

void matrix_scan_user(void) {
#ifdef CUSTOM_TAP_CODE_ENABLE
  process_tap_code_buffer();
#endif
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {{KC_VOLU, KC_VOLD}, {KC_MNXT, KC_MPRV}},
    [_LOWER] = {{RGB_SAI, RGB_SAD}, {RGB_HUI, RGB_HUD}},
    [_RAISE] = {{C(KC_LEFT), C(KC_RGHT)}, {C(S(KC_TAB)), C(KC_TAB)}}};
#endif

#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) { return keycode; }
#endif

#ifndef MAGIC_ENABLE
uint8_t mod_config(uint8_t mod) { return mod; }
#endif
