// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define TAPPING_TERM_PER_KEY
#define PERSMISSVE_HOLD
#define TAPPING_TERM 140
#define LAYER_STATE_8BIT
#define FORCE_NKRO
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define COMBO_TERM 40
#define NO_ACTION_ONESHOT
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
#define ENABLE_COMPILE_KEYCODE
#define IGNORE_ATOMIC_BLOCK
#ifdef RAW_ENABLE
#undef VENDOR_ID
#define VENDOR_ID 0x6A73
#undef PRODUCT_ID
#define PRODUCT_ID 0x6B62
#endif
#undef MANUFACTURER
#define MANUFACTURER "waffles"

#ifdef OLED_ENABLE
#    define OLED_FONT_H "users/waffle/oledfont.h"
#    define OLED_UPDATE_INTERVAL 50
#    define OLED_DISABLE_TIMEOUT
#endif

#ifdef SPLIT_KEYBOARD
#    define MASTER_RIGHT
#    define SPLIT_MODS_ENABLE
#    define SPLIT_WPM_ENABLE
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_OLED_ENABLE
#    define SPLIT_LED_STATE_ENABLE
#    define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_KEYLOG_STR
#endif
