#!/bin/zsh
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

link() {
  src="$QMKME/keymaps/$1"
  dst="$QMKFIRMWARE/keyboards/$2/keymaps/jack"
  ln -sv $src $dst
  echo "keyboards/$2/keymaps/jack" >> $QMKFIRMWARE/.git/info/exclude
}

link crkbd crkbd
link bully mkh_studio/bully
link f60 bioi/f60
link ferris ferris
link kyria splitkb/kyria
link relic projectcain/relic
link vault35 projectcain/vault35
