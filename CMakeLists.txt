cmake_minimum_required(VERSION 3.16)

# Policy
if(${CMAKE_VERSION} VERSION_LESS 3.28)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.28)
endif()

project(xrLua)

set(CMAKE_CXX_STANDARD 17)

# Check if xrLua is being used directly or via add_subdirectory, but allow
# overriding
if(NOT DEFINED XRLUA_MAIN_PROJECT)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(XRLUA_MAIN_PROJECT TRUE)
  else()
    set(XRLUA_MAIN_PROJECT FALSE)
  endif()
endif()

# Options

# Settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# subdirectories
add_subdirectory(src)
