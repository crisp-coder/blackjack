# Blackjack
This is a blackjack game written in c++.
It is currently playable from the command line only.
It was made as a personal project for boot.dev

# Disclaimer
This game is not intended as a professional release or for use with real money.
This game is for entertainment and learning purposes only.

# Goals
The goals of this project are to practice c++ coding and project design.
It is a future goal to create a simple gui using a library or the terminal.

## Setup
1. Run "source ./env.sh" from the blackjack directory, this is the root of the project.

## Compiling and Running
1. Run the setup instructions to set environment variables.
2. Run target.sh from the root of the project to create the target directory
   and compile the program.
3. Run gui.sh to create the target directory and compile the game with gui enabled.
   Note that gui is not implemented yet, it is just a test window.
4. Run unit_test.sh to create the unit_test executable in the target directory.

## Unit Testing
1. Perform setup instructions to set environment variables.
2. Run ./target/unit_test to execute tests.
3. View results in logs directory.
4. Alternatively, tail the resulting file and rerun to view results as they are generated.

## Logs
1. Log files are generated in the logs directory after building or running a compiled target.
2. Run "tail -f <log_file_name>" from within the logs directory to view logs while
   the game is running. The blackjack runtime log is the log for the game.

## Cleaning
1. Perform Setup instructions to set environment variables.
2. Run the clean.sh script to remove all build and log files.

