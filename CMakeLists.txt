# CMake minimum version requirement
cmake_minimum_required(VERSION 3.10)

# Project name
project(GameOfLife)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set GCC as the compiler
set(CMAKE_CXX_COMPILER "g++")

# Define include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/src                       # Source files directory
    ${PROJECT_SOURCE_DIR}/dep/imgui                 # ImGui dependency
    ${PROJECT_SOURCE_DIR}/dep/SDL-3.2.4/include     # SDL include directory
)

# Define library directories
link_directories(${PROJECT_SOURCE_DIR}/dep/SDL-3.2.4/lib)  # SDL library directory

# Add source files
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Add ImGui source files
file(GLOB IMGUI_SOURCES ${PROJECT_SOURCE_DIR}/dep/imgui/*.cpp)

# Add ImGui to the list of sources
list(APPEND SOURCES ${IMGUI_SOURCES})

# Create the executable
add_executable(GameOfLife ${SOURCES})

# Link libraries
target_link_libraries(GameOfLife SDL3)

set_target_properties(GameOfLife PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
