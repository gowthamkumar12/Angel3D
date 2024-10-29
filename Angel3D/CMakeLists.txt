# Name of the project
SET(ENGINE Angel3D)
PROJECT(${ENGINE} CXX)

# Ensure linker flags for Dist configuration
IF(NOT CMAKE_SHARED_LINKER_FLAGS_DIST)
  SET(CMAKE_SHARED_LINKER_FLAGS_DIST "")
ENDIF()

# Define output directories
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${ENGINE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${ENGINE}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${ENGINE}")

ADD_LIBRARY(${ENGINE} SHARED)

ADD_SUBDIRECTORY(src)

# Include directories
TARGET_INCLUDE_DIRECTORIES(
  ${ENGINE}
  PUBLIC
    "${PROJECT_SOURCE_DIR}/inc"         # Local include directory
)

# Platform-specific definitions
IF(WIN32)
  TARGET_COMPILE_DEFINITIONS(${ENGINE} PRIVATE ANGEL3D_PLATFORM_WINDOWS ANGEL3D_BUILD_DLL)
endif()

# Configuration-specific definitions
TARGET_COMPILE_DEFINITIONS(${ENGINE}
  PRIVATE
    $<$<CONFIG:Debug>:Angel3D_DEBUG>
    $<$<CONFIG:Release>:Angel3D_RELEASE>
    $<$<CONFIG:Dist>:Angel3D_DIST>
)

# Copy the required DLL after build
ADD_CUSTOM_COMMAND(TARGET ${ENGINE}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove -f "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/Sandbox"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/Sandbox"
    COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${ENGINE}/${ENGINE}.dll
      ${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/Sandbox
    COMMENT "Copying Angel3D.dll to Sandbox directory..."
)