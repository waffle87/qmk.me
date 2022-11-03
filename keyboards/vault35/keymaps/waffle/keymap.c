#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle(
    ___BASE1___, KC_NO,
    ___BASE2___,
    ___BASE3___,
    ___BASE4___
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
