// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP6
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4

#define LCD_CS_PIN GP5
#define LCD_DC_PIN GP6
#define LCD_RST_PIN GP28
#define LCD_DISPLAY_WIDTH 135
#define LCD_DISPLAY_HEIGHT 240
#define LCD_SPI_DIVISOR 4

#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 2

#define ADC_RESOLUTION 12
#define ADC_SATURATION ((1 << 12) - 1)
#define ADC_CURRENT_PIN GP26
#define ADC_VOLTAGE_PIN GP27
