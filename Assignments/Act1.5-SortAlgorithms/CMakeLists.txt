#
#   Activity 1.4 - Search Algorithms
#   Andrés Rodríguez Cantú 
#   
#   Copyright (C) Tecnólogico de Monterrey
#   
#   File: CMakeLists.txt
#   
#   Created:                   25/08/2026
#   Last Modified:             31/08/2026
#

cmake_minimum_required(VERSION 3.10)
project(ActividadSearchAlgorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/lib)

# Set global runtime output directory for all build configurations
set(RELEASE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/__release__")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${RELEASE_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${RELEASE_OUTPUT_DIR}")

add_executable(ActividadSearchAlgorithms  main.cpp)     # Actividades en clase
