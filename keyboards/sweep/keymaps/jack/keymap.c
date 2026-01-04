// Copyright 2026 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER0] = LAYOUT_jack(
    ___LAYER00___,
    ___LAYER01___,
    ___LAYER02___,
    ___LAYER03___
  ),
  [LAYER1] = LAYOUT_jack(
    ___LAYER10___,
    ___LAYER11___,
    ___LAYER12___,
    ___LAYER13___
  ),
  [LAYER2] = LAYOUT_jack(
    ___LAYER20___,
    ___LAYER21___,
    ___LAYER22___,
    ___LAYER23___
  ),
  [LAYER3] = LAYOUT_jack(
    ___LAYER30___,
    ___LAYER31___,
    ___LAYER32___,
    ___LAYER33___
  )
};
// clang-format on
