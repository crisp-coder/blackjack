#! /bin/bash

# Verify blackjack root of project is defined or terminate script.
if [ ! -d "$BLACKJACK_DIR" ]; then
  echo "Blackjack root is not defined. Run source env.sh from blackjack dir to set environment variables."
  exit 1
fi

# Delete contents of build directory.
if [ -d $TARGET_DIR ]; then
  for f in "$TARGET_DIR"/*; do
    [ -e $f ] || continue
    echo "removing $f"
    rm -r "$f"
  done
fi

# Delete build directory.
if [ -e $TARGET_DIR ]; then
  echo "removing $TARGET_DIR"
  rm -r "$TARGET_DIR"
fi

# Delete contents of logs directory.
if [ -d $LOGS_DIR ]; then
  for f in "$LOGS_DIR"/*; do
    [ -e $f ] || continue
    echo "removing $f"
    rm -r "$f"
  done
fi

# Delete logs directory.
if [ -e $LOGS_DIR ]; then
  echo "removing $LOGS_DIR"
  rm -r "$LOGS_DIR"
fi

