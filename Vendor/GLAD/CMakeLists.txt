CMAKE_MINIMUM_REQUIRED(VERSION 3.4...3.28 FATAL_ERROR)
PROJECT(GLAD VERSION 4.6 LANGUAGES C)

ADD_LIBRARY(GLAD STATIC src/glad.c)

# Include directories
TARGET_INCLUDE_DIRECTORIES(
  GLAD
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Configuration-specific definitions
TARGET_COMPILE_DEFINITIONS(
  GLAD
  PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)