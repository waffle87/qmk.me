### rp2040 kyria rev2
![photo](https://i.imgur.com/P0urp7n.jpeg)

#### parts & notes
* microcontrollers: [boardsource blok](https://boardsource.xyz/store/628b95b494dfa308a6581622)

* [35mm cirque trackpad](https://www.mouser.com/ProductDetail/Cirque/TM035035-2024-003?qs=sGAEpiMZZMu3sxpa5v1qrmePy6bg6o9msS9wwvLw9t0%3D) and [holder](https://www.thingiverse.com/thing:5385829)

to use I2C, R1 resistor must be removed.
luckily, the I2C pins are broken out, as i didn't bother using the FPC connector on the trackpad.
from there, wired trackpad directly to oled header pins on pcb. looks a bit iffy...
![trackpad wiring](https://i.imgur.com/tvLVEe0.jpeg)

* [pucks](https://splitkb.com/collections/keyboard-parts/products/tenting-puck) and [tripods](https://www.amazon.com/Manfrotto-MP3-BK-Large-Pocket-Support/dp/B00HCAB8MU) for tenting-puck

* wpm graph is very resource intensive and drops matrix scan rate to ~200/s...
