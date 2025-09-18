// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "jack.h"
#include <lib/lib8tion/lib8tion.h>

#define FADE_TRANSITION 500
#define FRAME_PERIOD 16

enum {
  ANIM_SLEEP,
  ANIM_WAKE,
  ANIM_TIME_SCALE_Q6 = (255 * 64 + FADE_TRANSITION / 2) / FADE_TRANSITION
};

static bool illuminated = false;
static uint8_t anim_start_value = 0;
static uint8_t anim_end_value = 0;
static uint8_t anim_type = ANIM_SLEEP;
static uint8_t awake_value = 0;
static uint16_t anim_update_time = 0;
static uint16_t anim_start_time = 0;
static uint32_t sleep_time = 0;

static uint8_t read_curr_value(void) {
  return rgb_matrix_is_enabled() ? rgb_matrix_get_val() : 0;
}

static void update_curr_value(uint8_t value) {
  if (value > 0 && !rgb_matrix_is_enabled())
    rgb_matrix_enable_noeeprom();
  hsv_t hsv = rgb_matrix_get_hsv();
  hsv.v = value;
  rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
}

static void update_sleep_timer(void) {
  sleep_time = (timer_read32() + UINT32_C(RGB_MATRIX_FADE_TIMEOUT)) | 1;
}

static void anim_play(uint8_t type, uint8_t end_value) {
  const uint8_t start_value = read_curr_value();
  if (start_value != end_value) {
    anim_start_time = timer_read() | 1;
    anim_update_time = anim_start_time;
    anim_start_value = start_value;
    anim_end_value = end_value;
    anim_type = type;
    illuminated = true;
  }
}

void housekeeping_task_rgb_matrix(void) {
  if (!illuminated)
    return;
  if (anim_start_time) {
    const uint16_t curr_time = timer_read();
    if (timer_expired(curr_time, anim_update_time)) {
      uint8_t value;
      const uint16_t elapsed_time = curr_time - anim_start_time;
      const uint8_t t =
          elapsed_time <= FADE_TRANSITION
              ? (((uint16_t)elapsed_time * ANIM_TIME_SCALE_Q6) >> 6)
              : UINT8_MAX;
      const uint8_t weight = ease8InOutCubic(t);
      if (weight < UINT8_MAX) {
        value = lerp8by8(anim_start_value, anim_end_value, weight);
        anim_update_time = curr_time + FRAME_PERIOD;
      } else {
        anim_start_time = 0;
        value = anim_end_value;
        switch (anim_type) {
        case ANIM_SLEEP:
          illuminated = false;
          break;
        case ANIM_WAKE:
          update_sleep_timer();
          break;
        }
      }
      update_curr_value(value);
    }
  } else if (sleep_time && timer_expired32(timer_read32(), sleep_time)) {
    awake_value = read_curr_value();
    anim_play(ANIM_SLEEP, 0);
  }
}

void keyboard_post_init_rgb_matrix(void) {
  if (rgb_matrix_is_enabled()) {
    awake_value = rgb_matrix_get_val();
    update_curr_value(0);
    anim_play(ANIM_WAKE, awake_value);
  }
}

bool process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed)
    if (awake_value > 0) {
      if (!illuminated || (anim_start_time && !anim_end_value))
        anim_play(ANIM_WAKE, awake_value);
      else
        update_sleep_timer();
    }
  return true;
}
