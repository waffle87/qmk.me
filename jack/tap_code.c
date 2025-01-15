// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"

#define TAP_CODE_BUFFER_SIZE 32
#define NEXT_TAP_CODE_POS(p) p = ((p + 1) & (TAP_CODE_BUFFER_SIZE - 1))

#define CHECK_REGISTERED_MT(keycode)                                           \
  (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX &&                       \
   (get_mods() & ((keycode & 0x0F00) >> 8)))

#define PGM_LOADBIT(mem, pos)                                                  \
  ((pgm_read_byte(&((mem)[(pos) / 8])) >> ((pos) % 8)) & 1)

typedef struct {
  uint8_t code;
  uint8_t mods;
  uint16_t delay;
  bool register_tap;
} tap_code_buffer;

tap_code_buffer tap_codes[TAP_CODE_BUFFER_SIZE] = {0};
static uint16_t process_pos = 0, queue_pos = 0;
static fast_timer_t process_timer = 0;

void tap_code_buffer_init(void) { memset(&tap_codes, 0, sizeof(tap_codes)); }

void tap_code_register(uint8_t code, uint8_t mods, uint16_t delay,
                       bool register_tap) {
  if (code && !delay) {
    if (mods)
      register_mods(mods);
    register_code(code);
    unregister_code(code);
    if (mods)
      unregister_mods(mods);
    return;
  }
  if (tap_codes[queue_pos].code) {
    if (!process_timer)
      process_tap_code_buffer();
    while (timer_elapsed_fast(process_timer) < tap_codes[process_pos].delay)
      wait_ms(1);
    process_tap_code_buffer();
  }
  tap_codes[queue_pos].code = code;
  tap_codes[queue_pos].mods = mods;
  tap_codes[queue_pos].delay = delay;
  tap_codes[queue_pos].register_tap = register_tap;
  NEXT_TAP_CODE_POS(queue_pos);
}

void process_tap_code_buffer(void) {
  if (tap_codes[process_pos].code) {
    if (!process_timer) {
      if (tap_codes[process_pos].register_tap) {
        if (tap_codes[process_pos].mods) {
          add_weak_mods(tap_codes[process_pos].mods);
        }
        register_code(tap_codes[process_pos].code);
      }
      process_timer = timer_read_fast();
    } else if (timer_elapsed_fast(process_timer) >=
               tap_codes[process_pos].delay) {
      del_weak_mods(tap_codes[process_pos].mods);
      unregister_code(tap_codes[process_pos].code);
      tap_codes[process_pos].code = 0;
      tap_codes[process_pos].mods = 0;
      tap_codes[process_pos].delay = 0;
      tap_codes[process_pos].register_tap = false;
      process_timer = 0;
      NEXT_TAP_CODE_POS(process_pos);
    }
  }
}

void tap_code(uint8_t code) {
  tap_code_register(code, 0, TAP_CODE_DELAY, true);
}

void tap_code_chord(uint8_t code) {
  register_code(code);
  tap_code_register(code, 0, TAP_CODE_DELAY, false);
}

void tap_code_delay(uint8_t code, uint16_t delay) {
  tap_code_register(code, 0, delay, true);
}

void tap_code16(uint16_t code) {
  tap_code_register((uint8_t)code, extract_mod_bits(code), TAP_CODE_DELAY,
                    true);
}

bool process_record_taps(uint16_t keycode, keyrecord_t *record) {
  static fast_timer_t prev_interrupt = 0, prev_key_down = 0;
  switch (keycode) {
  case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
  case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    if (record->event.pressed &&
        ((timer_elapsed_fast(prev_interrupt) < TAPPING_TERM) ||
         (timer_elapsed_fast(prev_key_down) < 200) ||
         CHECK_REGISTERED_MT(keycode))) {
      tap_code_chord(keycode & 0xFF);
      record->tap.count = 0xF;
      prev_interrupt = timer_read_fast();
      return false;
    }
    if (record->tap.count == 0xF)
      return false;
    if (record->tap.count > 1 && (keycode == ESCLWR || keycode == RSEBSP)) {
      if (record->event.pressed) {
        register_code(keycode & 0xFF);
        return false;
      } else {
        unregister_code(keycode & 0xFF);
        return false;
      }
    }
    if (record->tap.count && record->event.pressed) {
      if (keycode >= QK_MOD_TAP || keycode == ESCLWR || keycode == RSEBSP)
        tap_code_chord(keycode & 0xFF);
      else
        tap_code(keycode & 0xFF);
      return false;
    } else if (record->tap.interrupted &&
               (keycode >= QK_MOD_TAP || keycode == ESCLWR ||
                keycode == RSEBSP)) {
      tap_code_chord(keycode & 0xFF);
      prev_interrupt = timer_read_fast();
      return false;
    }
  default:
    if (record->event.pressed)
      prev_key_down = timer_read_fast();
    break;
  }
  return true;
}

extern const uint8_t ascii_to_shift_lut[16];
extern const uint8_t ascii_to_keycode_lut[128];

void tap_char(char ascii_code) {
  uint8_t keycode = pgm_read_byte(&ascii_to_keycode_lut[(uint8_t)ascii_code]);
  bool shifted = PGM_LOADBIT(ascii_to_shift_lut, (uint8_t)ascii_code);
  tap_code_register(keycode, shifted ? MOD_BIT(KC_LSFT) : 0, TAP_CODE_DELAY,
                    true);
}

void tap_string(const char *str) {
  while (1) {
    char ascii_code = pgm_read_byte(str);
    if (!ascii_code)
      break;
    tap_char(ascii_code);
    ++str;
  }
}
