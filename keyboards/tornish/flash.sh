#!/bin/sh
FIRMWARE=~/waffle_git/qmk_firmware/tornish_default.hex
BOOTLOADER=~/waffle_git/qmk_me/keyboards/tornish/usbasploader_atmega328p.hex

qmk compile -kb tornish -km default > /dev/null
sed -i '$ d' $FIRMWARE
cat $BOOTLOADER >> $FIRMWARE
doas avrdude -c usbtiny -p atmega328p -U flash:w:$FIRMWARE:i
