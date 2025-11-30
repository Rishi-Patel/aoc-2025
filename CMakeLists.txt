cmake_minimum_required(VERSION 3.10)
project(aoc-2025)

set(CMAKE_CXX_STANDARD 23)

# All executables use the include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Build executables for days 01-12
foreach(day RANGE 1 12)
    # Format day number with leading zero (01, 02, ..., 12)
    if(day LESS 10)
        set(day_padded "0${day}")
    else()
        set(day_padded "${day}")
    endif()
    
    # Check if the directory exists before adding executable
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${day_padded}/main.cpp")
        add_executable(day${day_padded} ${day_padded}/main.cpp)
        
        # Set output directory for executable to be in its own folder
        set_target_properties(day${day_padded} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/day${day_padded}"
        )
        
        # Copy input.txt to the same folder as the executable
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${day_padded}/input.txt")
            add_custom_command(TARGET day${day_padded} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/${day_padded}/input.txt"
                "${CMAKE_CURRENT_BINARY_DIR}/day${day_padded}/input.txt"
                COMMENT "Copying input.txt for day${day_padded}"
            )
        endif()
    endif()
endforeach()

