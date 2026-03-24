cmake_minimum_required(VERSION 3.27)
project(mini_3d_engine VERSION 0.0.1 LANGUAGES C)

# Use C11 standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Export compile commands (optional, for editor support)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Include CPM for external libraries
include(cmake/CMakePackageManager.cmake)

# Add engine subdirectory
add_subdirectory(engine)

# Game executable
add_executable(game game/main.c)

# Include engine headers
target_include_directories(game PRIVATE test)

# Link game with engine and Raylib
target_link_libraries(game PRIVATE engine raylib)

if (true)
target_compile_options( game
  PUBLIC
  ${_projectWarnings}
  /W4 # Baseline reasonable warnings
  /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss of data
  /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
  /w14263 # 'function': member function does not override any base class virtual member function
  /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not
          # be destructed correctly
  /w14287 # 'operator': unsigned/negative constant mismatch
  /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
          # the for-loop scope
  /w14296 # 'operator': expression is always 'boolean_value'
  /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
  /w14545 # expression before comma evaluates to a function which is missing an argument list
  /w14546 # function call before comma missing argument list
  /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
  /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
  /w14555 # expression has no effect; expected expression with side- effect
  /w14619 # pragma warning: there is no warning number 'number'
  /w14640 # Enable warning on thread un-safe static member initialization
  /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
  /w14905 # wide string literal cast to 'LPSTR'
  /w14906 # string literal cast to 'LPWSTR'
  /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied

  /wd5030 # attribute is not recognized, prevent msvc from report on other compilers attribute
  /wd4068 # unknown pragma, prevent msvc from report on other compilers pragma
  /wd4297 # function assumed not to throw an exception but does, need to throw for EASSERT_EX in constexpr function
)
endif()