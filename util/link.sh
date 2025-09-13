#!/bin/sh

QMK_ME="$HOME/git/qmk_me"
QMK_FIRMWARE="$HOME/git/qmk_firmware"

find $QMK_FIRMWARE -type l -not -path "$QMK_FIRMWARE/.venv/*" -delete
rm $QMK_FIRMWARE/.git/info/exclude

link_keyboard() {
  src="$QMK_ME/keyboards/$1"
  dst="$QMK_FIRMWARE/keyboards/$1"
  ln -sv $src $dst
  echo "keyboards/$1" >> $QMK_FIRMWARE/.git/info/exclude
}

link_keyboard endgame
link_keyboard locus
link_keyboard pseusplit
link_keyboard sweep
link_keyboard xyz60
