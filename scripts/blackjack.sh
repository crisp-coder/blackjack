#! /bin/bash

# Verify blackjack directory exists. It should be defined to set relative paths for other scripts.
if [ ! -d "$BLACKJACK_DIR" ]; then
  echo "Blackjack root directory not defined."
  echo "Run \"source ./scripts/env.sh\" from blackjack root directory to set environment variables."
  exit 1
fi

# Create build directory.
if [ ! -d $TARGET_DIR ]; then
  echo "Making target dir."
  mkdir "$TARGET_DIR"
fi

# Create logs directory.
if [ ! -d $LOGS_DIR ]; then
  echo "Making logs dir."
  mkdir "$LOGS_DIR"
fi

# Generate compilation command.
BUILD_LOG="$LOGS_DIR/build_log.txt"
includes="$BLACKJACK_DIR/includes"
src="$BLACKJACK_DIR/src"
compile="g++ -std=c++11 $src/cli/cli_main.cpp \
-I$includes \
-I$src \
-I$src/cli \
-I$src/cli/messages \
-I$src/cli/states \
-I$src/game \
-I$src/game/messages \
-I$src/game/states \
-I$src/player \
-I$src/player/messages \
-I$src/player/states \
-I$src/utils \
-o $TARGET_DIR/blackjack"

# Check that compile command is what was expected.
echo "$compile"

# Run compilation with redirect stderr to stdout and tee output to log file.
$compile 2>&1 | tee "$BUILD_LOG"

