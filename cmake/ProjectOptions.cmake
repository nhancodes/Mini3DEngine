include_guard()

macro(setup_project_options optionTarget)
  add_library(${optionTarget} INTERFACE)

  if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set_property(TARGET ${optionTarget} PROPERTY C_STANDARD 17)
    target_compile_features(${optionTarget} INTERFACE c_std_17)

    target_compile_options(${optionTarget}
      INTERFACE
      /nologo
      /utf-8
      /permissive-
      /Zc:preprocessor
      )    
  endif()

  if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set_property(TARGET ${optionTarget} PROPERTY C_STANDARD 17)
    target_compile_features(${optionTarget} INTERFACE c_std_17)
    set_property(TARGET ${optionTarget} PROPERTY CMAKE_C_EXTENSIONS OFF)
    target_compile_options(${optionTarget} INTERFACE -fvisibility=hidden)
  endif()

  if (CMAKE_C_COMPILER_ID MATCHES ".*Clang")
    if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
      set_property(TARGET ${optionTarget} PROPERTY C_STANDARD 17)
      target_compile_features(${optionTarget} INTERFACE c_std_17)
      target_compile_options(${optionTarget}
        INTERFACE
        /utf-8
        /permissive-
      )
      endif()
      
      if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        set_property(TARGET ${optionTarget} PROPERTY C_STANDARD 17)
        set_property(TARGET ${optionTarget} PROPERTY CMAKE_C_EXTENSIONS OFF)
        target_compile_features(${optionTarget} INTERFACE c_std_17)
        target_compile_options(${optionTarget} INTERFACE -fvisibility=hidden)
      endif()
  endif()

endmacro()