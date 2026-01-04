// Copyright 2026 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP6
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4

#define LCD_CS_PIN GP5
#define LCD_DC_PIN GP6
#define LCD_RST_PIN GP28

#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 2
