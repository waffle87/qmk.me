// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack(
    XXXXXXX,      KC_Q, KC_W, KC_E, KC_R,  KC_T,                                      KC_Y,      KC_U,  KC_I,    KC_O,   KC_P,     XXXXXXX,
    XXXXXXX, HRML(KC_A, KC_S, KC_D, KC_F), KC_G,                                      KC_H, HRMR(KC_J,  KC_K,    KC_L,   KC_SCLN), XXXXXXX,
    XXXXXXX,      KC_Z, KC_X, KC_C, KC_V,  KC_B, KC_SPC, XXXXXXX,      XXXXXXX, KC_BSPC, KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH,  XXXXXXX,
                      XXXXXXX,  UPDIR,  ESCLWR,  KC_SPC, XXXXXXX,      XXXXXXX, KC_BSPC, PSTRSE, PNP, XXXXXXX
  ),

  [LAYER1] = LAYOUT_jack(
    _______,      KC_1,    KC_2 ,  KC_3,    KC_4,    KC_5,                                             KC_6,         KC_7,    KC_8,    KC_9,    KC_0,     _______,
    _______, HRML(KC_EXLM, KC_AT,  KC_HASH, KC_DLR), KC_PERC,                                          KC_CIRC, HRMR(KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN), _______,
    _______,      KC_VOLD, KC_TAB, KC_CAPS, REMOVE,  KC_GRV,  _______, _______,      _______, _______, KC_LEFT,      KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU,  _______,
                                   _______, _______, _______, _______, _______,      _______, _______, SWTCH, _______, _______
  ),

  [LAYER3] = LAYOUT_jack(
    _______, XRGB_TOG, XRGB_NXT, XRGB_HUI, XRGB_SAI, XRGB_VAI,                                        _______, _______, _______, _______, QK_MAKE, _______,
    _______, LUMINO,   XRGB_PRV, XRGB_HUD, XRGB_SAD, XRGB_VAD,                                        _______, _______, _______, _______, QK_BOOT, _______,
    _______, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,  _______, _______,      _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
                                  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
  )
};
// clang-format on

#ifdef OLED_ENABLE
uint32_t oled_timer = 0;

void oled_timer_reset(void) { oled_timer = timer_read32(); }

void oled_wpm_graph(void) {
  static uint8_t height = OLED_DISPLAY_HEIGHT - 1, vert_count = 0,
                 max_wpm = 160;
  extern uint8_t oled_buffer[OLED_MATRIX_SIZE];
  extern OLED_BLOCK_TYPE oled_dirty;
  static uint16_t graph_timer = 0;
  if (timer_elapsed(graph_timer) > 100) {
    height = 63 - ((get_current_wpm() / (float)max_wpm) * 63);
    for (uint8_t i = 0; i <= 1; i++)
      oled_write_pixel(3, height + i, true);
    if (vert_count == 3) {
      vert_count = 0;
      while (height <= 63) {
        oled_write_pixel(3, height, true);
        height++;
      }
    } else {
      for (uint8_t i = 63; i > height; i--)
        if (!(i % 3))
          oled_write_pixel(3, i, true);
      vert_count++;
    }
    for (uint16_t y = 0; y < 8; y++) {
      for (uint16_t x = 124; x > 0; x--) {
        uint16_t i = y * OLED_DISPLAY_WIDTH + x;
        oled_buffer[i] = oled_buffer[i - 1];
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (i / OLED_BLOCK_SIZE));
      }
    }
    graph_timer = timer_read();
  }
}

void oled_wpm(void) {
  oled_write(PSTR("WPM: "), false);
  oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
}

bool oled_task_keymap(void) {
  if (is_keyboard_master()) {
    if (timer_elapsed32(oled_timer) > THREE_MIN) {
      oled_off();
      return false;
    } else
      oled_on();
  }
  if (is_keyboard_left()) {
    oled_wpm_graph();
    oled_wpm();
  }
  return false;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed)
    oled_timer_reset();
  return true;
}
#endif

#ifdef POINTING_DEVICE_ENABLE
static bool scrolling = false;
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case LAYER1:
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
