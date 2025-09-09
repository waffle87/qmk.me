#!/bin/sh

QMKME="$HOME/git/qmk_me"
QMKFIRMWARE="$HOME/git/qmk_firmware"

find $QMKFIRMWARE -type l -not -path "$QMKFIRMWARE/.venv/*" -delete
rm $QMKFIRMWARE/.git/info/exclude

ln -sv $QMKME/jack $QMKFIRMWARE/users/jack
echo "users/jack" >> $QMKFIRMWARE/.git/info/exclude

for dir in "keyboards"/*; do
  src="$QMKME/$dir"
  dst="$QMKFIRMWARE/$dir"
  ln -sv $src $dst
  echo "$dir" >> $QMKFIRMWARE/.git/info/exclude
done

link_keymap() {
  src="$QMKME/keymaps/$1"
  dst="$QMKFIRMWARE/keyboards/$2/keymaps/jack"
  ln -sv $src $dst
  echo "keyboards/$2/keymaps/jack" >> $QMKFIRMWARE/.git/info/exclude
}

link_keymap beiwagon boardsource/beiwagon
link_keymap bully mkh_studio/bully
link_keymap f60 bioi/f60
link_keymap kyria splitkb/kyria
link_keymap relic projectcain/relic
link_keymap vault35 projectcain/vault35
