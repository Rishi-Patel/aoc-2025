#!/bin/bash

# Check if day argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: ./run.sh <day>"
    echo "Example: ./run.sh day01"
    exit 1
fi

DAY=$1

# Validate day format (day01-day12)
if [[ ! $DAY =~ ^day(0[1-9]|1[0-2])$ ]]; then
    echo "Error: Day must be in format day01-day12"
    exit 1
fi

# Get the script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"

# Change to build directory
cd "$BUILD_DIR" || exit 1

# Run cmake if CMakeCache.txt doesn't exist
if [ ! -f "CMakeCache.txt" ]; then
    echo "Configuring CMake..."
    cmake "$SCRIPT_DIR" || exit 1
fi

# Build the specific target
echo "Building $DAY..."
cmake --build . --target "$DAY" || exit 1

# Run the executable
EXECUTABLE="$BUILD_DIR/$DAY/$DAY"
INPUT_FILE="$BUILD_DIR/$DAY/input.txt"

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found at $EXECUTABLE"
    exit 1
fi

if [ ! -f "$INPUT_FILE" ]; then
    echo "Warning: input.txt not found at $INPUT_FILE"
    echo "Running $DAY without input file..."
    "$EXECUTABLE"
else
    echo "Running $DAY with input.txt..."
    "$EXECUTABLE" < "$INPUT_FILE"
fi

