# Unzahl

![image](https://git.pngu.org/unzahl/about/img/pcb_bottom.svg)

* Keyboard Maintainer: [jack@pngu.org](mailto:jack@pngu.org)
* Hardware Supported: PCB with integrated STM32G431 microcontroller
* Hardware Availability: [git/sweep](https://git.pngu.org/unzahl)

Make example for this keyboard (after setting up your build environment):

    make unzahl:default

Flashing example for this keyboard:

    make unzahl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset button**: Tap reset button on back of PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
