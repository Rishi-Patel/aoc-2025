#!/bin/bash

# Check if day argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: ./run.sh <day> [build_type]"
    echo "Example: ./run.sh day01"
    echo "Example: ./run.sh day01 release"
    echo "Example: ./run.sh day01 debug"
    exit 1
fi

DAY=$1
BUILD_TYPE=${2:-Debug}  # Default to Debug if not provided

# Normalize build_type to have capital first letter (Debug or Release)
BUILD_TYPE=$(echo "$BUILD_TYPE" | awk '{print toupper(substr($0,1,1)) tolower(substr($0,2))}')

# Validate build_type
if [ "$BUILD_TYPE" != "Debug" ] && [ "$BUILD_TYPE" != "Release" ]; then
    echo "Error: build_type must be either 'debug' or 'release'"
    exit 1
fi

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

# Check if we need to reconfigure cmake
NEEDS_RECONFIGURE=false
if [ ! -f "CMakeCache.txt" ]; then
    NEEDS_RECONFIGURE=true
    echo "Configuring CMake for the first time..."
else
    # Check current build type in CMakeCache.txt
    CURRENT_BUILD_TYPE=$(grep "^CMAKE_BUILD_TYPE:" CMakeCache.txt 2>/dev/null | cut -d'=' -f2 | tr -d '\n')
    if [ "$CURRENT_BUILD_TYPE" != "$BUILD_TYPE" ]; then
        NEEDS_RECONFIGURE=true
        echo "Build type changed from $CURRENT_BUILD_TYPE to $BUILD_TYPE, reconfiguring CMake..."
    fi
fi

# Check if rebuild is needed
EXECUTABLE="$BUILD_DIR/$DAY/$DAY"
NEEDS_REBUILD=false

# Reconfigure cmake if needed
if [ "$NEEDS_RECONFIGURE" = true ]; then
    cmake "$SCRIPT_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" || exit 1
    # Force rebuild after reconfiguration
    NEEDS_REBUILD=true
fi

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

