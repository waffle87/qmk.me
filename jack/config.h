// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 140
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define COMBO_TERM 40
#define NO_ACTION_ONESHOT
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
#define ENABLE_COMPILE_KEYCODE
#define LAYER_STATE_8BIT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#undef MANUFACTURER
#define MANUFACTURER "jacks"

#ifdef OLED_ENABLE
#define OLED_FONT_H "users/jack/oledfont.h"
#define OLED_UPDATE_INTERVAL 50
#define OLED_DISABLE_TIMEOUT
#endif

#ifdef SPLIT_KEYBOARD
#define MASTER_RIGHT
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_ACTIVITY_ENABLE
#define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_KEYLOG_STR
#endif

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_TIMEOUT 300000
#undef RGB_MATRIX_DEFAULT_MODE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define PALETTEFX_ENABLE_ALL_EFFECTS
#define PALETTEFX_ENABLE_ALL_PALETTES
#endif
