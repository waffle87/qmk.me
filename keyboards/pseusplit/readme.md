# Pseusplit

* Keyboard Maintainer: [Jack Sangdahl](https://github.com/waffle87)
* Hardware Supported: PCBs with integrated STM32G0B1 microcontroller
* Hardware Availability: [git/pseusplit](https://git.pngu.org/pseusplit)

Make example for this keyboard (after setting up your build environment):

    make pseusplit:default

Flashing example for this keyboard:

    make pseusplit:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix
* **Physical reset button**: Briefly press the button on the back of the PCB
