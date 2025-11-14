// Copyright 2025 jack@pngu.org
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

void keyboard_pre_init_kb(void) {
  // Disable UCPDx_CCy AF on PB15
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_UCPD1_STROBE | SYSCFG_CFGR1_UCPD2_STROBE;
  keyboard_pre_init_user();
}

#if defined(QUANTUM_PAINTER_ENABLE) && defined(POINTING_DEVICE_ENABLE)
#error "Cannot enable both Quantum Painter and Pointing Device"
#endif

#ifdef QUANTUM_PAINTER_ENABLE
#include "qp.h"
static painter_device_t display;

void keyboard_post_init_kb(void) {
  display =
      qp_st7789_make_spi_device(ST7789_HEIGHT, ST7789_WIDTH, LCD_CS_PIN,
                                LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 0);
  qp_init(display, QP_ROTATION_0);
  keyboard_post_init_user();
}

void suspend_power_down_kb(void) {
  qp_power(display, false);
  suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
  qp_power(display, true);
  suspend_wakeup_init_user();
}
#endif // QUANTUM_PAINTER_ENABLE

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    // clang-format off
    {0, SW2_CS1, SW3_CS1, SW1_CS1},
    {0, SW2_CS2, SW3_CS2, SW1_CS2},
    {0, SW2_CS3, SW3_CS3, SW1_CS3},
    {0, SW2_CS4, SW3_CS4, SW1_CS4},
    {0, SW2_CS5, SW3_CS5, SW1_CS5},
    {0, SW2_CS6, SW3_CS6, SW1_CS6},
    {0, SW2_CS7, SW3_CS7, SW1_CS7},
    {0, SW2_CS8, SW3_CS8, SW1_CS8},
    {0, SW2_CS9, SW3_CS9, SW1_CS9},
    {0, SW2_CS10, SW3_CS10, SW1_CS10},
    {0, SW5_CS1, SW6_CS1, SW4_CS1},
    {0, SW5_CS2, SW6_CS2, SW4_CS2},
    {0, SW5_CS3, SW6_CS3, SW4_CS3},
    {0, SW5_CS4, SW6_CS4, SW4_CS4},
    {0, SW5_CS5, SW6_CS5, SW4_CS5},
    {0, SW5_CS6, SW6_CS6, SW4_CS6},
    {0, SW5_CS7, SW6_CS7, SW4_CS7},
    {0, SW5_CS8, SW6_CS8, SW4_CS8},
    {0, SW5_CS9, SW6_CS9, SW4_CS9},
    {0, SW5_CS10, SW6_CS10, SW4_CS10},
    {0, SW8_CS1, SW9_CS1, SW7_CS1},
    {0, SW8_CS2, SW9_CS2, SW7_CS2},
    {0, SW8_CS3, SW9_CS3, SW7_CS3},
    {0, SW8_CS4, SW9_CS4, SW7_CS4},
    {0, SW8_CS5, SW9_CS5, SW7_CS5},
    {0, SW8_CS6, SW9_CS6, SW7_CS6},
    {0, SW8_CS7, SW9_CS7, SW7_CS7},
    {0, SW8_CS8, SW9_CS8, SW7_CS8},
    {0, SW8_CS9, SW9_CS9, SW7_CS9},
    {0, SW8_CS10, SW9_CS10, SW7_CS10},
    {0, SW10_CS3, SW12_CS3, SW10_CS3},
    {0, SW10_CS4, SW12_CS4, SW10_CS4},
    {0, SW10_CS5, SW12_CS5, SW10_CS5},
    {0, SW10_CS6, SW12_CS6, SW10_CS6},
    {0, SW10_CS7, SW12_CS7, SW10_CS7},
    {0, SW10_CS8, SW12_CS8, SW10_CS8},
    // clang-format on
};
#endif // RGB_MATRIX_ENABLE
