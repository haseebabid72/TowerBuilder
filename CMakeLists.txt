cmake_minimum_required(VERSION 3.11)
project(TowerBuilder VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch raylib from GitHub
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)

# Set raylib build options
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/block.cpp
    src/tower.cpp
    src/scorehistory.cpp
)

# Header files (for IDE support)
set(HEADERS
    src/game.h
    src/block.h
    src/tower.h
    src/scorehistory.h
)

# Create executable
add_executable(TowerBuilder ${SOURCES} ${HEADERS})

# Link raylib
target_link_libraries(TowerBuilder PRIVATE raylib)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    target_link_libraries(TowerBuilder PRIVATE winmm)
endif()

if(APPLE)
    # macOS-specific settings
    target_link_libraries(TowerBuilder PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Installation
install(TARGETS TowerBuilder DESTINATION bin)
install(DIRECTORY assets DESTINATION bin)

# Print configuration
message(STATUS "")
message(STATUS "Tower Builder Configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
