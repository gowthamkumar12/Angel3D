# Name of the project
SET(SANDBOX Sandbox)
PROJECT(${SANDBOX} CXX)

# Ensure linker flags for Dist configuration
IF(NOT CMAKE_EXE_LINKER_FLAGS_DIST)
  SET(CMAKE_EXE_LINKER_FLAGS_DIST "")
ENDIF()

# Define output directories
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${SANDBOX}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${SANDBOX}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${SANDBOX}")

# Create the Sandbox executable
ADD_EXECUTABLE(${SANDBOX})

ADD_SUBDIRECTORY(src)

# Include directories
TARGET_INCLUDE_DIRECTORIES(
  ${SANDBOX}
  PUBLIC
    "${PROJECT_SOURCE_DIR}/inc"                   # Local include directory
    "${CMAKE_CURRENT_SOURCE_DIR}/../Angel3D/inc"  # Angel3D headers
)

TARGET_LINK_LIBRARIES(
  ${SANDBOX}
  PRIVATE
    Angel3D
)

# Platform-specific definitions
IF(WIN32)
  TARGET_COMPILE_DEFINITIONS(${SANDBOX} PRIVATE ANGEL3D_PLATFORM_WINDOWS)
endif()

# Configuration-specific definitions
TARGET_COMPILE_DEFINITIONS(${SANDBOX}
  PRIVATE
    $<$<CONFIG:Debug>:Angel3D_DEBUG>
    $<$<CONFIG:Release>:Angel3D_RELEASE>
    $<$<CONFIG:Dist>:Angel3D_DIST>
)