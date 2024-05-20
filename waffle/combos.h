// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

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
