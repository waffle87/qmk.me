# Sweep RP2040

![%KEYBOARD%](imgur.com image replace me!)

* Keyboard Maintainer: [Jack Sangdahl][https://github.com/waffle87]
* Hardware Supported: PCBs with integrated RP2040 microcontroller
* Hardware Availability: [git/sweep][https://git.pngu.org/sweep]

Make example for this keyboard (after setting up your build environment):

    make sweep:default

Flashing example for this keyboard:

    make sweep:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
