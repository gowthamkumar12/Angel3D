# Required minimum CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

# Name of the project and the language supported
PROJECT(Angel3D C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the architecture
SET(CMAKE_GENERATOR_PLATFORM x86_64)

# Define build configurations
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "Available build types" FORCE)

# Set flags for each configuration
SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
SET(CMAKE_CXX_FLAGS_DIST    "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Set output directory
set(OUTPUT_DIR "$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_GENERATOR_PLATFORM}")

# Add the compiler definitions
ADD_DEFINITIONS(-D_LIBCPP_ABI_NAMESPACE=__1)

# Set the required vendor package paths
SET(SPDLOGDIR ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog)

# Specify the include directories
INCLUDE_DIRECTORIES(${SPDLOGDIR}/include)

# Add the subdirectories here.
ADD_SUBDIRECTORY(Sandbox)
ADD_SUBDIRECTORY(Angel3D)