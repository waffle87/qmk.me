#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    ___BASE1___, KC_NO,
    ___BASE2___,
    ___BASE3___,
    UPDIR, KC_ESC, LWRSPC, RSEBSP, C(S(KC_V)), PNP
  ),

  [_LOWER] = LAYOUT_waffle(
    ___LOWER1___, KC_NO,
    ___LOWER2___,
    ___LOWER3___,
    ___LOWER4___
  ),
  [_RAISE] = LAYOUT_waffle(
    ___RAISE1___, KC_NO,
    ___RAISE2___,
    ___RAISE3___,
    ___RAISE4___
  )
};

void keyboard_post_init_user(void) {
  rgblight_sethsv_noeeprom(104,255,255);
}
