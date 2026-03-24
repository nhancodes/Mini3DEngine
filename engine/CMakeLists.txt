# Download Raylib
CPMAddPackage(
  GITHUB_REPOSITORY raysan5/raylib
  GIT_SHALLOW ON
  GIT_TAG c1ab645ca298a2801097931d1079b10ff7eb9df8
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)

# Build engine library
add_library(engine STATIC engine.c my_math.c)

# Make headers visible to other targets
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link Raylib to engine
target_link_libraries(engine PUBLIC raylib)