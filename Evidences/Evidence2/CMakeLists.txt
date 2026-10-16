cmake_minimum_required(VERSION 3.10)
project(ActividadSearchAlgorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include source root so `#include "include/..."` paths resolve properly
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set global runtime output directory for all build configurations
set(RELEASE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/__release__")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${RELEASE_OUTPUT_DIR}")

# Collect all .cpp source files inside the src directory
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(ALL_TARGET_NAMES "")

# Build each file as an executable target safely
foreach(SOURCE_FILE IN LISTS SRC_FILES)
    # Extract filename without path or extension
    get_filename_component(TARGET_NAME "${SOURCE_FILE}" NAME_WE)
    
    # Pass target name and source path as distinct, quoted arguments
    add_executable("${TARGET_NAME}" "${SOURCE_FILE}" "${CMAKE_SOURCE_DIR}/include/processing.cpp")
    
    list(APPEND ALL_TARGET_NAMES "${TARGET_NAME}")
endforeach()

# Run hash verification after ALL targets are compiled
if(ALL_TARGET_NAMES)
    add_custom_target(UpdateAllHashes ALL
        COMMAND ${CMAKE_COMMAND}
            -DRELEASE_DIR=${RELEASE_OUTPUT_DIR}
            -DTARGET_NAMES="${ALL_TARGET_NAMES}"
            -P ${CMAKE_SOURCE_DIR}/cmake/finalizeHashes.cmake
        COMMENT "Testing all executable hashes and updating __release__/hash.txt..."
    )

    # Force UpdateAllHashes to run strictly after every executable target finishes building
    add_dependencies(UpdateAllHashes ${ALL_TARGET_NAMES})
endif()