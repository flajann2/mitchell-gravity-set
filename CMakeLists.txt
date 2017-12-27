# Main project
cmake_minimum_required (VERSION 3.10.0)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

project (mgs VERSION 0.0.0 DESCRIPTION "Mitchell Gravity Set Compute")

add_subdirectory (compute)
add_subdirectory (gui)
add_subdirectory (test)
