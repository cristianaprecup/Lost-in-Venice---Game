# Minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Project name
project(Lost-in-Venice)

# Set paths for SDL and SDL_mixer
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dependencies/SDL2-2.30.9/include)
set(SDL2_LIBRARY ${CMAKE_SOURCE_DIR}/dependencies/SDL2-2.30.9/lib/x86)

set(SDL2_MIXER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dependencies/SDL2_mixer-2.8.0/include)
set(SDL2_MIXER_LIBRARY ${CMAKE_SOURCE_DIR}/dependencies/SDL2_mixer-2.8.0/lib/x86)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}/SDL2.lib ${SDL2_LIBRARY}/SDL2main.lib ${SDL2_MIXER_LIBRARY}/SDL2_mixer.lib)

# Avoid library conflicts
target_link_options(${PROJECT_NAME} PRIVATE /NODEFAULTLIB:MSVCRT)
