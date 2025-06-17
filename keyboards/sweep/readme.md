# Sweep RP2040

![image](https://git.pngu.org/sweep/about/img/image1.jpg)

* Keyboard Maintainer: [jack@pngu.org](mailto:jack@pngu.org)
* Hardware Supported: PCBs with integrated RP2040 microcontroller
* Hardware Availability: [git/sweep](https://git.pngu.org/sweep)

Make example for this keyboard (after setting up your build environment):

    make sweep:default

Flashing example for this keyboard:

    make sweep:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset button**: Hold button labeled BOOT and tap RESET button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
