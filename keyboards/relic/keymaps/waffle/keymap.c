#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    ___BASE1___, PNP,
    ___BASE2___,
    ___BASE3___,
    KC_VOLD, KC_ESC, LWRSPC, RSEBSP, C(S(KC_V)), KC_VOLU
  ),

  [_LOWER] = LAYOUT_waffle(
    ___LOWER1___, QK_MAKE,
    ___LOWER2___,
    ___LOWER3___,
    KC_TRNS, TABLE1, KC_TRNS, KC_TRNS, TABLE2, KC_TRNS
  ),
  [_RAISE] = LAYOUT_waffle(
    ___RAISE1___, KC_TRNS,
    ___RAISE2___,
    ___RAISE3___,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};
