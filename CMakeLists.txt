# Main project
cmake_minimum_required (VERSION 3.10.0)
project (mgs VERSION 0.0.0 DESCRIPTION "Mitchell Gravity Set Compute")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_subdirectory (compute)
add_subdirectory (gui)

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
