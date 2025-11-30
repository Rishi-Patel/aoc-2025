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

# Check if rebuild is needed
EXECUTABLE="$BUILD_DIR/$DAY/$DAY"
NEEDS_REBUILD=false

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    NEEDS_REBUILD=true
else
    # Check if any source files are newer than the executable
    # Check CMakeLists.txt
    if [ "$SCRIPT_DIR/CMakeLists.txt" -nt "$EXECUTABLE" ]; then
        NEEDS_REBUILD=true
    fi
    
    # Check day's main.cpp
    DAY_NUM="${DAY#day}"  # Remove "day" prefix to get number (e.g., "01")
    MAIN_CPP="$SCRIPT_DIR/$DAY_NUM/main.cpp"
    if [ -f "$MAIN_CPP" ] && [ "$MAIN_CPP" -nt "$EXECUTABLE" ]; then
        NEEDS_REBUILD=true
    fi
    
    # Check include files
    if [ -d "$SCRIPT_DIR/include" ]; then
        for include_file in "$SCRIPT_DIR/include"/*; do
            if [ -f "$include_file" ] && [ "$include_file" -nt "$EXECUTABLE" ]; then
                NEEDS_REBUILD=true
                break
            fi
        done
    fi

    # Check input.txt
    if [ -f "$SCRIPT_DIR/$DAY_NUM/input.txt" ] && [ "$SCRIPT_DIR/$DAY_NUM/input.txt" -nt "$EXECUTABLE" ]; then
        # Copy input.txt to the build directory
        cp "$SCRIPT_DIR/$DAY_NUM/input.txt" "$BUILD_DIR/$DAY/input.txt"
    fi
fi

# Build only if needed
if [ "$NEEDS_REBUILD" = true ]; then
    echo "Building $DAY..."
    cmake --build . --target "$DAY" || exit 1
fi

# Run the executable
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
    "$EXECUTABLE" < "$INPUT_FILE"
fi

