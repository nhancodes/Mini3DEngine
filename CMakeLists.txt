cmake_minimum_required(VERSION 3.27)
project(mini_3d_engine VERSION 0.0.1 LANGUAGES C)

# Use C11 standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Export compile commands (optional, for editor support)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Include CPM for external libraries
include(cmake/CMakePackageManager.cmake)
include(cmake/ProjectOptions.cmake)
include(cmake/ProjectWarnings.cmake)

setup_project_options(options_target)
setup_project_warnings(warnings_target)

# Add engine subdirectory
add_subdirectory(engine)

# Game executable
add_executable(game game/main.c)

# Link game with engine and Raylib
target_link_libraries(game PRIVATE engine raylib options_target warnings_target)