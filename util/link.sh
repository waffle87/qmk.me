#!/bin/zsh
QMKME="$HOME/git/qmk_me"
QMKFIRMWARE="$HOME/git/qmk_firmware"

find $QMKFIRMWARE -type l -not -path "$QMKFIRMWARE/.venv/*" -delete
rm $QMKFIRMWARE/.git/info/exclude

ln -sv $QMKME/waffle $QMKFIRMWARE/users/waffle
echo "users/waffle" >> $QMKFIRMWARE/.git/info/exclude

for dir in "keyboards"/*; do
  src="$QMKME/$dir"
  dst="$QMKFIRMWARE/$dir"
  ln -sv $src $dst
  echo "$dir" >> $QMKFIRMWARE/.git/info/exclude
done

link() {
  src="$QMKME/keymaps/$1"
  dst="$QMKFIRMWARE/keyboards/$2/keymaps/waffle"
  ln -sv $src $dst
  echo "keyboards/$2/keymaps/waffle" >> $QMKFIRMWARE/.git/info/exclude
}

link crkbd crkbd
link bully mkh_studio/bully
link f60 bioi/f60
link ferris ferris
link kyria splitkb/kyria
link microdox boardsource/microdox
link the_q boardsource/the_q
