// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "oled.h"
#include "waffle.h"

uint32_t oled_timer = 0;
char keylog_str[KEYLOG_LEN + 1] = {0};

void oled_timer_reset(void) { oled_timer = timer_read32(); }

__attribute__((weak)) bool oled_task_keymap(void) { return true; }

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    if (timer_elapsed32(oled_timer) > 300000) {
      oled_off();
      return false;
    } else
      oled_on();
  }
  oled_task_keymap();
  return false;
}

void anim_frame(uint16_t size, char const action[][size]) {
  static uint8_t current_frame = 0;
  current_frame = (current_frame + 1) & 1;
  oled_write_raw(action[current_frame], size);
}

#ifdef OLED_DISPLAY_128X64
void wpm_graph(void) {
  static uint8_t height = OLED_DISPLAY_HEIGHT - 1, vert_count = 0,
                 max_wpm = 160;
  static uint16_t graph_timer = 0;
  if (timer_elapsed(graph_timer) > 100) {
    height = 63 - ((get_current_wpm() / (float)max_wpm) * 63);
    for (uint8_t i = 0; i <= 1; i++)
      oled_write_pixel(3, height + i, true);
    if (vert_count == 3) {
      vert_count = 0;
      while (height <= 63) {
        oled_write_pixel(3, height, true);
        height++;
      }
    } else {
      for (uint8_t i = 63; i > height; i--)
        if (!(i % 3))
          oled_write_pixel(3, i, true);
      vert_count++;
    }
    for (uint16_t y = 0; y < 8; y++) {
      for (uint16_t x = 124; x > 0; x--) {
        uint16_t i = y * OLED_DISPLAY_WIDTH + x;
        oled_buffer[i] = oled_buffer[i - 1];
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (i / OLED_BLOCK_SIZE));
      }
    }
    graph_timer = timer_read();
  }
}
#endif

void felix_dog(void) {
  static uint16_t felix_anim_timer = 0;
  bool shifted =
      get_mods() & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock;
  if (timer_elapsed(felix_anim_timer) > 200) {
    felix_anim_timer = timer_read();
    if (shifted || is_caps_word_on())
      anim_frame(96, felix_bark);
    else if (get_mods() & MOD_MASK_CAG)
      anim_frame(96, felix_sneak);
    else if (get_current_wpm() > 60)
      anim_frame(96, felix_run);
    else if (get_current_wpm() && get_current_wpm() <= 60)
      anim_frame(96, felix_walk);
    else
      anim_frame(96, felix_sit);
  }
}

void layer_anim(void) {
  static uint16_t layer_anim_timer = 0;
  if (timer_elapsed(layer_anim_timer) > 200) {
    layer_anim_timer = timer_read();
    switch (get_highest_layer(layer_state)) {
    case _BASE:
      anim_frame(520, tap_num);
      break;
    case _LOWER:
      anim_frame(650, tap_sym);
      break;
    case _RAISE:
      anim_frame(520, tap_sys);
      break;
    }
  }
}

void layer_status(void) {
  static const char PROGMEM base[] = {0x20, 0x94, 0x95, 0x96, 0x20,
                                      0x20, 0xb4, 0xb5, 0xb6, 0x20,
                                      0x20, 0xd4, 0xd5, 0xd6, 0x20};
  static const char PROGMEM lower[] = {0x20, 0x9a, 0x9b, 0x9c, 0x20,
                                       0x20, 0xba, 0xbb, 0xbc, 0x20,
                                       0x20, 0xda, 0xdb, 0xdc, 0x20};
  static const char PROGMEM raise[] = {0x20, 0x97, 0x98, 0x99, 0x20,
                                       0x20, 0xb7, 0xb8, 0xb9, 0x20,
                                       0x20, 0xd7, 0xd8, 0xd9, 0x20};
  switch (get_highest_layer(layer_state)) {
  case _LOWER:
    oled_write(lower, false);
    break;
  case _RAISE:
    oled_write(raise, false);
    break;
  default:
    oled_write(base, false);
  }
}

