# [Proton-C crkbd](https://git.pngu.org/protoncrkbd)

![img](https://i.imgur.com/ob8D0hY.jpeg)

## Miscellaneous Notes
- [Low Scan Mode](https://github.com/waffle87/qmk.me/blob/master/keymaps/crkbd/keymap.c#L5-#L27) to avoid unnecessary scans if there's no matrix activity (5s timeout)
- [Audio Configuration](https://github.com/waffle87/qmk.me/blob/master/keymaps/crkbd/keymap.c#L30-#L39) to pass output from B1 to A5 (proper DAC pin)
- [Align Pimoroni Trackball LED](https://github.com/waffle87/qmk.me/blob/master/keymaps/crkbd/keymap.c#L90-#L99) with active RGB Matrix animation/colour, and sets underglow LEDs to yellow
