// Copyright Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// NOTE: written LSB first as the display expects them
#define LS0XX_WRITE 0x80 // Start sending framebuffer
#define LS0XX_VCOM 0x40  // Set VCOM high
#define LS0XX_CLEAR 0x20 // Clear
