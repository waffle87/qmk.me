// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE

#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE

#undef RP_PWM_USE_PWM3
#define RP_PWM_USE_PWM3 TRUE
