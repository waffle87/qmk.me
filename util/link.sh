#!/bin/sh

QMKME="$HOME/git/qmk_me"
QMKFIRMWARE="$HOME/git/qmk_firmware"

find $QMKFIRMWARE -type l -not -path "$QMKFIRMWARE/.venv/*" -delete
rm $QMKFIRMWARE/.git/info/exclude

for dir in "keyboards"/*; do
  src="$QMKME/$dir"
  dst="$QMKFIRMWARE/$dir"
  ln -sv $src $dst
  echo "$dir" >> $QMKFIRMWARE/.git/info/exclude
done
