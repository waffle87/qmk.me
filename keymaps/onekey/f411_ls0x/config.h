// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#undef ADC_PIN
#undef BACKLIGHT_PIN
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

// clang-format off
#define DIRECT_PINS {{A0}}
// clang-format on

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN NO_PIN

#define LS0XX_CS_PIN A6
#define LS0XX_HEIGHT 160
#define LS0XX_WIDTH 80
#define LS0XX_SPI_DIVISOR 16
