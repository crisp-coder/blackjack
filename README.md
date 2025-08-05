## Setup
0. Run "source ./env.sh" from the blackjack directory, this is the root of the project.

## Compiling and Running
0. Run the setup instructions to set environment variables.
1. Run target.sh from the root of the project to create the target directory
   and compile the program.
2. Run gui.sh to create the target directory and compile the game with gui enabled.
   Note that gui is not implemented yet, it is just a test window.
3. Run unit_test.sh to create the unit_test executable in the target directory.

## Unit Testing
0. Perform setup instructions to set environment variables.
1. Run ./target/unit_test to execute tests.
2. View results in logs directory.
3. Alternatively, tail the resulting file and rerun to view results as they are generated.

## Logs
0. Log files are generated in the logs directory after building or running a compiled target.
1. Run "tail -f <log_file_name>" from within the logs directory to view logs while
   the game is running. The blackjack runtime log is the log for the game.

## Cleaning
0. Perform Setup instructions to set environment variables.
1. Run the clean.sh script to remove all build and log files.

