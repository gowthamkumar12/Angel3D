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

# Create a precompiled header
set(PCH_HEADER "inc/pch.h")
set(PCH_SOURCE "src/pch.cpp")

ADD_LIBRARY(${ENGINE} SHARED)

# Add precompiled header
TARGET_PRECOMPILE_HEADERS(${ENGINE} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PCH_HEADER}")

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