void render_mod_status(void) {
  const uint8_t mods = get_mods();
  static const char PROGMEM
      gui_off_1[] = {0x85, 0x86},
      gui_off_2[] = {0xa5, 0xa6}, gui_on_1[] = {0x8d, 0x8e},
      gui_on_2[] = {0xad, 0xae}, alt_off_1[] = {0x87, 0x88},
      alt_off_2[] = {0xa7, 0xa8}, alt_on_1[] = {0x8f, 0x90},
      alt_on_2[] = {0xaf, 0xb0}, ctrl_off_1[] = {0x89, 0x8a},
      ctrl_off_2[] = {0xa9, 0xaa}, ctrl_on_1[] = {0x91, 0x92},
      ctrl_on_2[] = {0xb1, 0xb2}, shift_off_1[] = {0x8b, 0x8c},
      shift_off_2[] = {0xab, 0xac}, shift_on_1[] = {0xcd, 0xce},
      shift_on_2[] = {0xcf, 0xd0}, off_off_1[] = {0xc5}, off_off_2[] = {0xc6},
      on_off_1[] = {0xc7}, on_off_2[] = {0xc8}, off_on_1[] = {0xc9},
      off_on_2[] = {0xca}, on_on_1[] = {0xcb}, on_on_2[] = {0xcc};

  oled_write(mods & MOD_MASK_GUI ? gui_on_1 : gui_off_1, false);
  if ((mods & MOD_MASK_GUI) && (mods & MOD_MASK_ALT))
    oled_write(on_on_1, false);
  else if (mods & MOD_MASK_GUI)
    oled_write(on_off_1, false);
  else if (mods & MOD_MASK_ALT)
    oled_write(off_on_1, false);
  else
    oled_write(off_off_1, false);
  oled_write(mods & MOD_MASK_ALT ? alt_on_1 : alt_off_1, false);
  oled_write(mods & MOD_MASK_GUI ? gui_on_2 : gui_off_2, false);
  if ((mods & MOD_MASK_GUI) && (mods & MOD_MASK_ALT))
    oled_write(on_on_2, false);
  else if (mods & MOD_MASK_GUI)
    oled_write(on_off_2, false);
  else if (mods & MOD_MASK_ALT)
    oled_write(off_on_2, false);
  else
    oled_write(off_off_2, false);
  oled_write(mods & MOD_MASK_ALT ? alt_on_2 : alt_off_2, false);
  oled_write(mods & MOD_MASK_CTRL ? ctrl_on_1 : ctrl_off_1, false);
  if ((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_SHIFT))
    oled_write(on_on_1, false);
  else if (mods & MOD_MASK_CTRL)
    oled_write(on_off_1, false);
  else if (mods & MOD_MASK_SHIFT)
    oled_write(off_on_1, false);
  else
    oled_write(off_off_1, false);
  oled_write(mods & MOD_MASK_SHIFT ? shift_on_1 : shift_off_1, false);
  oled_write(mods & MOD_MASK_CTRL ? ctrl_on_2 : ctrl_off_2, false);
  if ((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_SHIFT))
    oled_write(on_on_2, false);
  else if (mods & MOD_MASK_CTRL)
    oled_write(on_off_2, false);
  else if (mods & MOD_MASK_SHIFT)
    oled_write(off_on_2, false);
  else
    oled_write(off_off_2, false);
  oled_write(mods & MOD_MASK_SHIFT ? shift_on_2 : shift_off_2, false);
}

void add_keylog(uint16_t keycode, keyrecord_t *record) {
  if (IS_QK_MOD_TAP(keycode))
    keycode =
        record->tap.count
            ? keycode_config(QK_MOD_TAP_GET_TAP_KEYCODE(keycode))
            : keycode_config(0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) +
                             biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10));
  else if (IS_QK_LAYER_TAP(keycode) && (record->tap.count))
    keycode = keycode_config(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode));
  else if (IS_QK_MODS(keycode))
    keycode = keycode_config(QK_MODS_GET_BASIC_KEYCODE(keycode));
  else if (IS_QK_BASIC(keycode))
    keycode = keycode_config(keycode);
  if ((keycode == KC_BSPC) && mod_config(get_mods()) & MOD_MASK_CTRL) {
    memset(keylog_str, ' ', KEYLOG_LEN);
    keylog_str[KEYLOG_LEN] = '\0';
    return;
  }
  char code = 0;
  if (keycode < ARRAY_SIZE(code_to_name))
    code = pgm_read_byte(&code_to_name[keycode]);
  if (code) {
    memmove(keylog_str, keylog_str + 1, KEYLOG_LEN - 1);
    keylog_str[KEYLOG_LEN - 1] = code;
  }
}

void render_keylog(void) {
  oled_write(PSTR("KLG: "), false);
  oled_write_ln(keylog_str, false);
}

void render_wpm(void) {
  oled_write(PSTR("WPM: "), false);
  oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
}

#ifdef DEBUG_MATRIX_SCAN_RATE
void render_scan_rate(void) {
  oled_write(PSTR("MSR: "), false);
  oled_write_ln(get_u16_str(get_matrix_scan_rate(), ' '), false);
}
#endif

void oled_render_boot(bool jump_to_bootloader) {
  oled_clear();
  static const char PROGMEM qmk_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84,
                                            0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
                                            0xC0, 0xC1, 0xC2, 0xC3, 0xC4};
  oled_write(qmk_logo, false);
  oled_set_cursor(0, 4);
  oled_write(qmk_logo, false);
  oled_set_cursor(0, 8);
  oled_write(qmk_logo, false);
  oled_set_cursor(0, 12);
  oled_write(qmk_logo, false);
  oled_render_dirty(true);
}
