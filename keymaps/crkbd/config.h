// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D3
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED
#define SERIAL_USART_SPEED 921600

#ifdef RGB_MATRIX_ENABLE
#undef WS2812_DI_PIN
#define WS2812_DI_PIN B5
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_PWM_DMA_CHANNEL 3
#define WS2812_PWM_DMAMUX_ID STM32_DMAMUX1_TIM3_UP
#endif

#ifdef ENCODER_ENABLE
#define ENCODER_A_PINS {B2}
#define ENCODER_B_PINS {B6}
#endif

#ifdef AUDIO_ENABLE
#define AUDIO_PIN A5
#define STARTUP_SONG SONG(ODE_TO_JOY)
#define AUDIO_CLICKY
#endif

#ifdef POINTING_DEVICE_ENABLE
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#endif
