#include "waffle.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_waffle_3x5(
    ___BASE1___,
    ___BASE2___,
    ___BASE3___,
    ___BASE4___
  ),
  [_LOWER] = LAYOUT_waffle_3x5(
    ___LOWER1___,
    ___LOWER2___,
    ___LOWER3___,
    ___LOWER4___
  ),
  [_RAISE] = LAYOUT_waffle_3x5(
    ___RAISE1___,
    ___RAISE2___,
    ___RAISE3___,
    ___RAISE4___
  )
};
