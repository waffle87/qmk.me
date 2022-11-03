### [proton-c crkbd](https://github.com/waffle87/waffle_corne)
![img](https://i.imgur.com/ob8D0hY.jpeg)

#### notes
[low scan mode](https://github.com/waffle87/qmk.me/blob/master/keymaps/crkbd/keymap.c#L24-#L46) to avoid unecessary scans if there's no matrix activity (5s timeout)\
[audio configuration](https://github.com/waffle87/qmk.me/blob/master/keymaps/crkbd/keymap.c#L49-#L57) to pass output from B1 to A5 (proper dac pin).
```c
extern LED_TYPE rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  pimoroni_trackball_set_rgbw(rgb_matrix_ws2812_array[29].r, rgb_matrix_ws2812_array[29].g, rgb_matrix_ws2812_array[29].b, 0);
  for (uint8_t i = led_min; i <= led_max; i++)
    if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW)
      rgb_matrix_set_color(i, RGB_YELLOW);
  return false;
}
```
above snippet aligns pimoronic trackball rgb led with the active rgb matrix animation, & sets the underglow leds to yellow.
