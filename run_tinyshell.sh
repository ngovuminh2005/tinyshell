#!/bin/bash
# Helper script to run Tinyshell (Group 1) on Linux/macOS

# Find the directory where the script resides
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
TS_EXE_PATH=""

# Check common build locations relative to the script directory
if [ -f "$SCRIPT_DIR/tinyshell" ]; then
    TS_EXE_PATH="$SCRIPT_DIR/tinyshell"
elif [ -f "$SCRIPT_DIR/build/tinyshell" ]; then
    TS_EXE_PATH="$SCRIPT_DIR/build/tinyshell"
elif [ -f "$SCRIPT_DIR/build/Release/tinyshell" ]; then
    TS_EXE_PATH="$SCRIPT_DIR/build/Release/tinyshell"
elif [ -f "$SCRIPT_DIR/build/Debug/tinyshell" ]; then
    TS_EXE_PATH="$SCRIPT_DIR/build/Debug/tinyshell"
fi

if [ -n "$TS_EXE_PATH" ] && [ -x "$TS_EXE_PATH" ]; then
    echo "Starting Tinyshell (Group 1)..."
    # Execute the tinyshell directly
    "$TS_EXE_PATH"
else
    echo "tinyshell executable not found or not executable in common locations (., build/, build/Release/, build/Debug/) relative to this script."
    echo "Please compile the project (e.g., using CMake) and ensure the tinyshell executable is accessible."
    # Use read -p for interactive pause, or just exit for non-interactive use
    # read -p "Press enter to exit"
    exit 1
fi

# Exit with the status code of the tinyshell process
exit $?

