// Copyright 2024 jack@pngu.org
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE
