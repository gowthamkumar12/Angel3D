# Name of the project
SET(EDITOR Editor)
PROJECT(${EDITOR} CXX)

message("Started to build for ${EDITOR} project.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define output directories
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${EDITOR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${EDITOR}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${EDITOR}")

# Ensure linker flags for Dist configuration
IF(NOT CMAKE_EXE_LINKER_FLAGS_DIST)
  SET(CMAKE_EXE_LINKER_FLAGS_DIST "")
ENDIF()

# Create the EDITOR executable
ADD_EXECUTABLE(${EDITOR})

# Add source files
ADD_SUBDIRECTORY(src)

# Include directories
TARGET_INCLUDE_DIRECTORIES(
  ${EDITOR}
  PUBLIC
    "${PROJECT_SOURCE_DIR}/inc"                   # Local include directory
    "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/inc"  # Engine headers
    "${GLM}"
)

# Link dependencies
TARGET_LINK_LIBRARIES(
  ${EDITOR}
  PRIVATE
    Engine
)

# Configuration-specific definitions
TARGET_COMPILE_DEFINITIONS(
  ${EDITOR}
  PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:Dist>:DIST>
)