// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "waffle.h"
uint32_t oled_timer = 0;

void render_wpm(void) {
  oled_write(PSTR("WPM: "), false);
  oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
}

#ifdef DEBUG_MATRIX_SCAN_RATE
void render_scan_rate(void) {
  oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);
  oled_write_ln(PSTR("/s"), false);
}
#endif

#ifdef RAW_ENABLE
void host_info(uint8_t data) {
  char buffer[3];
  oled_write_ln((char*)itoa(data, buffer, 10), false);
}

void render_time(void) {
  if (user_state.hour < 10)
    oled_write(PSTR("0"), false);
  host_info(user_state.hour);
  oled_write(PSTR(":"), false);
  if (user_state.min < 10)
    oled_write(PSTR("0"), false);
  host_info(user_state.min);
}
#endif

void qmk_logo(void) {
  static const char PROGMEM qmk_logo[16] = {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
  oled_write(qmk_logo, false);
};

void render_keyboard(void) {
  static const char PROGMEM keyboard[16] = {0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0};
  oled_write(keyboard, false);
};

void layer_status(void) {
  bool blink = (timer_read() % 1000) < 500;
  switch (get_highest_layer(layer_state)) {
    case _RAISE:
      oled_write_ln(PSTR("> hi"), false);
      break;
    case _LOWER:
      oled_write_ln(PSTR("> lo"), false);
      break;
    case _ADJUST:
      oled_write_ln(PSTR("> ad"), false);
      break;
    default:
      oled_write_ln(blink ? PSTR("> _") : PSTR(">   "), false);
  }
};

void mod_status(uint8_t mods) {
  static const char PROGMEM status [4][3] = {{0xd3, 0xd4, 0}, {0x93, 0x94, 0}, {0xb3, 0xb4, 0}, {0x95, 0x96, 0}};
  bool blink = (timer_read() % 1000) < 500;
  if (mods & MOD_MASK_CTRL) {
    oled_set_cursor(2, 11);
    oled_write(status[0], false);
  } else if (mods & MOD_MASK_SHIFT) {
    oled_set_cursor(2, 11);
    oled_write(status[1], false);
  } else if (mods & MOD_MASK_ALT) {
    oled_set_cursor(2, 11);
    oled_write(status[2], false);
  } else if (mods & MOD_MASK_GUI) {
    oled_set_cursor(2, 11);
    oled_write(status[3], false);
  } else
    oled_write_ln(blink ? PSTR("$ _") : PSTR("$   "), false);
}

void keylock_status(led_t led_usb_state) {
  bool blink = (timer_read() % 1000) < 500;
  if (led_usb_state.caps_lock)
    oled_write_ln(PSTR("% cap"), false);
  else if (led_usb_state.num_lock)
    oled_write_ln(PSTR("% num"), false);
  else if (led_usb_state.scroll_lock)
     oled_write_ln(PSTR("% scr"), false);
  else
    oled_write_ln(blink ? PSTR("% _") : PSTR("%    "), false);
}

char keylog_str[5]  = {};
static uint16_t keylog_timer = 0;
const char code_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

void add_keylog(uint16_t keycode) {
  for (uint8_t i = ARRAY_SIZE(keylog_str) - 1; i > 0; i--)
    keylog_str[i] = keylog_str[i - 1];
  if (keycode < ARRAY_SIZE(code_to_name))
    keylog_str[0] = code_to_name[keycode & 0xFF];
  keylog_timer   = timer_read();
}

void render_keylog(void) {
  oled_write(keylog_str, false);
}

void render_keylogger(void) { oled_write(keylog_str, false); }

void keylogger_status(void) {
  bool blink = (timer_read() % 1000) < 500;
  oled_write_ln(blink ? PSTR("~ _") : PSTR("~  "), false);
}

void anim_frame(uint16_t size, char const action[][size]) {
  static uint8_t current_frame = 0;
  current_frame = (current_frame + 1) & 1;
  oled_write_raw(action[current_frame], size);
}

#ifdef FELIX_DOG
void felix(void) {
  static uint16_t felix_anim_timer = 0;
  bool shifted = get_mods() & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock || is_caps_word_on();
  void animate(void) {
    if (shifted)
      anim_frame(96, felix_bark);
    else if (get_mods() & MOD_MASK_CAG)
      anim_frame(96, felix_sneak);
    else if (get_current_wpm() > 40)
      anim_frame(96, felix_run);
    else if (get_current_wpm() > 30 && get_current_wpm() <= 40)
      anim_frame(96, felix_walk);
    else
      anim_frame(96, felix_sit);
  }
  if (timer_elapsed(felix_anim_timer) > 200) {
    felix_anim_timer = timer_read();
    animate();
  }
}
#endif

#ifdef BONGO_CAT
void bongo(void) {
  static uint16_t bongo_anim_timer = 0;
  void animate(void) {
    if (get_current_wpm() <= 30) {
      anim_frame(512, bongo_idle);
    } if (get_current_wpm() > 30 && get_current_wpm() <= 40) {
      anim_frame(512, bongo_prep);
    } if (get_current_wpm() > 40) {
      anim_frame(512, bongo_tap);
    }
  }
  if (timer_elapsed(bongo_anim_timer) > 200) {
    bongo_anim_timer = timer_read();
    animate();
  }
}
#endif

#ifdef WPM_GRAPH
void wpm_graph(void) {
  static uint8_t height = OLED_DISPLAY_HEIGHT - 1, vert_count = 0, max_wpm = 160;
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

#ifdef LAYER_ANIM
void layer_anim(void) {
  static uint16_t layer_anim_timer = 0;
  void animate(void) {
    switch (get_highest_layer(layer_state)) {
      case _RAISE:
        anim_frame(650, tap_sym);
        break;
      case _LOWER:
        anim_frame(520, tap_num);
        break;
      case _ADJUST:
        anim_frame(520, tap_sys);
        break;
      default:
        bongo();
    }
  }
  if (timer_elapsed(layer_anim_timer) > 200) {
    layer_anim_timer = timer_read();
    animate();
  }
}
#endif

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    if (timer_elapsed32(oled_timer) > 180000) {
      oled_off();
      return false;
    } else
      oled_on();
  }
  oled_task_keymap();
  return false;
}

void oled_timer_reset(void) {
  oled_timer = timer_read32();
}
