#pragma once
#define RGB_DI_PIN B0
#define DRIVER_LED_TOTAL 34
#define RGB_MATRIX_SPLIT {17,17}
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define __ NO_PIN
#undef DIRECT_PINS
#undef DIRECT_PINS_RIGHT
#define DIRECT_PINS { \
   {D7,F7,F6,F5,F4},  \
   {B1,B3,B2,B6,D3},  \
   {D1,D0,D4,C6,E6},  \
   {B4,B5,__,__,__}   \
}
#define DIRECT_PINS_RIGHT { \
   {F4,F5,F6,F7,D7},        \
   {D3,B6,B2,B3,B1},        \
   {E6,C6,D4,D0,D1},        \
   {B5,B4,__,__,__}         \
}
