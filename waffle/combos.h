// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define CMB(name, action, ...) C_##name,
enum combos {
#include "combos.def"
  COMBO_LENGTH
};
#undef CMB
uint16_t COMBO_LEN = COMBO_LENGTH;

#define CMB(name, action, ...) const uint16_t PROGMEM name##_combo[] = {__VA_ARGS__, COMBO_END};
#include "combos.def"
#undef CMB

combo_t key_combos[COMBO_LENGTH] = {
#define CMB(name, action, ...) COMBO(name##_combo, action),
#include "combos.def"
#undef CMB
};
