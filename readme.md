# qmk.me
This is a self-contained repository for my personal [QMK](https://github.com/qmk/qmk_firmware) userspace & keyboard code.

![keyboard](https://i.imgur.com/s0dN0JD.jpeg)

## Building
Keymaps for keyboards that exist in [upstream QMK](https://github.com/qmk/qmk_firmware) can be compiled like normal, or through GitHub actions. For the custom keyboards this repository contains, they can be symlinked to a proper `qmk_firmware` repository.

eg.
```shell
ln -s qmk.me/keyboards/endgame qmk_firmware/keyboards/endgame
echo "keyboards/endgame" >> qmk_firmware/.git/info/exclude
qmk compile -kb endgame -km jack
```
## Layout

![layout](util/layout.svg)
