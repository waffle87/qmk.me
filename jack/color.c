// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "color.h"
#include <lib/lib8tion/lib8tion.h>
#define FORCE_REFERENCE(var) __asm__ volatile("" : : "r"(var))
#define FASTLED_SCALE8_FIXED 1

RGB rgb_matrix_hsv_to_rgb(const HSV hsv) {
  const uint8_t Y1 = 1, Y2 = 0, G_2 = 1, Gscale = 0, hue = hsv.h, sat = hsv.s;
  uint8_t val = hsv.v, offset = hue & 0x1F, offset8 = offset;
  {
#ifdef __AVR__
    offset8 <<= 1;
    __asm__ volatile("");
    offset8 <<= 1;
    __asm__ volatile("");
    offset8 <<= 1;
#else
    offset8 <<= 3;
#endif
  }
  uint8_t third = scale8(offset8, (256 / 3)), r, g, b;
  if (!(hue & 0x80)) {
    if (!(hue & 0x40)) {
      if (!(hue & 0x20)) {
        r = 255 - third;
        g = third;
        b = 0;
        FORCE_REFERENCE(b);
      } else {
        if (Y1) {
          r = 171;
          g = 85 + third;
          b = 0;
          FORCE_REFERENCE(b);
        }
        if (Y2) {
          r = 170 + third;
          uint8_t twothirds = scale8(offset8, ((256 * 2) / 3));
          g = 85 + twothirds;
          b = 0;
          FORCE_REFERENCE(b);
        }
      }
    } else {
      if (!(hue & 0x20)) {
        if (Y1) {
          uint8_t twothirds = scale8(offset8, ((256 * 2) / 3));
          r = 171 - twothirds;
          g = 170 + third;
          b = 0;
          FORCE_REFERENCE(b);
        }
        if (Y2) {
          r = 255 - offset8;
          g = 255;
          b = 0;
          FORCE_REFERENCE(b);
        }
      } else {
        r = 0;
        FORCE_REFERENCE(r);
        g = 255 - third;
        b = third;
      }
    }
  } else {
    if (!(hue & 0x40)) {
      if (!(hue & 0x20)) {
        r = 0;
        FORCE_REFERENCE(r);
        uint8_t twothirds = scale8(offset8, ((256 * 2) / 3));
        g = 171 - twothirds;
        b = 85 + twothirds;
      } else {
        r = third;
        g = 0;
        FORCE_REFERENCE(g);
        b = 255 - third;
      }
    } else {
      if (!(hue & 0x20)) {
        r = 85 + third;
        g = 0;
        FORCE_REFERENCE(g);
        b = 171 - third;
      } else {
        r = 170 + third;
        g = 0;
        FORCE_REFERENCE(g);
        b = 85 - third;
      }
    }
  }
  if (G_2)
    g = g >> 1;
  if (Gscale)
    g = scale8_video_LEAVING_R1_DIRTY(g, Gscale);
  if (sat != 255) {
    if (sat == 0) {
      r = 255;
      b = 255;
      g = 255;
    } else {
      uint8_t desat = 255 - sat;
      desat = scale8_video(desat, desat);
      uint8_t satscale = 255 - desat;
      r = scale8_LEAVING_R1_DIRTY(r, satscale);
      g = scale8_LEAVING_R1_DIRTY(g, satscale);
      b = scale8_LEAVING_R1_DIRTY(b, satscale);
      cleanup_R1();
      uint8_t brightness_floor = desat;
      r += brightness_floor;
      g += brightness_floor;
      b += brightness_floor;
    }
  }
  if (val != 255) {
    val = scale8_video_LEAVING_R1_DIRTY(val, val);
    if (val == 0) {
      r = 0;
      g = 0;
      b = 0;
    } else {
      r = scale8_LEAVING_R1_DIRTY(r, val);
      g = scale8_LEAVING_R1_DIRTY(g, val);
      b = scale8_LEAVING_R1_DIRTY(b, val);
      cleanup_R1();
    }
  }
  return (RGB){.r = r, .g = g, .b = b};
}
