#!/bin/sh

set -e

git_exclude() {
  local subdir="$1"
  local TARGET_DIR="$HOME/git/qmk_firmware"
  local EXCLUDE_FILE="$TARGET_DIR/.git/info/exclude"
  local EXCLUDE_PATTERN="keyboards/$subdir"

  if [[ ! -d "$TARGET_DIR/.git" ]]; then
    printf "Warning: %s is not a git repository; skipping\n" $TARGET_DIR
    return 0
  fi

  if ! grep -q "^$EXCLUDE_PATTERN" "$EXCLUDE_FILE" 2>/dev/null; then
    printf "Excluding %s in .git/info/exclude\n" $EXCLUDE_PATTERN
    echo "$EXCLUDE_PATTERN" >> "$EXCLUDE_FILE"
  fi
}

link() {
  local subdir="$1"
  local SOURCE_DIR="$HOME/git/qmk_me"
  local TARGET_DIR="$HOME/git/qmk_firmware"
  local SOURCE_PATH="$SOURCE_DIR/keyboards/$subdir"
  local TARGET_PATH="$TARGET_DIR/keyboards/$subdir"

  printf "Linking: %s\n" $subdir

  if [[ ! -d "$SOURCE_PATH" ]]; then
    printf "Error: %s does not exist!\n" $SOURCE_PATH
    return 1
  fi

  if [[ ! -d "$TARGET_PATH" ]]; then
    mkdir -p "$TARGET_PATH"
  fi

  for item in "$SOURCE_PATH"/*; do
    [[ ! -e "$item" ]] && continue

    local item_name=$(basename "$item")
    local target_item="$TARGET_PATH/$item_name"

    if [[ "$item_name" == "keymaps" ]]; then
      continue
    fi

    if [[ -e "$target_item" || -L "$target_item" ]]; then
      rm -rf "$target_item"
    fi

    ln -sv "$(realpath "$item")" "$target_item"

    if [[ ! -L "$target_item" ]]; then
      printf "Error: linking %s failed!\n" $subdir
    fi
  done

  git_exclude "$subdir"
}

link_keyboards() {
  local good_cnt=0
  local fail_cnt=0

  for subdir in "$@"; do
    if link "$subdir"; then
      ((good_cnt++))
    else
      ((fail_cnt++))
    fi
  done
  return $fail_cnt
}

link_keyboards endgame locus sweep xyz60
