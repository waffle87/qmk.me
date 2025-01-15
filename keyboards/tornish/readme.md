### half a [torn](https://github.com/rtitmuss/torn) keyboard used for minecraft :)
![img](https://i.imgur.com/e7zKTK7.jpeg)

for whatever reason, this board does not like to flash over usb.
so [flash.sh](flash.sh) does the work instead:
```shell
qmk compile -kb tornish -km default > /dev/null
sed -i '$ d' $FIRMWARE #remove last line from firmware hex file (eof indicator)
cat $BOOTLOADER >> $FIRMWARE #append bootloader hex file to firmware
avrdude -c usbtiny -p atmega328p -U flash:w:$FIRMWARE:i #flash firmware + bootloader over serial
```
