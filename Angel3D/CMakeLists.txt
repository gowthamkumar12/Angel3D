# Name of the project
SET(ENGINE Angel3D)
PROJECT(${ENGINE} CXX)

message("Started to build for ${ENGINE} project.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set GLFW to build as a static library
set(GLFW_LIBRARY_TYPE "STATIC" CACHE STRING "Library type override for GLFW (SHARED, STATIC, OBJECT, or empty to follow BUILD_SHARED_LIBS)")

# Add GLFW as a subdirectory
ADD_SUBDIRECTORY(${GLFW}  ${GLFW}/build)
ADD_SUBDIRECTORY(${GLAD}  ${GLAD}/build)
ADD_SUBDIRECTORY(${IMGUI} ${IMGUI}/build)

# Define output directories
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${ENGINE}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${ENGINE}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_out/bin/${OUTPUT_DIR}/${ENGINE}")

# Create a precompiled header
SET(PCH_HEADER "inc/pch.h")
SET(PCH_SOURCE "src/pch.cpp")

# Creating this Angel3D library as a shared library (DLL)
ADD_LIBRARY(${ENGINE} SHARED)

# Add precompiled header
TARGET_PRECOMPILE_HEADERS(${ENGINE} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${PCH_HEADER}")

# Include directories
TARGET_INCLUDE_DIRECTORIES(
  ${ENGINE}
  PUBLIC
    "${PROJECT_SOURCE_DIR}/inc"         # Local include directory
    "${SPDLOGDIR}/include"
    "${GLFW}/include"
    "${GLAD}/include"
    "${IMGUI}"
    "${GLM}"
)

# Link GLFW and OpenGL as private dependencies
TARGET_LINK_LIBRARIES(
  ${ENGINE}
  PRIVATE
    glfw
    GLAD
    ImGui
    opengl32.lib
)

# Ensure linker flags for Dist configuration
IF(NOT CMAKE_SHARED_LINKER_FLAGS_DIST)
  SET(CMAKE_SHARED_LINKER_FLAGS_DIST "")
ENDIF()

# Platform-specific definitions
IF(WIN32)
  TARGET_COMPILE_DEFINITIONS(${ENGINE} PRIVATE ANGEL3D_PLATFORM_WINDOWS ANGEL3D_BUILD_DLL ANGEL3D_ENABLE_ASSERTS GLFW_INCLUDE_NONE)
ENDIF()

# Configuration-specific definitions
TARGET_COMPILE_DEFINITIONS(${ENGINE}
  PRIVATE
    $<$<CONFIG:Debug>:Angel3D_DEBUG>
    $<$<CONFIG:Release>:Angel3D_RELEASE>
    $<$<CONFIG:Dist>:Angel3D_DIST>
)

# Add source directory
ADD_SUBDIRECTORY(src)

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
