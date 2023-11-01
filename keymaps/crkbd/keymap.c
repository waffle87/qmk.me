// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle_3x6(
    KC_NO, ___BASE1___, KC_NO,
    LINKS, ___BASE2___, RWORD,
    KC_NO, ___BASE3___, KC_NO,
           ___BASE4___
  ),
  [_LOWER] = LAYOUT_waffle_3x6(
    KC_NO, ___LOWER1___, KC_NO,
    KC_NO, ___LOWER2___, KC_NO,
    KC_NO, ___LOWER3___, KC_NO,
           ___LOWER4___
  ),
  [_RAISE] = LAYOUT_waffle_3x6(
    KC_NO, ___RAISE1___, KC_NO,
    KC_NO, ___RAISE2___, KC_NO,
    KC_NO, ___RAISE3___, KC_NO,
           ___RAISE4___
  )
};

void housekeeping_task_keymap(void) {
  if (last_input_activity_elapsed() > 15000) {
    const pin_t row_pins[] = MATRIX_ROW_PINS, col_pins[] = MATRIX_COL_PINS;
    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); ++i) {
      setPinOutput(col_pins[i]);
      writePinLow(col_pins[i]);
    }
    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); ++i) {
      setPinInputHigh(row_pins[i]);
      palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
    }
    __WFI();
    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); ++i) {
      palDisableLineEvent(row_pins[i]);
      writePinHigh(row_pins[i]);
      setPinInputHigh(row_pins[i]);
    }
    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); ++i) {
      writePinHigh(col_pins[i]);
      setPinInputHigh(col_pins[i]);
    }
  }
}

#ifdef AUDIO_ENABLE
void keyboard_pre_init_user(void) { //thank you to @sigprof for this
  palSetLineMode(A5, PAL_MODE_INPUT_ANALOG);
  palSetLineMode(B1, PAL_MODE_INPUT_ANALOG);
}

void keyboard_post_init_keymap(void) {
  // enable OPAMP1 as A5 → B1 follower
  OPAMP3->CSR = OPAMP3_CSR_VMSEL_1 | OPAMP3_CSR_VMSEL_0 | OPAMP3_CSR_VPSEL_0 | OPAMP3_CSR_OPAMP3EN;
}
#endif //audio

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return 3;
  else
    return 2;
  return rotation;
}

bool oled_task_keymap(void) {
  if (is_keyboard_master())
    layer_anim();
  else {
    oled_set_cursor(0, 0);
    render_wpm();
    oled_set_cursor(0, 3);
    felix();
    oled_set_cursor(0, 7);
    render_keyboard();
    oled_set_cursor(0, 9);
    layer_status();
    oled_set_cursor(0, 11);
    mod_status(get_mods());
    oled_set_cursor(0, 13);
    keylock_status(host_keyboard_led_state());
    oled_set_cursor(1, 15);
    render_keylogger();
    oled_set_cursor(0, 15);
    keylogger_status();
  }
  return false;
}
#endif //oled

#ifdef RGB_MATRIX_ENABLE
void matrix_init_user(void) {
  g_led_config = (led_config_t) { {
    {  15,  16,  17,  18,  19,  20 },
    {  14,  13,  12,  11,  10,  9 },
    {  3,   4,   5,   6,   7,   8 },
    { NO_LED, NO_LED, NO_LED,  2,  1,   0 },
    {  47,  46,  45,  44,  43,  42 },
    {  36,  37,  38,  39,  40,  41 },
    {  35,  34,  33,  32,  31,  30 },
    { NO_LED, NO_LED, NO_LED,  27,  28,  29 }
  }, {
    {  95,  63 }, {  85,  39 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  68,  37 },
    {  80,  58 }, {  60,  55 }, {  50,  35 }, {  50,  13 }, {  50,   0 }, {  33,   3 }, {  33,  20 },
    {  33,  37 }, {  16,  42 }, {  16,  24 }, {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 },
    {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, { 129,  63 },
    { 139,  39 }, { 139,  21 }, { 139,   4 }, { 156,   2 }, { 156,  19 }, { 156,  37 }, { 144,  58 },
    { 164,  55 }, { 174,  35 }, { 174,  13 }, { 174,   0 }, { 191,   3 }, { 191,  20 }, { 191,  37 },
    { 208,  42 }, { 208,  24 }, { 208,   7 }, { 224,   7 }, { 224,  24 }, { 224,  41 }, { 139,  16 },
    { 174,  13 }, { 208,  20 }, { 208,  38 }, { 174,  48 }, { 139,  52 },
  }, {
    1, 1, 1, 1, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    1, 1, 4, 4, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 1,
    1, 1, 4, 4, 4, 4, 4,
    1, 1, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1, 2,
    2, 2, 2, 2, 2
  } };
}
#endif //rgb matrix
