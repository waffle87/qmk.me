### RP2040 Kyria rev2
![photo](https://i.imgur.com/P0urp7n.jpeg)

#### parts & notes
* microcontrollers: [boardsource blok](https://boardsource.xyz/store/628b95b494dfa308a6581622)

blok uses GPIO16/17 for "standard" I2C pins, differing from what's found in [`/platforms/chibios/boards/QMK_PM2040/configs`](https://github.com/qmk/qmk_firmware/tree/develop/platforms/chibios/boards/QMK_PM2040/configs).
this means the following changes are required if using blok:

`config.h`
```c
#define I2C_DRIVER I2CD1
```
`mcuconf.h`
```c
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
```

* [35mm cirque trackpad](https://www.mouser.com/ProductDetail/Cirque/TM035035-2024-003?qs=sGAEpiMZZMu3sxpa5v1qrmePy6bg6o9msS9wwvLw9t0%3D) and [holder](https://www.thingiverse.com/thing:5385829)

to use I2C, R1 resistor must be removed.
luckily, the I2C pins are broken out, as i didn't bother using the FPC connector on the trackpad.
from there, wired trackpad directly to oled header pins on pcb. looks a bit iffy...
![trackpad wiring](https://i.imgur.com/tvLVEe0.jpeg)

* [pucks](https://splitkb.com/collections/keyboard-parts/products/tenting-puck) and [tripods](https://www.amazon.com/Manfrotto-MP3-BK-Large-Pocket-Support/dp/B00HCAB8MU) for tenting-puck
