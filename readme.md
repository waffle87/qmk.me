### layout
![layout](https://i.imgur.com/uKNJuKi.png)

### combos
`#define COMBO_TERM 50`
| trigger | output (single/double tap) |
| :-----: | :------------------------: |
| r + u   | enter                      |
| v + m   | ?                          |
| t + y   | :                          |
| b + n   | _                          |
| s + l   | +                          |
| d + k   | =                          |
| g + h   | ' / "                      |
| w + o   | - / —                      |
| e + r   | { / }                      |
| u + i   | [ / ]                      |
| e + i   | \ / \|                     |
| d + f   | left click                 |
| f + g   | right click                |

### oled
[font file](oledfont.h) can be viewed and modified at [qmk logo editor](https://joric.github.io/qle)\
all the boring animation code is stored in [oled.h](https://github.com/waffle87/qmk_firmware/blob/waffle_develop/users/waffle/oled.h)

**animations:**\
[felix the dog](https://github.com/waffle87/qmk_firmware/blob/waffle_develop/users/waffle/oled.c#L133-#L151)\
[bongo cat](https://github.com/waffle87/qmk_firmware/blob/waffle_develop/users/waffle/oled.c#L155-#L172)\
[layer animation](https://github.com/waffle87/qmk_firmware/blob/waffle_develop/users/waffle/oled.c#L206-#L229)\
below snippet can be used to render the big byte arrays used by animations.
where `size` is the array size and `action` is the animation frame name.
```c
void anim_frame(uint16_t size, char const action[][size]) {
  static uint8_t current_frame = 0;
  current_frame = (current_frame + 1) & 1;
  oled_write_raw_P(action[current_frame], size);
}
```
**custom timeout:**\
some animations don't respect `OLED_TIMEOUT`, so a custom timeout from [drashna](https://github.com/qmk/qmk_firmware/blob/develop/users/drashna/oled/oled_stuff.c) can be used.
this depends on `OLED_DISABLE_TIMEOUT` & `SPLIT_OLED_ENABLE` being defined.
```c
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    if (timer_elapsed32(oled_timer) > 180000) { //turn off after 3min
      oled_off();
      return false;
    } else
      oled_on();
  }
  if (!oled_task_keymap())
    return false;
  return false;
}

uint32_t oled_timer = 0;
void oled_timer_reset(void) {
  oled_timer = timer_read32();
}
```
`oled_timer_reset()` just needs to be called from `process_record_user()`:
```c
if (record->event.pressed)
  oled_timer_reset();
```
the above snippet is also neat because global oled behavior can be placed in `oled_task_user`,
while keyboard specific oled code, like rendering certain things, can go in `oled_task_keymap`.

### raw hid
[raw.py](raw.py) is a basic implementation modified from [rawhid in python](https://gist.github.com/fauxpark/03a3efcc7dbdfbfe57791ea267b13c55).
renders current time on oled display:
```c
void host_info(uint8_t data) {
  char buffer[3];
  oled_write_P((char*)itoa(data, buffer, 10), false);
}

void render_time(void) {
  if (user_state.hour < 10)
    oled_write_P(PSTR("0"), false);
  host_info(user_state.hour);
  oled_write_P(PSTR(":"), false);
  if (user_state.min < 10)
    oled_write_P(PSTR("0"), false);
  host_info(user_state.min);
}
```

### some keyboards
[crkbd](https://github.com/waffle87/qmk_firmware/tree/waffle_develop/keyboards/crkbd/keymaps/waffle)\
[relic](https://github.com/waffle87/qmk_firmware/tree/waffle_develop/keyboards/relic/keymaps/waffle)\
[kyria](https://github.com/waffle87/qmk_firmware/tree/waffle_develop/keyboards/splitkb/kyria/keymaps/waffle)\
[ferris](https://github.com/waffle87/qmk_firmware/tree/waffle_develop/keyboards/ferris/keymaps/waffle)\
[microdox](https://github.com/waffle87/qmk_firmware/tree/waffle_develop/keyboards/boardsource/microdox/keymaps/waffle)\
[minidox](https://github.com/waffle87/qmk_firmware/tree/waffle_develop/keyboards/handwired/minidox/keymaps/waffle)\
[leftover30](https://github.com/waffle87/qmk_firmware/blob/waffle_develop/keyboards/tominabox1/leftover30_arm/keymaps/waffle/keymap.c)
